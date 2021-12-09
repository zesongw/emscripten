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
      var mgr = 'WebNN.mgr' + type
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
      return makeGetValue(struct, offset, 'i32', false, false);
    },
    makeGetF32: function(struct, offset) {
      return makeGetValue(struct, offset, 'float');
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
      if (WebNN.mgrContext) return;

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

      {{{ webnn.makeInitManager('Context') }}}
      {{{ webnn.makeInitManager('Graph') }}}
      {{{ webnn.makeInitManager('GraphBuilder') }}}
      {{{ webnn.makeInitManager('NamedInputs') }}}
      {{{ webnn.makeInitManager('NamedOutputs') }}}
      {{{ webnn.makeInitManager('NamedOperands') }}}
      {{{ webnn.makeInitManager('Operand') }}}
      {{{ webnn.makeInitManager('Operator') }}}
    },

    AutoPad: [
      'explicit',
      'same-upper',
      'same-lower',
    ],
    ComputeGraphStatus: [
      'success',
      'error',
      'context-lost',
      'unknown',
    ],
    DevicePreference: [
      'default',
      'gpu',
      'cpu',
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
    InterpolationMode: [
      'nearest-neighbor',
      'linear',
    ],
    OperandType: [
      'float32',
      'float16',
      'int32',
      'uint32',
      'int8',
      'uint8',
    ],
    PaddingMode: [
      'constant',
      'edge',
      'reflection',
      'symmetric',
    ],
    PowerPreference: [
      'default',
      'high_performance',
      'low_power',
    ],
    RecurrentNetworkDirection: [
      'forward',
      'backward',
      'both',
    ],
    RecurrentNetworkWeightLayout: [
      'zrn',
      'rzn',
    ],

    makeI32Array: function(count, arrayPtr) {
      if (count === 0 || arrayPtr === 0) {
        return undefined;
      }
      var array = [];
      for (var i = 0; i < count; ++i, arrayPtr += 4) {
        array.push({{{ webnn.makeGetI32('arrayPtr', 0) }}});
      }
      return array;
    },

    makeF32Array: function(count, arrayPtr) {
      if (count === 0 || arrayPtr === 0) {
        return undefined;
      }
      var array = [];
      for (var i = 0; i < count; ++i, arrayPtr += 4) {
        array.push({{{ webnn.makeGetF32('arrayPtr', 0) }}});
      }
      return array;
    },

    makeArrayBufferView: function(ptr, type = "float32") {
      const offset = {{{ makeGetValue('ptr', C_STRUCTS.MLArrayBufferView.buffer, '*') }}} + 
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLArrayBufferView.byteOffset) }}};
      const byteSize = {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLArrayBufferView.byteLength) }}};
      if (type === "float32") {
        return new Float32Array(HEAPU8.buffer, offset, byteSize / Float32Array.BYTES_PER_ELEMENT);
      } else if (type === "uint32") {
        return new Uint32Array(HEAPU8.buffer, offset, byteSize / Uint32Array.BYTES_PER_ELEMENT);
      } else if (type === "int32") {
        return new Int32Array(HEAPU8.buffer, offset, byteSize / Uint32Array.BYTES_PER_ELEMENT);
      } else {
        // TODO: support other array buffer view types.
        console.warn(`operand type ${type} is not supported.`);
        assert(false);
      }
    },

    makeClampOptions: function(ptr) {
      return {
        "minValue": {{{ webnn.makeGetF32('ptr', C_STRUCTS.MLClampOptions.minValue) }}},
        "maxValue": {{{ webnn.makeGetF32('ptr', C_STRUCTS.MLClampOptions.maxValue) }}},
      };
    },

    makeBatchNormOptions: function(ptr) {
      return {
        "scale": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.MLBatchNormOptions.scale, '*') }}}),
        "bias": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.MLBatchNormOptions.bias, '*') }}}),
        "axis": {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLBatchNormOptions.axis) }}},
        "epsilon": {{{ webnn.makeGetF32('ptr', C_STRUCTS.MLBatchNormOptions.epsilon) }}},
        "activation": WebNN.mgrOperator.get({{{ makeGetValue('ptr', C_STRUCTS.MLBatchNormOptions.activation, '*') }}}),
      };
    },

    makeGemmOptions: function(ptr) {
      return {
        "c": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.MLGemmOptions.c, '*') }}}),
        "alpha": {{{ webnn.makeGetF32('ptr', C_STRUCTS.MLGemmOptions.alpha) }}},
        "beta": {{{ webnn.makeGetF32('ptr', C_STRUCTS.MLGemmOptions.beta) }}},
        "aTranspose": {{{ webnn.makeGetBool('ptr', C_STRUCTS.MLGemmOptions.aTranspose)}}},
        "bTranspose": {{{ webnn.makeGetBool('ptr', C_STRUCTS.MLGemmOptions.bTranspose)}}},
      };
    },

    makeLeakyReluOptions: function(ptr) {
      return {
        "alpha": {{{ webnn.makeGetF32('ptr', C_STRUCTS.MLLeakyReluOptions.alpha) }}},
      };
    },

    makeOperandDescriptor: function(ptr) {
      return {
        "type": WebNN.OperandType[
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLOperandDescriptor.type) }}}
        ],
        "dimensions": WebNN.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLOperandDescriptor.dimensionsCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.MLOperandDescriptor.dimensions, '*') }}}
        ),
      };
    },
    
    makeConv2dOptions: function(ptr) {
      return {
        "padding": WebNN.AutoPad[
            {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLConv2dOptions.autoPad) }}}
          ] === 'explicit' ? WebNN.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLConv2dOptions.paddingCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.MLConv2dOptions.padding, '*') }}}
          ) : undefined,
        "strides": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLConv2dOptions.stridesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLConv2dOptions.strides, '*') }}}
        ),
        "dilations": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLConv2dOptions.dilationsCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLConv2dOptions.dilations, '*') }}}
        ),
        "autoPad": WebNN.AutoPad[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLConv2dOptions.autoPad) }}}
        ],
        "groups": {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLConv2dOptions.groups) }}},
        "inputLayout": WebNN.InputOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLConv2dOptions.inputLayout) }}}
        ],
        "filterLayout": WebNN.FilterOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLConv2dOptions.filterLayout) }}}
        ],
        "bias": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.MLConv2dOptions.bias, '*') }}}),
        "activation": WebNN.mgrOperator.get({{{ makeGetValue('ptr', C_STRUCTS.MLConv2dOptions.activation, '*') }}}),
        "transpose": {{{ webnn.makeGetBool('ptr', C_STRUCTS.MLConv2dOptions.transpose)}}},
        "outputPadding": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLConv2dOptions.outputPaddingCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLConv2dOptions.outputPadding, '*') }}}
        ),
        "outputSizes": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLConv2dOptions.outputSizesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLConv2dOptions.outputSizes, '*') }}}
        ),
      };
    },

    makePool2dOptions: function(ptr) {
      return {
        "windowDimensions": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLPool2dOptions.windowDimensionsCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLPool2dOptions.windowDimensions, '*') }}}
        ),
        "padding": WebNN.AutoPad[
            {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLPool2dOptions.autoPad) }}}
          ] === 'explicit' ? WebNN.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLPool2dOptions.paddingCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.MLPool2dOptions.padding, '*') }}}
          ) : undefined,
        "strides": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLPool2dOptions.stridesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLPool2dOptions.strides, '*') }}}
        ),
        "dilations": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLPool2dOptions.dilationsCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLPool2dOptions.dilations, '*') }}}
        ),
        "autoPad": WebNN.AutoPad[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLPool2dOptions.autoPad) }}}
        ],
        "layout": WebNN.InputOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLPool2dOptions.layout) }}}
        ],
      };
    },

    makePadOptions: function(ptr) {
      return {
        "mode": WebNN.PaddingMode[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLPadOptions.mode) }}}
        ],
        "value": {{{ webnn.makeGetF32('ptr', C_STRUCTS.MLPadOptions.value) }}},
      }
    },

    makeReduceOptions: function(ptr) {
      return {
        "axes": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLReduceOptions.axesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLReduceOptions.axes, '*') }}}
        ),
        "keepDimensions": {{{ webnn.makeGetBool('ptr', C_STRUCTS.MLReduceOptions.keepDimensions)}}},
      }
    },

    makeInput: function(ptr) {
      if ({{{ makeGetValue('ptr', C_STRUCTS.MLInput.dimensions, '*') }}} === 0) {
        return WebNN.makeArrayBufferView(ptr + {{{ C_STRUCTS.MLInput.resource }}});
      } else {
        return {
          "resource": WebNN.makeArrayBufferView(ptr + {{{ C_STRUCTS.MLInput.resource }}}),
          "dimensions": WebNN.makeI32Array(
              {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLInput.dimensionsCount) }}},
              {{{ makeGetValue('ptr', C_STRUCTS.MLInput.dimensions, '*') }}}
          ),
        };
      }
    },

    makeTransposeOptions: function(ptr) {
      return {
        "permutation": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLTransposeOptions.permutationCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLTransposeOptions.permutation, '*') }}}
        )
      };
    },

    makeResample2dOptions: function(ptr) {
      return {
        "mode": WebNN.InterpolationMode[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.MLResample2dOptions.mode) }}}
        ],
        "scales": WebNN.makeF32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLResample2dOptions.scalesCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.MLResample2dOptions.scales, '*') }}}
        ),
        "sizes": WebNN.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLResample2dOptions.sizesCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.MLResample2dOptions.sizes, '*') }}}
        ),
        "axes": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.MLResample2dOptions.axesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.MLResample2dOptions.axes, '*') }}}
        ),
      };
    },

  },

  // *Reference/*Release

  {{{ webnn.makeReferenceRelease('Context') }}}
  {{{ webnn.makeReferenceRelease('Graph') }}}
  {{{ webnn.makeReferenceRelease('GraphBuilder') }}}
  {{{ webnn.makeReferenceRelease('NamedInputs') }}}
  {{{ webnn.makeReferenceRelease('NamedOperands') }}}
  {{{ webnn.makeReferenceRelease('NamedOutputs') }}}
  {{{ webnn.makeReferenceRelease('Operand') }}}
  {{{ webnn.makeReferenceRelease('Operator') }}}

  // Methods of GraphBuilder
  mlGraphBuilderAdd: function(builderId, aId, bId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder["add"](a, b);
    return WebNN.mgrOperand.create(c);
  },

  mlGraphBuilderAveragePool2d: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makePool2dOptions(optionsPtr);
    var pool2d = builder["averagePool2d"](input, options);
    return WebNN.mgrOperand.create(pool2d);
  },

  mlGraphBuilderBatchNorm: function(builderId, inputId, meanId, varianceId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var mean = WebNN.mgrOperand.get(meanId);
    var variance = WebNN.mgrOperand.get(varianceId);
    var options = WebNN.makeBatchNormOptions(optionsPtr);
    var output = builder["batchNormalization"](input, mean, variance, options);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderBuild: function(builderId, namedOperandsId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var namedOperands = WebNN.mgrNamedOperands.get(namedOperandsId);
    try {
      var graph = builder["build"](namedOperands);
      return WebNN.mgrGraph.create(graph);
    } catch (error) {
      console.log('builder.build failed: ' + error);
      return 0;  // nullptr
    }
  },

  mlGraphBuilderClamp: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeClampOptions(optionsPtr);
    var clamp = builder["clamp"](input, options);
    return WebNN.mgrOperand.create(clamp);
  },

  mlGraphBuilderClampOperator: function(builderId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var options = WebNN.makeClampOptions(optionsPtr);
    var clamp = builder["clamp"](options);
    return WebNN.mgrOperator.create(clamp);
  },

  mlGraphBuilderConcat: function(builderId, inputsCount, inputsPtr, axis) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var inputIds = WebNN.makeI32Array(inputsCount, inputsPtr);
    var inputs = [];
    for (var i = 0; i < inputIds.length; ++i) {
      inputs.push(WebNN.mgrOperand.get(inputIds[i]));
    }
    var output = builder["concat"](inputs, axis);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderConstant: function(builderId, descPtr, arrayBufferViewPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var desc = WebNN.makeOperandDescriptor(descPtr);
    var buffer = WebNN.makeArrayBufferView(arrayBufferViewPtr, desc.type);
    var constant;
    if (desc["dimensions"] === undefined) {
      constant = builder["constant"](buffer[0]);
    } else {
      constant = builder["constant"](desc, buffer);
    }
    return WebNN.mgrOperand.create(constant);
  },

  mlGraphBuilderConv2d: function(builderId, inputId, filterId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var filter = WebNN.mgrOperand.get(filterId);
    var options = WebNN.makeConv2dOptions(optionsPtr);
    var conv2d = builder["conv2d"](input, filter, options);
    return WebNN.mgrOperand.create(conv2d);
  },

  mlGraphBuilderDiv: function(builderId, aId, bId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder["div"](a, b);
    return WebNN.mgrOperand.create(c);
  },

  mlGraphBuilderGemm: function(builderId, aId, bId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var options = WebNN.makeGemmOptions(optionsPtr);
    var output = builder["gemm"](a, b, options);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderInput: function(builderId, namePtr, descPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var name = UTF8ToString(namePtr);
    var desc = WebNN.makeOperandDescriptor(descPtr);
    var input = builder["input"](name, desc);
    return WebNN.mgrOperand.create(input);
  },

  mlGraphBuilderHardSwish: function(builderId, inputId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var output = builder["hardSwish"](input);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderHardSwishOperator: function(builderId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var output = builder["hardSwish"]();
    return WebNN.mgrOperator.create(output);
  },

  mlGraphBuilderLeakyRelu: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeLeakyReluOptions(optionsPtr);
    var output = builder["leakyRelu"](input, options);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderLeakyReluOperator: function(builderId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var options = WebNN.makeLeakyReluOptions(optionsPtr);
    var output = builder["leakyRelu"](options);
    return WebNN.mgrOperator.create(output);
  },

  mlGraphBuilderMatmul: function(builderId, aId, bId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder["matmul"](a, b);
    return WebNN.mgrOperand.create(c);
  },

  mlGraphBuilderMaxPool2d: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makePool2dOptions(optionsPtr);
    var pool2d = builder["maxPool2d"](input, options);
    return WebNN.mgrOperand.create(pool2d);
  },

  mlGraphBuilderMul: function(builderId, aId, bId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder["mul"](a, b);
    return WebNN.mgrOperand.create(c);
  },

  mlGraphBuilderPad: function(builderId, inputId, paddingId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var padding = WebNN.mgrOperand.get(paddingId);
    var options = WebNN.makePadOptions(optionsPtr);
    var output = builder["pad"](input, padding, options);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderReduceMean: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeReduceOptions(optionsPtr);
    var output = builder["reduceMean"](input, options);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderRelu: function(builderId, inputId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var output = builder["relu"](input);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderReluOperator: function(builderId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var output = builder["relu"]();
    return WebNN.mgrOperator.create(output);
  },

  mlGraphBuilderResample2d: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeResample2dOptions(optionsPtr);
    var output = builder["resample2d"](input, options);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderReshape: function(builderId, inputId, newShapePtr, newShapeCount) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var newShape = WebNN.makeI32Array(newShapeCount, newShapePtr);
    var output = builder["reshape"](input, newShape);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderSigmoid: function(builderId, inputId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var output = builder["sigmoid"](input);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderSigmoidOperator: function(builderId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var output = builder["sigmoid"]();
    return WebNN.mgrOperator.create(output);
  },

  mlGraphBuilderSoftmax: function(builderId, inputId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var output = builder["softmax"](input);
    return WebNN.mgrOperand.create(output);
  },

  mlGraphBuilderSub: function(builderId, aId, bId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder["sub"](a, b);
    return WebNN.mgrOperand.create(c);
  },

  mlGraphBuilderTranspose: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeTransposeOptions(optionsPtr);
    var output = builder["transpose"](input, options);
    return WebNN.mgrOperand.create(output);
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

  mlNamedOutputsSet: function(namedOutputsId, namePtr, arrayBufferViewPtr) {
    var namedOutputs = WebNN.mgrNamedOutputs.get(namedOutputsId);
    var name = UTF8ToString(namePtr);
    var output = WebNN.makeArrayBufferView(arrayBufferViewPtr);
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
  
  mlGraphCompute: function(graphId, inputsId, outputsId) {
    var graph = WebNN.mgrGraph.get(graphId);
    var inputs = WebNN.mgrNamedInputs.get(inputsId);
    var outputs = WebNN.mgrNamedOutputs.get(outputsId);
    return graph["compute"](inputs, outputs);
  },

};

autoAddDeps(LibraryWebNN, '$WebNN');
mergeInto(LibraryManager.library, LibraryWebNN);
