/**
 * @license
 * Copyright 2021 The Emscripten Authors
 * SPDX-License-Identifier: MIT
 */

/*
 * WebNN support.
 *
 * This file implements the common C header <webnn/webnn.h> on top of the
 * browser's native JS WebNN implementation. This allows applications targeting
 * webnn-native (https://github.com/webmachinelearning/webnn-native) also target the Web with the
 * same API and fairly minimal changes - similar to OpenGL ES 2.0/3.0
 * on WebGL 1.0/2.0.
 */

{{{ (function() {
  // Helper functions for code generation
  global.webnn = {
    makeInitManager: function(type) {
      var mgr = 'this.mgr' + type
      return mgr + ' = ' + mgr + ' || makeManager();';
    },
    makeReferenceRelease: function(type) {
      var s = '';
      s += 'ml' + type + 'Reference: function(id) {\n';
      s += '  WebNN.mgr' + type + '.reference(id);\n'
      s += '},\n';
      s += 'ml' + type + 'Release: function(id) {\n';
      s += '  WebNN.mgr' + type + '.release(id);\n'
      s += '},';
      return s;
    },
    makeU64ToNumber: function(lowName, highName) {
      var ret = '('
      if (ASSERTIONS) {
        ret += 'assert(' + highName + ' < 0x200000), ';
      }
      ret += highName + ' * 0x100000000 + ' + lowName + ')\n'
      return ret;
    },
    makeGetBool: function(struct, offset) {
      // In an actual build, bool seems to be i8. But on the off-chance it's i32, on little-endian
      // this will still work as long as the value of 'true' isn't zero in the lowest byte.
      return '(' + makeGetValue(struct, offset, 'i8') + ' !== 0)';
    },
    makeGetU32: function(struct, offset) {
      return makeGetValue(struct, offset, 'i32', false, true);
    },
    makeGetI32: function(struct, offset) {
      return makeGetValue(struct, offset, 'i32', false, true);
    },
    makeGetF32: function(struct, offset) {
      return makeGetValue(struct, offset, 'f32', false, true);
    },
    makeGetU64: function(struct, offset) {
      var l = makeGetValue(struct, offset, 'i32', false, true);
      var h = makeGetValue('(' + struct + ' + 4)', offset, 'i32', false, true)
      return h + ' * 0x100000000 + ' + l
    },
    makeCheck: function(str) {
      if (!ASSERTIONS) return '';
      return 'assert(' + str + ');';
    },
    makeCheckDefined: function(name) {
      return this.makeCheck('typeof ' + name + ' !== "undefined"');
    },
  };
  return null;
})(); }}}

