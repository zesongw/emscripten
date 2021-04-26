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
      s += 'webnn' + type + 'Reference: function(id) {\n';
      s += '  WebNN.mgr' + type + '.reference(id);\n'
      s += '},\n';
      s += 'webnn' + type + 'Release: function(id) {\n';
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
      if (this["mgrNeuralNetworkContext"]) return;

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

      this["mgrNeuralNetworkContext"] = this["mgrNeuralNetworkContext"] || makeManager();
      {{{ webnn.makeInitManager('Compilation') }}}
      {{{ webnn.makeInitManager('Model') }}}
      {{{ webnn.makeInitManager('ModelBuilder') }}}
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
    CompileStatus: [
      'success',
      'error',
      'context-lost',
      'unknown',
    ],
    ComputeStatus: [
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
    ],
    PowerPreference: [
      'default',
      'low_power',
      'high_performance',
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

    makeCompilationOptions: function(ptr) {
      return {
        "powerPreference": this.PowerPreference[{{{ webnn.makeGetU32('ptr', C_STRUCTS.WebnnCompilationOptions.powerPreference) }}}],
      };
    },

    makeClampOptions: function(ptr) {
      return {
        "minValue": this.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.WebnnClampOptions.minValue, '*') }}}),
        "maxValue": this.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.WebnnClampOptions.maxValue, '*') }}}),
      };
    },

    makeOperandDescriptor: function(ptr) {
      return {
        "type": this.OperandType[
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WebnnOperandDescriptor.type) }}}
        ],
        "dimensions": this.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WebnnOperandDescriptor.dimensionsCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.WebnnOperandDescriptor.dimensions, '*') }}}
        ),
      };
    },
    
    makeConv2dOptions: function(ptr) {
      return {
        "padding": this.AutoPad[
            {{{ webnn.makeGetI32('ptr', C_STRUCTS.WebnnConv2dOptions.autoPad) }}}
          ] === 'explicit' ? this.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WebnnConv2dOptions.paddingCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.WebnnConv2dOptions.padding, '*') }}}
          ) : undefined,
        "strides": this.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WebnnConv2dOptions.stridesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WebnnConv2dOptions.strides, '*') }}}
        ),
        "dilations": this.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WebnnConv2dOptions.dilationsCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WebnnConv2dOptions.dilations, '*') }}}
        ),
        "autoPad": this.AutoPad[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WebnnConv2dOptions.autoPad) }}}
        ],
        "groups": {{{ webnn.makeGetI32('ptr', C_STRUCTS.WebnnConv2dOptions.groups) }}},
        "inputLayout": this.InputOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WebnnConv2dOptions.inputLayout) }}}
        ],
        "filterLayout": this.FilterOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WebnnConv2dOptions.filterLayout) }}}
        ]
      };
    },

    makeInput: function(ptr) {
      return {
        "buffer": this.makeArrayBufferView(
            {{{ makeGetValue('ptr', C_STRUCTS.WebnnInput.buffer, '*') }}}, 
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WebnnInput.size) }}}
        ),
        "dimensions":({{{ makeGetValue('ptr', C_STRUCTS.WebnnInput.dimensions, '*') }}} === 0) ? undefined :
            this.makeI32Array(
                {{{ webnn.makeGetU32('ptr', C_STRUCTS.WebnnInput.dimensionsCount) }}},
                {{{ makeGetValue('ptr', C_STRUCTS.WebnnInput.dimensions, '*') }}}
        ),
      };
    },

    makeOutput: function(ptr) {
      return {
        "buffer": ({{{ makeGetValue('ptr', C_STRUCTS.WebnnInput.buffer, '*') }}} === 0) ? undefined :
            this.makeArrayBufferView(
                {{{ makeGetValue('ptr', C_STRUCTS.WebnnInput.buffer, '*') }}}, 
                {{{ webnn.makeGetU32('ptr', C_STRUCTS.WebnnInput.size) }}}
        ),
        "dimensions":({{{ makeGetValue('ptr', C_STRUCTS.WebnnInput.dimensions, '*') }}} === 0) ? undefined :
            this.makeI32Array(
                {{{ webnn.makeGetU32('ptr', C_STRUCTS.WebnnInput.dimensionsCount) }}},
                {{{ makeGetValue('ptr', C_STRUCTS.WebnnInput.dimensions, '*') }}}
        ),
      };
    },
  },

  // *Reference/*Release

  {{{ webnn.makeReferenceRelease('Compilation') }}}
  {{{ webnn.makeReferenceRelease('Model') }}}
  {{{ webnn.makeReferenceRelease('ModelBuilder') }}}
  {{{ webnn.makeReferenceRelease('NamedInputs') }}}
  {{{ webnn.makeReferenceRelease('NamedOperands') }}}
  {{{ webnn.makeReferenceRelease('NamedOutputs') }}}
  {{{ webnn.makeReferenceRelease('NamedResults') }}}
  {{{ webnn.makeReferenceRelease('NeuralNetworkContext') }}}
  {{{ webnn.makeReferenceRelease('Operand') }}}
  {{{ webnn.makeReferenceRelease('Result') }}}

  // Methods of ModelBuilder

  webnnModelBuilderInput: function(builderId, namePtr, descPtr) {
    var builder = WebNN.mgrModelBuilder.get(builderId);
    var name = UTF8ToString(namePtr);
    var desc = WebNN.makeOperandDescriptor(descPtr);
    var input = builder.input(name, desc);
    return WebNN.mgrOperand.create(input);
  },

  webnnModelBuilderConstant: function(builderId, descPtr, valuePtr, size) {
    var builder = WebNN.mgrModelBuilder.get(builderId);
    var desc = WebNN.makeOperandDescriptor(descPtr);
    var buffer = WebNN.makeArrayBufferView(valuePtr, size);
    var constant = builder.constant(desc, buffer);
    return WebNN.mgrOperand.create(constant);
  },

  webnnModelBuilderConv2d: function(builderId, inputId, filterId, optionsPtr) {
    var builder = WebNN.mgrModelBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var filter = WebNN.mgrOperand.get(filterId);
    var options = WebNN.makeConv2dOptions(optionsPtr);
    var conv2d = builder.conv2d(input, filter, options);
    return WebNN.mgrOperand.create(conv2d);
  },

  webnnModelBuilderClamp: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrModelBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeClampOptions(optionsPtr);
    var clamp = builder.clamp(input, options);
    return WebNN.mgrOperand.create(clamp);
  },

  webnnModelBuilderAdd: function(builderId, aId, bId) {
    var builder = WebNN.mgrModelBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder.add(a, b);
    return WebNN.mgrOperand.create(c);
  },

  webnnCreateNamedInputs: function() {
    var inputs = {};
    return WebNN.mgrNamedInputs.create(inputs);
  },

  webnnNamedInputsSet: function(namedInputsId, namePtr, inputPtr) {
    var namedInputs = WebNN.mgrNamedInputs.get(namedInputsId);
    var name = UTF8ToString(namePtr);
    var input = WebNN.makeInput(inputPtr);
    namedInputs[name] = input;
  },

  webnnCreateNamedOutputs: function() {
    var outputs = {};
    return WebNN.mgrNamedOutputs.create(outputs);
  },

  webnnNamedOutputsSet: function(namedOutputsId, namePtr, outputPtr) {
    var namedOutputs = WebNN.mgrNamedOutputs.get(namedOutputsId);
    var name = UTF8ToString(namePtr);
    var output = WebNN.makeOutput(outputPtr);
    namedOutputs[name] = output;
  },

  webnnCreateNamedOperands: function() {
    var operands = {};
    return WebNN.mgrNamedOperands.create(operands);
  },

  webnnNamedOperandsSet: function(namedOperandsId, namePtr, operandId) {
    var namedOperands = WebNN.mgrNamedOperands.get(namedOperandsId);
    var name = UTF8ToString(namePtr);
    var operand = WebNN.mgrOperand.get(operandId);
    namedOperands[name] = operand;
  },

  webnnNeuralNetworkContextCreateModelBuilder: function(contextId) {
    var context = WebNN.mgrNeuralNetworkContext.get(contextId);
    var builder = context.createModelBuilder();
    return WebNN.mgrModelBuilder.create(builder);
  },

  webnnModelBuilderCreateModel: function(builderId, namedOperandsId) {
    var builder = WebNN.mgrModelBuilder.get(builderId);
    var namedOperands = WebNN.mgrNamedOperands.get(namedOperandsId);
    var model = builder.createModel(namedOperands);
    return WebNN.mgrModel.create(model);
  },

  webnnModelCompile: function(modelId, callback, userdata, optionsPtr) {
    var model = WebNN.mgrModel.get(modelId);
    var options = optionsPtr === 0 ? undefined : WebNN.makeCompilationOptions(optionsPtr);
    model.compile(options).then(function(compilation) {
      var compilationId = WebNN.mgrCompilation.create(compilation);
      {{{ makeDynCall('viiii', 'callback') }}}(0 /* WebnnCompileStatus_Success */, compilationId, 0, userdata);
    }, function(error) {
      var messagePtr = allocateUTF8(error.message);
      {{{ makeDynCall('viiii', 'callback') }}}(1 /* WebnnCompileStatus_Error */, 0, messagePtr, userdata);
    });
  },

  webnnCompilationCompute: function(compilationId, inputsId, callback, userdata, outputsId) {
    var compilation = WebNN.mgrCompilation.get(compilationId);
    var inputs = WebNN.mgrNamedInputs.get(inputsId);
    var outputs = outputsId === 0 ? undefined : WebNN.mgrNamedOutputs.get(outputsId);
    compilation.compute(inputs, outputs).then(function(results) {
      // TODO: implement results
      {{{ makeDynCall('viiii', 'callback') }}}(0 /* WebnnComputeStatus_Success */, 0, 0, userdata);
    }, function(error) {
      var messagePtr = allocateUTF8(error.message);
      {{{ makeDynCall('viiii', 'callback') }}}(1 /* WebnnComputeStatus_Error */, 0, messagePtr, userdata);
    });
  },

  webnnModelCompileSync: function(modelId, optionsPtr) {
    var model = WebNN.mgrModel.get(modelId);
    var options = optionsPtr === 0 ? undefined : WebNN.makeCompilationOptions(optionsPtr);
    try {
      var compilation = model.compileSync(options);
      return WebNN.mgrCompilation.create(compilation);
    } catch (error) {
      console.log('Model.compileSync failed: ' + error);
      return 0;  // nullptr
    }
  },

  webnnCompilationComputeSync: function(compilationId, inputsId, outputsId) {
    var compilation = WebNN.mgrCompilation.get(compilationId);
    var inputs = WebNN.mgrNamedInputs.get(inputsId);
    var outputs = outputsId === 0 ? undefined : WebNN.mgrNamedOutputs.get(outputsId);
    try {
      var results = compilation.computeSync(inputs, outputs);
      return WebNN.mgrNamedResults.create(results);
    } catch (error) {
      console.log('Model.computeSync failed: ' + error);
      return 0;   // nullptr
    }
    
  },

};

autoAddDeps(LibraryWebNN, '$WebNN');
mergeInto(LibraryManager.library, LibraryWebNN);
