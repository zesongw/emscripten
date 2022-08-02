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
      s += 'wnn' + type + 'Reference: function(id) {\n';
      s += '  WebNN.mgr' + type + '.reference(id);\n'
      s += '},\n';
      s += 'wnn' + type + 'Release: function(id) {\n';
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
      {{{ webnn.makeInitManager('FusionOperator') }}}
      {{{ webnn.makeInitManager('Graph') }}}
      {{{ webnn.makeInitManager('GraphBuilder') }}}
      {{{ webnn.makeInitManager('Instance') }}}
      {{{ webnn.makeInitManager('NamedInputs') }}}
      {{{ webnn.makeInitManager('NamedOutputs') }}}
      {{{ webnn.makeInitManager('NamedOperands') }}}
      {{{ webnn.makeInitManager('Operand') }}}
      {{{ webnn.makeInitManager('OperandArray') }}}
      {{{ webnn.makeInitManager('OperatorArray') }}}
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
    ConvTranspose2dFilterOperandLayout: [
      "iohw",
      "hwoi",
      "ohwi",
    ],
    Conv2dFilterOperandLayout: [
      "oihw",
      "hwio",
      "ohwi",
      "ihwo",
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
    RoundingType: [
      'floor',
      'ceil',
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

    makeU32Array: function(count, arrayPtr) {
      if (count === 0 || arrayPtr === 0) {
        return undefined;
      }
      var array = [];
      for (var i = 0; i < count; ++i, arrayPtr += 4) {
        array.push({{{ webnn.makeGetU32('arrayPtr', 0) }}});
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
      const offset = {{{ makeGetValue('ptr', C_STRUCTS.WNNArrayBufferView.buffer, '*') }}} +
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNArrayBufferView.byteOffset) }}};
      const byteSize = {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNArrayBufferView.byteLength) }}};
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

    makeResource: function(ptr) {
      return WebNN.makeArrayBufferView(ptr + {{{ C_STRUCTS.WNNResource.arrayBufferView }}});
    },

    makeClampOptions: function(ptr) {
      return {
        "minValue": {{{ webnn.makeGetF32('ptr', C_STRUCTS.WNNClampOptions.minValue) }}},
        "maxValue": {{{ webnn.makeGetF32('ptr', C_STRUCTS.WNNClampOptions.maxValue) }}},
      };
    },

    makeBatchNormOptions: function(ptr) {
      return {
        "scale": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.WNNBatchNormOptions.scale, '*') }}}),
        "bias": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.WNNBatchNormOptions.bias, '*') }}}),
        "axis": {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNBatchNormOptions.axis) }}},
        "epsilon": {{{ webnn.makeGetF32('ptr', C_STRUCTS.WNNBatchNormOptions.epsilon) }}},
        "activation": WebNN.mgrFusionOperator.get({{{ makeGetValue('ptr', C_STRUCTS.WNNBatchNormOptions.activation, '*') }}}),
      };
    },

    makeGemmOptions: function(ptr) {
      return {
        "c": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.WNNGemmOptions.c, '*') }}}),
        "alpha": {{{ webnn.makeGetF32('ptr', C_STRUCTS.WNNGemmOptions.alpha) }}},
        "beta": {{{ webnn.makeGetF32('ptr', C_STRUCTS.WNNGemmOptions.beta) }}},
        "aTranspose": {{{ webnn.makeGetBool('ptr', C_STRUCTS.WNNGemmOptions.aTranspose)}}},
        "bTranspose": {{{ webnn.makeGetBool('ptr', C_STRUCTS.WNNGemmOptions.bTranspose)}}},
      };
    },

    makeGruOptions: function(ptr) {
      return {
        "bias": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.WNNGruOptions.bias, '*') }}}),
        "recurrentBias": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.WNNGruOptions.recurrentBias, '*') }}}),
        "initialHiddenState": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.WNNGruOptions.initialHiddenState, '*') }}}),
        "resetAfter": {{{ webnn.makeGetBool('ptr', C_STRUCTS.WNNGruOptions.resetAfter)}}},
        "returnSequence": {{{ webnn.makeGetBool('ptr', C_STRUCTS.WNNGruOptions.returnSequence)}}},
        "direction": WebNN.RecurrentNetworkDirection[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNGruOptions.direction) }}}
        ],
        "layout": WebNN.RecurrentNetworkWeightLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNGruOptions.layout) }}}
        ],
        "activations": WebNN.mgrOperatorArray.get({{{ makeGetValue('ptr', C_STRUCTS.WNNGruOptions.activations, '*') }}}),
      };
    },

    makeLeakyReluOptions: function(ptr) {
      return {
        "alpha": {{{ webnn.makeGetF32('ptr', C_STRUCTS.WNNLeakyReluOptions.alpha) }}},
      };
    },

    makeOperandDescriptor: function(ptr) {
      return {
        "type": WebNN.OperandType[
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNOperandDescriptor.type) }}}
        ],
        "dimensions": WebNN.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNOperandDescriptor.dimensionsCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.WNNOperandDescriptor.dimensions, '*') }}}
        ),
      };
    },

    makeConvTranspose2dOptions: function(ptr) {
      return {
        "padding": WebNN.AutoPad[
            {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNConvTranspose2dOptions.autoPad) }}}
          ] === 'explicit' ? WebNN.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNConvTranspose2dOptions.paddingCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.WNNConvTranspose2dOptions.padding, '*') }}}
          ) : undefined,
        "strides": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNConvTranspose2dOptions.stridesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNConvTranspose2dOptions.strides, '*') }}}
        ),
        "dilations": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNConvTranspose2dOptions.dilationsCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNConvTranspose2dOptions.dilations, '*') }}}
        ),
        "outputPadding": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNConvTranspose2dOptions.outputPaddingCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNConvTranspose2dOptions.outputPadding, '*') }}}
        ),
        "outputSizes": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNConvTranspose2dOptions.outputSizesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNConvTranspose2dOptions.outputSizes, '*') }}}
        ),
        "autoPad": WebNN.AutoPad[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNConvTranspose2dOptions.autoPad) }}}
        ],
        "groups": {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNConvTranspose2dOptions.groups) }}},
        "inputLayout": WebNN.InputOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNConvTranspose2dOptions.inputLayout) }}}
        ],
        "filterLayout": WebNN.ConvTranspose2dFilterOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNConvTranspose2dOptions.filterLayout) }}}
        ],
        "bias": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.WNNConvTranspose2dOptions.bias, '*') }}}),
        "activation": WebNN.mgrFusionOperator.get({{{ makeGetValue('ptr', C_STRUCTS.WNNConvTranspose2dOptions.activation, '*') }}}),
      };
    },

    makeConv2dOptions: function(ptr) {
      return {
        "padding": WebNN.AutoPad[
            {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNConv2dOptions.autoPad) }}}
          ] === 'explicit' ? WebNN.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNConv2dOptions.paddingCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.WNNConv2dOptions.padding, '*') }}}
          ) : undefined,
        "strides": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNConv2dOptions.stridesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNConv2dOptions.strides, '*') }}}
        ),
        "dilations": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNConv2dOptions.dilationsCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNConv2dOptions.dilations, '*') }}}
        ),
        "autoPad": WebNN.AutoPad[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNConv2dOptions.autoPad) }}}
        ],
        "groups": {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNConv2dOptions.groups) }}},
        "inputLayout": WebNN.InputOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNConv2dOptions.inputLayout) }}}
        ],
        "filterLayout": WebNN.Conv2dFilterOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNConv2dOptions.filterLayout) }}}
        ],
        "bias": WebNN.mgrOperand.get({{{ makeGetValue('ptr', C_STRUCTS.WNNConv2dOptions.bias, '*') }}}),
        "activation": WebNN.mgrFusionOperator.get({{{ makeGetValue('ptr', C_STRUCTS.WNNConv2dOptions.activation, '*') }}}),
      };
    },

    makePool2dOptions: function(ptr) {
      return {
        "windowDimensions": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNPool2dOptions.windowDimensionsCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNPool2dOptions.windowDimensions, '*') }}}
        ),
        "padding": WebNN.AutoPad[
            {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNPool2dOptions.autoPad) }}}
          ] === 'explicit' ? WebNN.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNPool2dOptions.paddingCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.WNNPool2dOptions.padding, '*') }}}
          ) : undefined,
        "strides": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNPool2dOptions.stridesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNPool2dOptions.strides, '*') }}}
        ),
        "dilations": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNPool2dOptions.dilationsCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNPool2dOptions.dilations, '*') }}}
        ),
        "autoPad": WebNN.AutoPad[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNPool2dOptions.autoPad) }}}
        ],
        "layout": WebNN.InputOperandLayout[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNPool2dOptions.layout) }}}
        ],
        "roundingType": WebNN.RoundingType[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNPool2dOptions.roundingType) }}}
        ],
        "outputSizes": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNPool2dOptions.outputSizesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNPool2dOptions.outputSizes, '*') }}}
        ),
      };
    },

    makeSplitOptions: function(ptr) {
      return {
        "axis": {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNSplitOptions.axis) }}},
      };
    },

    makeSqueezeOptions: function(ptr) {
      return {
        "axes": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNSqueezeOptions.axesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNSqueezeOptions.axes, '*') }}}
        )
      };
    },

    makePadOptions: function(ptr) {
      return {
        "mode": WebNN.PaddingMode[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNPadOptions.mode) }}}
        ],
        "value": {{{ webnn.makeGetF32('ptr', C_STRUCTS.WNNPadOptions.value) }}},
      }
    },

    makeReduceOptions: function(ptr) {
      return {
        "axes": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNReduceOptions.axesCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNReduceOptions.axes, '*') }}}
        ),
        "keepDimensions": {{{ webnn.makeGetBool('ptr', C_STRUCTS.WNNReduceOptions.keepDimensions)}}},
      }
    },

    makeInput: function(ptr) {
      if ({{{ makeGetValue('ptr', C_STRUCTS.WNNInput.dimensions, '*') }}} === 0) {
        return WebNN.makeResource(ptr + {{{ C_STRUCTS.WNNInput.resource }}});
      } else {
        return {
          "resource": WebNN.makeResource(ptr + {{{ C_STRUCTS.WNNInput.resource }}}),
          "dimensions": WebNN.makeI32Array(
              {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNInput.dimensionsCount) }}},
              {{{ makeGetValue('ptr', C_STRUCTS.WNNInput.dimensions, '*') }}}
          ),
        };
      }
    },

    makeTransposeOptions: function(ptr) {
      return {
        "permutation": WebNN.makeI32Array(
          {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNTransposeOptions.permutationCount) }}},
          {{{ makeGetValue('ptr', C_STRUCTS.WNNTransposeOptions.permutation, '*') }}}
        )
      };
    },

    makeResample2dOptions: function(ptr) {
      return {
        "mode": WebNN.InterpolationMode[
          {{{ webnn.makeGetI32('ptr', C_STRUCTS.WNNResample2dOptions.mode) }}}
        ],
        "scales": WebNN.makeF32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNResample2dOptions.scalesCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.WNNResample2dOptions.scales, '*') }}}
        ),
        "sizes": WebNN.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNResample2dOptions.sizesCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.WNNResample2dOptions.sizes, '*') }}}
        ),
        "axes": WebNN.makeI32Array(
            {{{ webnn.makeGetU32('ptr', C_STRUCTS.WNNResample2dOptions.axesCount) }}},
            {{{ makeGetValue('ptr', C_STRUCTS.WNNResample2dOptions.axes, '*') }}}
        ),
      };
    },

  },

  // *Reference/*Release

  {{{ webnn.makeReferenceRelease('Context') }}}
  {{{ webnn.makeReferenceRelease('FusionOperator') }}}
  {{{ webnn.makeReferenceRelease('Graph') }}}
  {{{ webnn.makeReferenceRelease('GraphBuilder') }}}
  {{{ webnn.makeReferenceRelease('Instance') }}}
  {{{ webnn.makeReferenceRelease('NamedInputs') }}}
  {{{ webnn.makeReferenceRelease('NamedOperands') }}}
  {{{ webnn.makeReferenceRelease('NamedOutputs') }}}
  {{{ webnn.makeReferenceRelease('Operand') }}}
  {{{ webnn.makeReferenceRelease('OperandArray') }}}
  {{{ webnn.makeReferenceRelease('OperatorArray') }}}

  // Methods of GraphBuilder
  wnnGraphBuilderAdd: function(builderId, aId, bId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder["add"](a, b);
    return WebNN.mgrOperand.create(c);
  },

  wnnGraphBuilderAveragePool2d: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makePool2dOptions(optionsPtr);
    var pool2d = builder["averagePool2d"](input, options);
    return WebNN.mgrOperand.create(pool2d);
  },

  wnnGraphBuilderBatchNorm: function(builderId, inputId, meanId, varianceId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var mean = WebNN.mgrOperand.get(meanId);
    var variance = WebNN.mgrOperand.get(varianceId);
    var options = WebNN.makeBatchNormOptions(optionsPtr);
    var output = builder["batchNormalization"](input, mean, variance, options);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderBuild: function(builderId, namedOperandsId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var namedOperands = WebNN.mgrNamedOperands.get(namedOperandsId);
    try {
      var graph = builder["buildSync"](namedOperands);
      return WebNN.mgrGraph.create(graph);
    } catch (error) {
      console.log('builder.build failed: ' + error);
      return 0;  // nullptr
    }
  },

  wnnGraphBuilderClamp: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeClampOptions(optionsPtr);
    var clamp = builder["clamp"](input, options);
    return WebNN.mgrOperand.create(clamp);
  },

  wnnGraphBuilderClampOperator: function(builderId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var options = WebNN.makeClampOptions(optionsPtr);
    var clamp = builder["clamp"](options);
    return WebNN.mgrFusionOperator.create(clamp);
  },

  wnnGraphBuilderConcat: function(builderId, inputsCount, inputsPtr, axis) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var inputIds = WebNN.makeI32Array(inputsCount, inputsPtr);
    var inputs = [];
    for (var i = 0; i < inputIds.length; ++i) {
      inputs.push(WebNN.mgrOperand.get(inputIds[i]));
    }
    var output = builder["concat"](inputs, axis);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderConstant: function(builderId, descPtr, arrayBufferViewPtr) {
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

  wnnGraphBuilderConv2d: function(builderId, inputId, filterId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var filter = WebNN.mgrOperand.get(filterId);
    var options = WebNN.makeConv2dOptions(optionsPtr);
    var conv2d = builder["conv2d"](input, filter, options);
    return WebNN.mgrOperand.create(conv2d);
  },

  wnnGraphBuilderConvTranspose2d: function(builderId, inputId, filterId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var filter = WebNN.mgrOperand.get(filterId);
    var options = WebNN.makeConvTranspose2dOptions(optionsPtr);
    var conv2d = builder["convTranspose2d"](input, filter, options);
    return WebNN.mgrOperand.create(conv2d);
  },

  wnnGraphBuilderDiv: function(builderId, aId, bId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder["div"](a, b);
    return WebNN.mgrOperand.create(c);
  },

  wnnGraphBuilderGemm: function(builderId, aId, bId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var options = WebNN.makeGemmOptions(optionsPtr);
    var output = builder["gemm"](a, b, options);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderGru: function(builderId, inputId, weightId, recurrentWeightId,
    steps, hiddenSize, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var weight = WebNN.mgrOperand.get(weightId);
    var recurrentWeight = WebNN.mgrOperand.get(recurrentWeightId);
    var options = WebNN.makeGruOptions(optionsPtr);
    var gru = builder["gru"](input, weight, recurrentWeight, steps, hiddenSize, options);
  return WebNN.mgrOperandArray.create(gru);
},

  wnnGraphBuilderInput: function(builderId, namePtr, descPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var name = UTF8ToString(namePtr);
    var desc = WebNN.makeOperandDescriptor(descPtr);
    var input = builder["input"](name, desc);
    return WebNN.mgrOperand.create(input);
  },

  wnnGraphBuilderHardSwish: function(builderId, inputId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var output = builder["hardSwish"](input);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderHardSwishOperator: function(builderId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var output = builder["hardSwish"]();
    return WebNN.mgrFusionOperator.create(output);
  },

  wnnGraphBuilderLeakyRelu: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeLeakyReluOptions(optionsPtr);
    var output = builder["leakyRelu"](input, options);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderLeakyReluOperator: function(builderId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var options = WebNN.makeLeakyReluOptions(optionsPtr);
    var output = builder["leakyRelu"](options);
    return WebNN.mgrFusionOperator.create(output);
  },

  wnnGraphBuilderMatmul: function(builderId, aId, bId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder["matmul"](a, b);
    return WebNN.mgrOperand.create(c);
  },

  wnnGraphBuilderMaxPool2d: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makePool2dOptions(optionsPtr);
    var pool2d = builder["maxPool2d"](input, options);
    return WebNN.mgrOperand.create(pool2d);
  },

  wnnGraphBuilderMul: function(builderId, aId, bId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder["mul"](a, b);
    return WebNN.mgrOperand.create(c);
  },

  wnnGraphBuilderPad: function(builderId, inputId, paddingId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var padding = WebNN.mgrOperand.get(paddingId);
    var options = WebNN.makePadOptions(optionsPtr);
    var output = builder["pad"](input, padding, options);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderReduceMean: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeReduceOptions(optionsPtr);
    var output = builder["reduceMean"](input, options);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderRelu: function(builderId, inputId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var output = builder["relu"](input);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderReluOperator: function(builderId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var output = builder["relu"]();
    return WebNN.mgrFusionOperator.create(output);
  },

  wnnGraphBuilderResample2d: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeResample2dOptions(optionsPtr);
    var output = builder["resample2d"](input, options);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderReshape: function(builderId, inputId, newShapePtr, newShapeCount) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var newShape = WebNN.makeI32Array(newShapeCount, newShapePtr);
    var output = builder["reshape"](input, newShape);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderSigmoid: function(builderId, inputId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var output = builder["sigmoid"](input);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderSigmoidOperator: function(builderId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var output = builder["sigmoid"]();
    return WebNN.mgrFusionOperator.create(output);
  },

  wnnGraphBuilderSoftmax: function(builderId, inputId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var output = builder["softmax"](input);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderSplit: function(builderId, inputId, splitsPtr, splitsCount, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var splits = WebNN.makeU32Array(splitsCount, splitsPtr);
    if (splitsCount == 1) splits = splits[0];
    var options = WebNN.makeSplitOptions(optionsPtr);
    var output = builder["split"](input, splits, options);
    return WebNN.mgrOperandArray.create(output);
  },

  wnnGraphBuilderSqueeze: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeSqueezeOptions(optionsPtr);
    var output = builder["squeeze"](input, options);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderSub: function(builderId, aId, bId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var a = WebNN.mgrOperand.get(aId);
    var b = WebNN.mgrOperand.get(bId);
    var c = builder["sub"](a, b);
    return WebNN.mgrOperand.create(c);
  },

  wnnGraphBuilderTanh: function(builderId, inputId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var output = builder["tanh"](input);
    return WebNN.mgrOperand.create(output);
  },

  wnnGraphBuilderTanhOperator: function(builderId) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var output = builder["tanh"]();
    return WebNN.mgrFusionOperator.create(output);
  },

  wnnGraphBuilderTranspose: function(builderId, inputId, optionsPtr) {
    var builder = WebNN.mgrGraphBuilder.get(builderId);
    var input = WebNN.mgrOperand.get(inputId);
    var options = WebNN.makeTransposeOptions(optionsPtr);
    var output = builder["transpose"](input, options);
    return WebNN.mgrOperand.create(output);
  },

  wnnOperandArrayGet: function(operandArrayId, indexId) {
    var operandArray = WebNN.mgrOperandArray.get(operandArrayId);
    var operand = operandArray[indexId];
    return WebNN.mgrOperand.create(operand);
  },

  wnnOperandArraySize: function(operandArrayId) {
    var operandArray = WebNN.mgrOperandArray.get(operandArrayId);
    return operandArray.length;
  },

  wnnOperatorArrayGet: function(operatorArrayId, indexId) {
    var operatorArray = WebNN.mgrOperatorArray.get(operatorArrayId);
    var operator = operatorArray[indexId];
    return WebNN.mgrFusionOperator.create(operator);
  },

  wnnOperatorArraySet: function(operatorArrayId, wnnOperatorId) {
    var operatorArray = WebNN.mgrOperatorArray.get(operatorArrayId);
    var wnnOperator = WebNN.mgrFusionOperator.get(wnnOperatorId);
    operatorArray.push(wnnOperator);
  },

  wnnOperatorArraySize: function(operatorArrayId) {
    var operatorArray = WebNN.mgrOperatorArray.get(operatorArrayId);
    return operatorArray.length;
  },

  webnnCreateOperatorArray: function() {
    var operatorArray = [];
    return WebNN.mgrOperatorArray.create(operatorArray);
  },

  webnnCreateNamedInputs: function() {
    var inputs = {};
    return WebNN.mgrNamedInputs.create(inputs);
  },

  wnnNamedInputsSet: function(namedInputsId, namePtr, inputPtr) {
    var namedInputs = WebNN.mgrNamedInputs.get(namedInputsId);
    var name = UTF8ToString(namePtr);
    var input = WebNN.makeInput(inputPtr);
    namedInputs[name] = input;
  },

  webnnCreateNamedOutputs: function() {
    var outputs = {};
    return WebNN.mgrNamedOutputs.create(outputs);
  },

  wnnNamedOutputsSet: function(namedOutputsId, namePtr, resourcePtr) {
    var namedOutputs = WebNN.mgrNamedOutputs.get(namedOutputsId);
    var name = UTF8ToString(namePtr);
    var output = WebNN.makeResource(resourcePtr);
    namedOutputs[name] = output;
  },

  webnnCreateNamedOperands: function() {
    var operands = {};
    return WebNN.mgrNamedOperands.create(operands);
  },

  wnnNamedOperandsSet: function(namedOperandsId, namePtr, operandId) {
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

  wnnContextComputeSync: function(contextId, graphId, inputsId, outputsId) {
    var context = WebNN.mgrContext.get(contextId);
    var graph = WebNN.mgrGraph.get(graphId);
    var inputs = WebNN.mgrNamedInputs.get(inputsId);
    var outputs = WebNN.mgrNamedOutputs.get(outputsId);
    context["computeSync"](graph, inputs, outputs)
  },
  
};

autoAddDeps(LibraryWebNN, '$WebNN');
mergeInto(LibraryManager.library, LibraryWebNN);