var LibraryWebNN = {
  $WebNN: {
    initManagers: function() {
      if (this["mgrContext"]) return;

      function makeManager() {
        return {
          objects: {},
          nextId: 1,
          create: function(object, wrapper /* = {} */) {
            wrapper = wrapper || {};

            var id = this.nextId++;
            {{{ webnn.makeCheck("typeof this.objects[id] === 'undefined'") }}}
            wrapper.refcount = 1;
            wrapper.object = object;
            this.objects[id] = wrapper;
            return id;
          },
          get: function(id) {
            if (id === 0) return undefined;
            var o = this.objects[id];
            {{{ webnn.makeCheckDefined('o') }}}
            return o.object;
          },
          reference: function(id) {
            var o = this.objects[id];
            {{{ webnn.makeCheckDefined('o') }}}
            o.refcount++;
          },
          release: function(id) {
            var o = this.objects[id];
            {{{ webnn.makeCheckDefined('o') }}}
            {{{ webnn.makeCheck('o.refcount > 0') }}}
            o.refcount--;
            if (o.refcount <= 0) {
              delete this.objects[id];
            }
          },
        };
      }

      this["mgrContext"] = this["mgrContext"] || makeManager();
      {{{ webnn.makeInitManager('Graph') }}}
      {{{ webnn.makeInitManager('GraphBuilder') }}}
      {{{ webnn.makeInitManager('NamedInputs') }}}
      {{{ webnn.makeInitManager('NamedOperands') }}}
      {{{ webnn.makeInitManager('NamedOutputs') }}}
      {{{ webnn.makeInitManager('NamedResults') }}}
      {{{ webnn.makeInitManager('Operand') }}}
      {{{ webnn.makeInitManager('Result') }}}
    },

    AutoPad: [
      'explicit',
      'same-upper',
      'same-lower',
    ],
    BuildGraphStatus: [
      'success',
      'error',
      'context-lost',
      'unknown',
    ],
    ComputeGraphStatus: [
      'success',
      'error',
      'context-lost',
      'unknown',
    ],
    ErrorFilter: [
      'none',
      'validation',
      'out-of-memory',
    ],
    ErrorType: [
      'no-error',
      'validation',
      'out-of-memory',
      'unknown',
      'device-lost',
    ],
    FilterOperandLayout: [
      'oihw',
      'hwio',
      'ohwi',
      'ihwo',
    ],
    InputOperandLayout: [
      'nchw',
      'nhwc',
    ],
    OperandType: [
      'float32',
      'float16',
      'int32',
      'uint32',
      'int8',
      'uint8',
    ],
    PowerPreference: [
      'default',
      'high_performance',
      'low_power',
    ],

    makeI32Array: function(count, arrayPtr) {
      var array = [];
      for (var i = 0; i < count; ++i, arrayPtr += 4) {
        array.push({{{ webnn.makeGetI32('arrayPtr', 0) }}});
      }
      return array;
    },

    makeArrayBufferView: function(offset, byteSize, type = "float32") {
      assert(type === "float32");
      // TODO: support other array buffer view types.
      return new Float32Array(HEAPU8.buffer, offset, byteSize / Float32Array.BYTES_PER_ELEMENT);
    },

    makeClampOptions: function(ptr) {
      return {
        "minValue": this.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.MLClampOptions.minValue, '*') }}}),
        "maxValue": this.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.MLClampOptions.maxValue, '*') }}}),
      };
    },

    makeOperandDescriptor: function(ptr) {
      return {
        "type": this.OperandType[
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLOperandDescriptor.type) }}}
        ],
        "dimensions": this.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLOperandDescriptor.dimensionsCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.MLOperandDescriptor.dimensions, '*') }}}
        ),
      };
    },
    
    makeConv2dOptions: function(ptr) {
      return {
        "padding": this.AutoPad[
            {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLConv2dOptions.autoPad) }}}
          ] === 'explicit' ? this.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLConv2dOptions.paddingCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.MLConv2dOptions.padding, '*') }}}
          ) : undefined,
        "strides": this.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLConv2dOptions.stridesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLConv2dOptions.strides, '*') }}}
        ),
        "dilations": this.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLConv2dOptions.dilationsCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLConv2dOptions.dilations, '*') }}}
        ),
        "autoPad": this.AutoPad[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLConv2dOptions.autoPad) }}}
        ],
        "groups": {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLConv2dOptions.groups) }}},
        "inputLayout": this.InputOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLConv2dOptions.inputLayout) }}}
        ],
        "filterLayout": this.FilterOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLConv2dOptions.filterLayout) }}}
        ]
      };
    },

    makeInput: function(ptr) {
      return {
        "data": this.makeArrayBufferView(
            {{{ makeGetValue('ptr', C_STRUCTS.MLInput.buffer, '*') }}}, 
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLInput.size) }}}
        ),
        "dimensions":({{{ makeGetValue('ptr', C_STRUCTS.MLInput.dimensions, '*') }}} === 0) ? undefined :
            this.makeI32Array(
                {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLInput.dimensionsCount) }}},
                {{{ makeGetValue('ptr', C_STRUCTS.MLInput.dimensions, '*') }}}
        ),
      };
    },

    makeOutput: function(ptr) {
      return {
        "data": ({{{ makeGetValue('ptr', C_STRUCTS.MLOutput.buffer, '*') }}} === 0) ? undefined :
            this.makeArrayBufferView(
                {{{ makeGetValue('ptr', C_STRUCTS.MLOutput.buffer, '*') }}}, 
                {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLOutput.size) }}}
        ),
        "dimensions":({{{ makeGetValue('ptr', C_STRUCTS.MLOutput.dimensions, '*') }}} === 0) ? undefined :
            this.makeI32Array(
                {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLOutput.dimensionsCount) }}},
                {{{ makeGetValue('ptr', C_STRUCTS.MLOutput.dimensions, '*') }}}
        ),
      };
    },
  },

  // *Reference/*Release

  {{{ webnn.makeReferenceRelease('Graph') }}}
  {{{ webnn.makeReferenceRelease('GraphBuilder') }}}
  {{{ webnn.makeReferenceRelease('NamedInputs') }}}
  {{{ webnn.makeReferenceRelease('NamedOperands') }}}
  {{{ webnn.makeReferenceRelease('NamedOutputs') }}}
  {{{ webnn.makeReferenceRelease('NamedResults') }}}
  {{{ webnn.makeReferenceRelease('Context') }}}
  {{{ webnn.makeReferenceRelease('Operand') }}}
  {{{ webnn.makeReferenceRelease('Result') }}}

  // Methods of GraphBuilder

  mlGraphBuilderInput: function(builderId, namePtr, descPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var name = UTF8ToString(namePtr);
    var desc = WebNN.makeOperandDescriptor(descPtr);
    var input = builder.input(name, desc);
    return WebNN.mgrOperand.create(input);
  },

  mlGraphBuilderConstant: function(builderId, descPtr, valuePtr, size) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var desc = WebNN.makeOperandDescriptor(descPtr);
    var buffer = WebNN.makeArrayBufferView(valuePtr, size);
    var constant = builder.constant(desc, buffer);
    return WebNN.mgrOperand.create(constant);
  },

  mlGraphBuilderConv2d: function(builderId, inputId, filterId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var filter = WebNN.mgrOperand.get(filterId);
    var options = WebNN.makeConv2dOptions(optionsPtr);
    var conv2d = builder.conv2d(input, filter, options);
    return WebNN.mgrOperand.create(conv2d);
  },

  mlGraphBuilderClamp: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeClampOptions(optionsPtr);
    var clamp = builder.clamp(input, options);
    return WebNN.mgrOperand.create(clamp);
  },

  mlGraphBuilderAdd: function(builderId, aId, bId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder.add(a, b);
    return WebNN.mgrOperand.create(c);
  },

  webnnCreateNamedInputs: function() {
    var inputs = {};
    return WebNN.mgrNamedInputs.create(inputs);
  },

  mlNamedInputsSet: function(namedInputsId, namePtr, inputPtr) {
    var namedInputs = WebNN.mgrNamedInputs.get(namedInputsId);
    var name = UTF8ToString(namePtr);
    var input = WebNN.makeInput(inputPtr);
    namedInputs[name] = input;
  },

  webnnCreateNamedOutputs: function() {
    var outputs = {};
    return WebNN.mgrNamedOutputs.create(outputs);
  },

  mlNamedOutputsSet: function(namedOutputsId, namePtr, outputPtr) {
    var namedOutputs = WebNN.mgrNamedOutputs.get(namedOutputsId);
    var name = UTF8ToString(namePtr);
    var output = WebNN.makeOutput(outputPtr);
    namedOutputs[name] = output;
  },

  webnnCreateNamedOperands: function() {
    var operands = {};
    return WebNN.mgrNamedOperands.create(operands);
  },

  mlNamedOperandsSet: function(namedOperandsId, namePtr, operandId) {
    var namedOperands = WebNN.mgrNamedOperands.get(namedOperandsId);
    var name = UTF8ToString(namePtr);
    var operand = WebNN.mgrOperand.get(operandId);
    namedOperands[name] = operand;
  },

  webnnCreateGraphBuilder: function(contextId) {
    var context = WebNN.mgrContext.get(contextId);
    var builder = new MLGraphBuilder(context);
    return WebNN.mgrGraphBuilder.create(builder);
  },

  mlGraphBuilderBuild: function(builderId, namedOperandsId, callback, userdata) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var namedOperands = WebNN.mgrNamedOperands.get(namedOperandsId);
    builder.build(namedOperands).then(function(graph) {
      var graphId = WebNN.mgrGraph.create(graph);
      {{{ makeDynCall('viiii', 'callback') }}}(0 /* MLBuildGraphStatus_Success */, graphId, 0, userdata);
    }, function(error) {
      var messagePtr = allocateUTF8(error.message);
      {{{ makeDynCall('viiii', 'callback') }}}(1 /* MLBuildGraphStatus_Error */, 0, messagePtr, userdata);
    });
  },

  mlGraphBuilderBuildSync: function(builderId, namedOperandsId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var namedOperands = WebNN.mgrNamedOperands.get(namedOperandsId);
    try {
      var graph = builder.buildSync(namedOperands);
      return WebNN.mgrGraph.create(graph);
    } catch (error) {
      console.log('builder.buildSync failed: ' + error);
      return 0;  // nullptr
    }
  },

  mlGraphCompute: function(graphId, inputsId, callback, userdata, outputsId) {
    var graph = WebNN.mgrGraph.get(graphId);
    var inputs = WebNN.mgrNamedInputs.get(inputsId);
    var outputs = outputsId === 0 ? undefined : WebNN.mgrNamedOutputs.get(outputsId);
    graph.compute(inputs, outputs).then(function(results) {
      // TODO: implement results
      {{{ makeDynCall('viiii', 'callback') }}}(0 /* MLComputeGraphStatus_Success */, 0, 0, userdata);
    }, function(error) {
      var messagePtr = allocateUTF8(error.message);
      {{{ makeDynCall('viiii', 'callback') }}}(1 /* MLComputeGraphStatus_Error */, 0, messagePtr, userdata);
    });
  },

  mlGraphComputeSync: function(graphId, inputsId, outputsId) {
    var graph = WebNN.mgrGraph.get(graphId);
    var inputs = WebNN.mgrNamedInputs.get(inputsId);
    var outputs = WebNN.mgrNamedOutputs.get(outputsId);
    return graph.computeSync(inputs, outputs);
  },

};

autoAddDeps(LibraryWebNN, '$WebNN');
mergeInto(LibraryManager.library, LibraryWebNN);
