// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef WEBNN_H_
#define WEBNN_H_

#if defined(WEBNN_SHARED_LIBRARY)
#    if defined(_WIN32)
#        if defined(WEBNN_IMPLEMENTATION)
#            define WEBNN_EXPORT __declspec(dllexport)
#        else
#            define WEBNN_EXPORT __declspec(dllimport)
#        endif
#    else  // defined(_WIN32)
#        if defined(WEBNN_IMPLEMENTATION)
#            define WEBNN_EXPORT __attribute__((visibility("default")))
#        else
#            define WEBNN_EXPORT
#        endif
#    endif  // defined(_WIN32)
#else       // defined(WEBNN_SHARED_LIBRARY)
#    define WEBNN_EXPORT
#endif  // defined(WEBNN_SHARED_LIBRARY)

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint32_t WEBNNFlags;

typedef struct WNNContextImpl* WNNContext;
typedef struct WNNFusionOperatorImpl* WNNFusionOperator;
typedef struct WNNGraphImpl* WNNGraph;
typedef struct WNNGraphBuilderImpl* WNNGraphBuilder;
typedef struct WNNInstanceImpl* WNNInstance;
typedef struct WNNNamedInputsImpl* WNNNamedInputs;
typedef struct WNNNamedOperandsImpl* WNNNamedOperands;
typedef struct WNNNamedOutputsImpl* WNNNamedOutputs;
typedef struct WNNOperandImpl* WNNOperand;
typedef struct WNNOperandArrayImpl* WNNOperandArray;
typedef struct WNNOperatorArrayImpl* WNNOperatorArray;

typedef enum WNNAutoPad {
    WNNAutoPad_Explicit = 0x00000000,
    WNNAutoPad_SameUpper = 0x00000001,
    WNNAutoPad_SameLower = 0x00000002,
    WNNAutoPad_Force32 = 0x7FFFFFFF
} WNNAutoPad;

typedef enum WNNBackendType {
    WNNBackendType_Null = 0x00000000,
    WNNBackendType_DirectML = 0x00000001,
    WNNBackendType_OpenVINO = 0x00000002,
    WNNBackendType_OneDNN = 0x00000003,
    WNNBackendType_MLAS = 0x00000004,
    WNNBackendType_Force32 = 0x7FFFFFFF
} WNNBackendType;

typedef enum WNNConvTranspose2dFilterOperandLayout {
    WNNConvTranspose2dFilterOperandLayout_Iohw = 0x00000000,
    WNNConvTranspose2dFilterOperandLayout_Hwoi = 0x00000001,
    WNNConvTranspose2dFilterOperandLayout_Ohwi = 0x00000002,
    WNNConvTranspose2dFilterOperandLayout_Force32 = 0x7FFFFFFF
} WNNConvTranspose2dFilterOperandLayout;

typedef enum WNNConv2dFilterOperandLayout {
    WNNConv2dFilterOperandLayout_Oihw = 0x00000000,
    WNNConv2dFilterOperandLayout_Hwio = 0x00000001,
    WNNConv2dFilterOperandLayout_Ohwi = 0x00000002,
    WNNConv2dFilterOperandLayout_Ihwo = 0x00000003,
    WNNConv2dFilterOperandLayout_Force32 = 0x7FFFFFFF
} WNNConv2dFilterOperandLayout;

typedef enum WNNDevicePreference {
    WNNDevicePreference_Default = 0x00000000,
    WNNDevicePreference_Gpu = 0x00000001,
    WNNDevicePreference_Cpu = 0x00000002,
    WNNDevicePreference_Force32 = 0x7FFFFFFF
} WNNDevicePreference;

typedef enum WNNErrorFilter {
    WNNErrorFilter_None = 0x00000000,
    WNNErrorFilter_Validation = 0x00000001,
    WNNErrorFilter_OutOfMemory = 0x00000002,
    WNNErrorFilter_Force32 = 0x7FFFFFFF
} WNNErrorFilter;

typedef enum WNNErrorType {
    WNNErrorType_NoError = 0x00000000,
    WNNErrorType_Validation = 0x00000001,
    WNNErrorType_OutOfMemory = 0x00000002,
    WNNErrorType_Unknown = 0x00000003,
    WNNErrorType_DeviceLost = 0x00000004,
    WNNErrorType_Force32 = 0x7FFFFFFF
} WNNErrorType;

typedef enum WNNInputOperandLayout {
    WNNInputOperandLayout_Nchw = 0x00000000,
    WNNInputOperandLayout_Nhwc = 0x00000001,
    WNNInputOperandLayout_Force32 = 0x7FFFFFFF
} WNNInputOperandLayout;

typedef enum WNNInterpolationMode {
    WNNInterpolationMode_NearestNeighbor = 0x00000000,
    WNNInterpolationMode_Linear = 0x00000001,
    WNNInterpolationMode_Force32 = 0x7FFFFFFF
} WNNInterpolationMode;

typedef enum WNNOperandType {
    WNNOperandType_Float32 = 0x00000000,
    WNNOperandType_Float16 = 0x00000001,
    WNNOperandType_Int32 = 0x00000002,
    WNNOperandType_Uint32 = 0x00000003,
    WNNOperandType_Int8 = 0x00000004,
    WNNOperandType_Uint8 = 0x00000005,
    WNNOperandType_Force32 = 0x7FFFFFFF
} WNNOperandType;

typedef enum WNNPaddingMode {
    WNNPaddingMode_Constant = 0x00000000,
    WNNPaddingMode_Edge = 0x00000001,
    WNNPaddingMode_Reflection = 0x00000002,
    WNNPaddingMode_Symmetric = 0x00000003,
    WNNPaddingMode_Force32 = 0x7FFFFFFF
} WNNPaddingMode;

typedef enum WNNPowerPreference {
    WNNPowerPreference_Default = 0x00000000,
    WNNPowerPreference_High_performance = 0x00000001,
    WNNPowerPreference_Low_power = 0x00000002,
    WNNPowerPreference_Force32 = 0x7FFFFFFF
} WNNPowerPreference;

typedef enum WNNRecurrentNetworkDirection {
    WNNRecurrentNetworkDirection_Forward = 0x00000000,
    WNNRecurrentNetworkDirection_Backward = 0x00000001,
    WNNRecurrentNetworkDirection_Both = 0x00000002,
    WNNRecurrentNetworkDirection_Force32 = 0x7FFFFFFF
} WNNRecurrentNetworkDirection;

typedef enum WNNRecurrentNetworkWeightLayout {
    WNNRecurrentNetworkWeightLayout_Zrn = 0x00000000,
    WNNRecurrentNetworkWeightLayout_Rzn = 0x00000001,
    WNNRecurrentNetworkWeightLayout_Force32 = 0x7FFFFFFF
} WNNRecurrentNetworkWeightLayout;

typedef enum WNNRoundingType {
    WNNRoundingType_Floor = 0x00000000,
    WNNRoundingType_Ceil = 0x00000001,
    WNNRoundingType_Force32 = 0x7FFFFFFF
} WNNRoundingType;


typedef struct WNNArrayBufferView {
    void * buffer;
    size_t byteLength;
    size_t byteOffset;
} WNNArrayBufferView;

typedef struct WNNBatchNormOptions {
    WNNOperand scale;
    WNNOperand bias;
    uint32_t axis;
    float epsilon;
    WNNFusionOperator activation;
} WNNBatchNormOptions;

typedef struct WNNClampOptions {
    float minValue;
    float maxValue;
} WNNClampOptions;

typedef struct WNNContextOptions {
    WNNDevicePreference devicePreference;
    WNNPowerPreference powerPreference;
} WNNContextOptions;

typedef struct WNNConvTranspose2dOptions {
    uint32_t paddingCount;
    int32_t const * padding;
    uint32_t stridesCount;
    int32_t const * strides;
    uint32_t dilationsCount;
    int32_t const * dilations;
    uint32_t outputPaddingCount;
    int32_t const * outputPadding;
    uint32_t outputSizesCount;
    int32_t const * outputSizes;
    WNNAutoPad autoPad;
    int32_t groups;
    WNNInputOperandLayout inputLayout;
    WNNConvTranspose2dFilterOperandLayout filterLayout;
    WNNOperand bias;
    WNNFusionOperator activation;
} WNNConvTranspose2dOptions;

typedef struct WNNConv2dOptions {
    uint32_t paddingCount;
    int32_t const * padding;
    uint32_t stridesCount;
    int32_t const * strides;
    uint32_t dilationsCount;
    int32_t const * dilations;
    WNNAutoPad autoPad;
    int32_t groups;
    WNNInputOperandLayout inputLayout;
    WNNConv2dFilterOperandLayout filterLayout;
    WNNOperand bias;
    WNNFusionOperator activation;
} WNNConv2dOptions;

typedef struct WNNGemmOptions {
    WNNOperand c;
    float alpha;
    float beta;
    bool aTranspose;
    bool bTranspose;
} WNNGemmOptions;

typedef struct WNNGpuBufferView {
    void * buffer;
    uint32_t id;
    uint32_t generation;
    size_t size;
    size_t offset;
} WNNGpuBufferView;

typedef struct WNNGpuDevice {
    void * device;
    uint32_t id;
    uint32_t generation;
} WNNGpuDevice;

typedef struct WNNGruOptions {
    WNNOperand bias;
    WNNOperand recurrentBias;
    WNNOperand initialHiddenState;
    bool resetAfter;
    bool returnSequence;
    WNNRecurrentNetworkDirection direction;
    WNNRecurrentNetworkWeightLayout layout;
    WNNOperatorArray activations;
} WNNGruOptions;

typedef struct WNNInstanceDescriptor {
} WNNInstanceDescriptor;

typedef struct WNNInstanceNormOptions {
    WNNOperand scale;
    WNNOperand bias;
    float epsilon;
    WNNInputOperandLayout layout;
} WNNInstanceNormOptions;

typedef struct WNNLeakyReluOptions {
    float alpha;
} WNNLeakyReluOptions;

typedef struct WNNOperandDescriptor {
    WNNOperandType type;
    int32_t const * dimensions;
    uint32_t dimensionsCount;
} WNNOperandDescriptor;

typedef struct WNNPadOptions {
    WNNPaddingMode mode;
    float value;
} WNNPadOptions;

typedef struct WNNPool2dOptions {
    uint32_t windowDimensionsCount;
    int32_t const * windowDimensions;
    uint32_t paddingCount;
    int32_t const * padding;
    uint32_t stridesCount;
    int32_t const * strides;
    uint32_t dilationsCount;
    int32_t const * dilations;
    WNNAutoPad autoPad;
    WNNInputOperandLayout layout;
    WNNRoundingType roundingType;
    uint32_t outputSizesCount;
    int32_t const * outputSizes;
} WNNPool2dOptions;

typedef struct WNNReduceOptions {
    uint32_t axesCount;
    int32_t const * axes;
    bool keepDimensions;
} WNNReduceOptions;

typedef struct WNNResample2dOptions {
    WNNInterpolationMode mode;
    uint32_t scalesCount;
    float const * scales;
    uint32_t sizesCount;
    int32_t const * sizes;
    uint32_t axesCount;
    int32_t const * axes;
} WNNResample2dOptions;

typedef struct WNNSliceOptions {
    uint32_t axesCount;
    int32_t const * axes;
} WNNSliceOptions;

typedef struct WNNSplitOptions {
    int32_t axis;
} WNNSplitOptions;

typedef struct WNNSqueezeOptions {
    uint32_t axesCount;
    int32_t const * axes;
} WNNSqueezeOptions;

typedef struct WNNTransposeOptions {
    uint32_t permutationCount;
    int32_t const * permutation;
} WNNTransposeOptions;

typedef struct WNNResource {
    WNNArrayBufferView arrayBufferView;
    WNNGpuBufferView gpuBufferView;
} WNNResource;

typedef struct WNNInput {
    WNNResource resource;
    int32_t const * dimensions;
    uint32_t dimensionsCount;
} WNNInput;


#ifdef __cplusplus
extern "C" {
#endif

typedef void (*WNNComputeAsyncCallback)(WNNErrorType type, char const * message, void * userdata);
typedef void (*WNNErrorCallback)(WNNErrorType type, char const * message, void * userdata);

typedef void (*WebnnProc)(void);

#if !defined(WEBNN_SKIP_PROCS)

typedef WNNGraphBuilder (*WebnnProcCreateGraphBuilder)(WNNContext context);
typedef WNNNamedInputs (*WebnnProcCreateNamedInputs)();
typedef WNNNamedOperands (*WebnnProcCreateNamedOperands)();
typedef WNNNamedOutputs (*WebnnProcCreateNamedOutputs)();
typedef WNNOperatorArray (*WebnnProcCreateOperatorArray)();

// Procs of Context
typedef void (*WebnnProcContextInjectError)(WNNContext context, WNNErrorType type, char const * message);
typedef bool (*WebnnProcContextPopErrorScope)(WNNContext context, WNNErrorCallback callback, void * userdata);
typedef void (*WebnnProcContextPushErrorScope)(WNNContext context, WNNErrorFilter filter);
typedef void (*WebnnProcContextSetUncapturedErrorCallback)(WNNContext context, WNNErrorCallback callback, void * userdata);
typedef void (*WebnnProcContextReference)(WNNContext context);
typedef void (*WebnnProcContextRelease)(WNNContext context);

// Procs of FusionOperator
typedef void (*WebnnProcFusionOperatorReference)(WNNFusionOperator fusionOperator);
typedef void (*WebnnProcFusionOperatorRelease)(WNNFusionOperator fusionOperator);

// Procs of Graph
typedef void (*WebnnProcGraphCompute)(WNNGraph graph, WNNNamedInputs inputs, WNNNamedOutputs outputs);
typedef void (*WebnnProcGraphComputeAsync)(WNNGraph graph, WNNNamedInputs inputs, WNNNamedOutputs outputs, WNNComputeAsyncCallback callback, void * userdata);
typedef void (*WebnnProcGraphReference)(WNNGraph graph);
typedef void (*WebnnProcGraphRelease)(WNNGraph graph);

// Procs of GraphBuilder
typedef WNNOperand (*WebnnProcGraphBuilderAbs)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNOperand (*WebnnProcGraphBuilderAdd)(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
typedef WNNOperand (*WebnnProcGraphBuilderAveragePool2d)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNPool2dOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderBatchNorm)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNOperand mean, WNNOperand variance, WNNBatchNormOptions const * options);
typedef WNNGraph (*WebnnProcGraphBuilderBuild)(WNNGraphBuilder graphBuilder, WNNNamedOperands namedOperands);
typedef WNNOperand (*WebnnProcGraphBuilderCeil)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNOperand (*WebnnProcGraphBuilderClamp)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNClampOptions const * options);
typedef WNNFusionOperator (*WebnnProcGraphBuilderClampOperator)(WNNGraphBuilder graphBuilder, WNNClampOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderConcat)(WNNGraphBuilder graphBuilder, uint32_t inputsCount, WNNOperand const * inputs, uint32_t axis);
typedef WNNOperand (*WebnnProcGraphBuilderConstant)(WNNGraphBuilder graphBuilder, WNNOperandDescriptor const * desc, WNNArrayBufferView const * value);
typedef WNNOperand (*WebnnProcGraphBuilderConstantWithGpuBuffer)(WNNGraphBuilder graphBuilder, WNNOperandDescriptor const * desc, WNNGpuBufferView const * value);
typedef WNNOperand (*WebnnProcGraphBuilderConvTranspose2d)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNOperand filter, WNNConvTranspose2dOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderConv2d)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNOperand filter, WNNConv2dOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderCos)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNOperand (*WebnnProcGraphBuilderDiv)(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
typedef WNNOperand (*WebnnProcGraphBuilderExp)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNOperand (*WebnnProcGraphBuilderFloor)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNOperand (*WebnnProcGraphBuilderGemm)(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b, WNNGemmOptions const * options);
typedef WNNOperandArray (*WebnnProcGraphBuilderGru)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNOperand weight, WNNOperand recurrentWeight, int32_t steps, int32_t hiddenSize, WNNGruOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderHardSwish)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNFusionOperator (*WebnnProcGraphBuilderHardSwishOperator)(WNNGraphBuilder graphBuilder);
typedef WNNOperand (*WebnnProcGraphBuilderInput)(WNNGraphBuilder graphBuilder, char const * name, WNNOperandDescriptor const * desc);
typedef WNNOperand (*WebnnProcGraphBuilderInstanceNorm)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNInstanceNormOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderL2Pool2d)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNPool2dOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderLeakyRelu)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNLeakyReluOptions const * options);
typedef WNNFusionOperator (*WebnnProcGraphBuilderLeakyReluOperator)(WNNGraphBuilder graphBuilder, WNNLeakyReluOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderLog)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNOperand (*WebnnProcGraphBuilderMatmul)(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
typedef WNNOperand (*WebnnProcGraphBuilderMax)(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
typedef WNNOperand (*WebnnProcGraphBuilderMaxPool2d)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNPool2dOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderMin)(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
typedef WNNOperand (*WebnnProcGraphBuilderMul)(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
typedef WNNOperand (*WebnnProcGraphBuilderNeg)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNOperand (*WebnnProcGraphBuilderPad)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNOperand padding, WNNPadOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderPow)(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
typedef WNNOperand (*WebnnProcGraphBuilderReduceArgMax)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderReduceArgMin)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderReduceL1)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderReduceL2)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderReduceMax)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderReduceMean)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderReduceMin)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderReduceProduct)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderReduceSum)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderRelu)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNFusionOperator (*WebnnProcGraphBuilderReluOperator)(WNNGraphBuilder graphBuilder);
typedef WNNOperand (*WebnnProcGraphBuilderResample2d)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNResample2dOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderReshape)(WNNGraphBuilder graphBuilder, WNNOperand input, int32_t const * newShape, uint32_t newShapeCount);
typedef WNNOperand (*WebnnProcGraphBuilderSigmoid)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNFusionOperator (*WebnnProcGraphBuilderSigmoidOperator)(WNNGraphBuilder graphBuilder);
typedef WNNOperand (*WebnnProcGraphBuilderSin)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNOperand (*WebnnProcGraphBuilderSlice)(WNNGraphBuilder graphBuilder, WNNOperand input, int32_t const * starts, uint32_t startsCount, int32_t const * sizes, uint32_t sizesCount, WNNSliceOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderSoftmax)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNOperandArray (*WebnnProcGraphBuilderSplit)(WNNGraphBuilder graphBuilder, WNNOperand input, uint32_t const * splits, uint32_t splitsCount, WNNSplitOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderSqueeze)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNSqueezeOptions const * options);
typedef WNNOperand (*WebnnProcGraphBuilderSub)(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
typedef WNNOperand (*WebnnProcGraphBuilderTan)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNOperand (*WebnnProcGraphBuilderTanh)(WNNGraphBuilder graphBuilder, WNNOperand input);
typedef WNNFusionOperator (*WebnnProcGraphBuilderTanhOperator)(WNNGraphBuilder graphBuilder);
typedef WNNOperand (*WebnnProcGraphBuilderTranspose)(WNNGraphBuilder graphBuilder, WNNOperand input, WNNTransposeOptions const * options);
typedef void (*WebnnProcGraphBuilderReference)(WNNGraphBuilder graphBuilder);
typedef void (*WebnnProcGraphBuilderRelease)(WNNGraphBuilder graphBuilder);

// Procs of Instance
typedef WNNContext (*WebnnProcInstanceCreateContext)(WNNInstance instance, WNNContextOptions const * options);
typedef WNNContext (*WebnnProcInstanceCreateContextWithGpuDevice)(WNNInstance instance, WNNGpuDevice const * gpuDevice);
typedef WNNGraphBuilder (*WebnnProcInstanceCreateGraphBuilder)(WNNInstance instance, WNNContext context);
typedef WNNNamedInputs (*WebnnProcInstanceCreateNamedInputs)(WNNInstance instance);
typedef WNNNamedOperands (*WebnnProcInstanceCreateNamedOperands)(WNNInstance instance);
typedef WNNNamedOutputs (*WebnnProcInstanceCreateNamedOutputs)(WNNInstance instance);
typedef WNNOperatorArray (*WebnnProcInstanceCreateOperatorArray)(WNNInstance instance);
typedef void (*WebnnProcInstanceReference)(WNNInstance instance);
typedef void (*WebnnProcInstanceRelease)(WNNInstance instance);

// Procs of NamedInputs
typedef void (*WebnnProcNamedInputsSet)(WNNNamedInputs namedInputs, char const * name, WNNInput const * input);
typedef void (*WebnnProcNamedInputsReference)(WNNNamedInputs namedInputs);
typedef void (*WebnnProcNamedInputsRelease)(WNNNamedInputs namedInputs);

// Procs of NamedOperands
typedef void (*WebnnProcNamedOperandsSet)(WNNNamedOperands namedOperands, char const * name, WNNOperand operand);
typedef void (*WebnnProcNamedOperandsReference)(WNNNamedOperands namedOperands);
typedef void (*WebnnProcNamedOperandsRelease)(WNNNamedOperands namedOperands);

// Procs of NamedOutputs
typedef void (*WebnnProcNamedOutputsGet)(WNNNamedOutputs namedOutputs, char const * name, WNNArrayBufferView * resource);
typedef void (*WebnnProcNamedOutputsSet)(WNNNamedOutputs namedOutputs, char const * name, WNNResource const * resource);
typedef void (*WebnnProcNamedOutputsReference)(WNNNamedOutputs namedOutputs);
typedef void (*WebnnProcNamedOutputsRelease)(WNNNamedOutputs namedOutputs);

// Procs of Operand
typedef void (*WebnnProcOperandReference)(WNNOperand operand);
typedef void (*WebnnProcOperandRelease)(WNNOperand operand);

// Procs of OperandArray
typedef WNNOperand (*WebnnProcOperandArrayGet)(WNNOperandArray operandArray, size_t index);
typedef size_t (*WebnnProcOperandArraySize)(WNNOperandArray operandArray);
typedef void (*WebnnProcOperandArrayReference)(WNNOperandArray operandArray);
typedef void (*WebnnProcOperandArrayRelease)(WNNOperandArray operandArray);

// Procs of OperatorArray
typedef WNNFusionOperator (*WebnnProcOperatorArrayGet)(WNNOperatorArray operatorArray, size_t index);
typedef void (*WebnnProcOperatorArraySet)(WNNOperatorArray operatorArray, WNNFusionOperator wnnOperator);
typedef size_t (*WebnnProcOperatorArraySize)(WNNOperatorArray operatorArray);
typedef void (*WebnnProcOperatorArrayReference)(WNNOperatorArray operatorArray);
typedef void (*WebnnProcOperatorArrayRelease)(WNNOperatorArray operatorArray);

#endif  // !defined(WEBNN_SKIP_PROCS)

#if !defined(WEBNN_SKIP_DECLARATIONS)

WEBNN_EXPORT WNNGraphBuilder webnnCreateGraphBuilder(WNNContext context);
WEBNN_EXPORT WNNNamedInputs webnnCreateNamedInputs();
WEBNN_EXPORT WNNNamedOperands webnnCreateNamedOperands();
WEBNN_EXPORT WNNNamedOutputs webnnCreateNamedOutputs();
WEBNN_EXPORT WNNOperatorArray webnnCreateOperatorArray();

// Methods of Context
WEBNN_EXPORT void wnnContextInjectError(WNNContext context, WNNErrorType type, char const * message);
WEBNN_EXPORT bool wnnContextPopErrorScope(WNNContext context, WNNErrorCallback callback, void * userdata);
WEBNN_EXPORT void wnnContextPushErrorScope(WNNContext context, WNNErrorFilter filter);
WEBNN_EXPORT void wnnContextSetUncapturedErrorCallback(WNNContext context, WNNErrorCallback callback, void * userdata);
WEBNN_EXPORT void wnnContextReference(WNNContext context);
WEBNN_EXPORT void wnnContextRelease(WNNContext context);

// Methods of FusionOperator
WEBNN_EXPORT void wnnFusionOperatorReference(WNNFusionOperator fusionOperator);
WEBNN_EXPORT void wnnFusionOperatorRelease(WNNFusionOperator fusionOperator);

// Methods of Graph
WEBNN_EXPORT void wnnGraphCompute(WNNGraph graph, WNNNamedInputs inputs, WNNNamedOutputs outputs);
WEBNN_EXPORT void wnnGraphComputeAsync(WNNGraph graph, WNNNamedInputs inputs, WNNNamedOutputs outputs, WNNComputeAsyncCallback callback, void * userdata);
WEBNN_EXPORT void wnnGraphReference(WNNGraph graph);
WEBNN_EXPORT void wnnGraphRelease(WNNGraph graph);

// Methods of GraphBuilder
WEBNN_EXPORT WNNOperand wnnGraphBuilderAbs(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNOperand wnnGraphBuilderAdd(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
WEBNN_EXPORT WNNOperand wnnGraphBuilderAveragePool2d(WNNGraphBuilder graphBuilder, WNNOperand input, WNNPool2dOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderBatchNorm(WNNGraphBuilder graphBuilder, WNNOperand input, WNNOperand mean, WNNOperand variance, WNNBatchNormOptions const * options);
WEBNN_EXPORT WNNGraph wnnGraphBuilderBuild(WNNGraphBuilder graphBuilder, WNNNamedOperands namedOperands);
WEBNN_EXPORT WNNOperand wnnGraphBuilderCeil(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNOperand wnnGraphBuilderClamp(WNNGraphBuilder graphBuilder, WNNOperand input, WNNClampOptions const * options);
WEBNN_EXPORT WNNFusionOperator wnnGraphBuilderClampOperator(WNNGraphBuilder graphBuilder, WNNClampOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderConcat(WNNGraphBuilder graphBuilder, uint32_t inputsCount, WNNOperand const * inputs, uint32_t axis);
WEBNN_EXPORT WNNOperand wnnGraphBuilderConstant(WNNGraphBuilder graphBuilder, WNNOperandDescriptor const * desc, WNNArrayBufferView const * value);
WEBNN_EXPORT WNNOperand wnnGraphBuilderConstantWithGpuBuffer(WNNGraphBuilder graphBuilder, WNNOperandDescriptor const * desc, WNNGpuBufferView const * value);
WEBNN_EXPORT WNNOperand wnnGraphBuilderConvTranspose2d(WNNGraphBuilder graphBuilder, WNNOperand input, WNNOperand filter, WNNConvTranspose2dOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderConv2d(WNNGraphBuilder graphBuilder, WNNOperand input, WNNOperand filter, WNNConv2dOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderCos(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNOperand wnnGraphBuilderDiv(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
WEBNN_EXPORT WNNOperand wnnGraphBuilderExp(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNOperand wnnGraphBuilderFloor(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNOperand wnnGraphBuilderGemm(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b, WNNGemmOptions const * options);
WEBNN_EXPORT WNNOperandArray wnnGraphBuilderGru(WNNGraphBuilder graphBuilder, WNNOperand input, WNNOperand weight, WNNOperand recurrentWeight, int32_t steps, int32_t hiddenSize, WNNGruOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderHardSwish(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNFusionOperator wnnGraphBuilderHardSwishOperator(WNNGraphBuilder graphBuilder);
WEBNN_EXPORT WNNOperand wnnGraphBuilderInput(WNNGraphBuilder graphBuilder, char const * name, WNNOperandDescriptor const * desc);
WEBNN_EXPORT WNNOperand wnnGraphBuilderInstanceNorm(WNNGraphBuilder graphBuilder, WNNOperand input, WNNInstanceNormOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderL2Pool2d(WNNGraphBuilder graphBuilder, WNNOperand input, WNNPool2dOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderLeakyRelu(WNNGraphBuilder graphBuilder, WNNOperand input, WNNLeakyReluOptions const * options);
WEBNN_EXPORT WNNFusionOperator wnnGraphBuilderLeakyReluOperator(WNNGraphBuilder graphBuilder, WNNLeakyReluOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderLog(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNOperand wnnGraphBuilderMatmul(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
WEBNN_EXPORT WNNOperand wnnGraphBuilderMax(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
WEBNN_EXPORT WNNOperand wnnGraphBuilderMaxPool2d(WNNGraphBuilder graphBuilder, WNNOperand input, WNNPool2dOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderMin(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
WEBNN_EXPORT WNNOperand wnnGraphBuilderMul(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
WEBNN_EXPORT WNNOperand wnnGraphBuilderNeg(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNOperand wnnGraphBuilderPad(WNNGraphBuilder graphBuilder, WNNOperand input, WNNOperand padding, WNNPadOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderPow(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
WEBNN_EXPORT WNNOperand wnnGraphBuilderReduceArgMax(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderReduceArgMin(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderReduceL1(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderReduceL2(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderReduceMax(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderReduceMean(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderReduceMin(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderReduceProduct(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderReduceSum(WNNGraphBuilder graphBuilder, WNNOperand input, WNNReduceOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderRelu(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNFusionOperator wnnGraphBuilderReluOperator(WNNGraphBuilder graphBuilder);
WEBNN_EXPORT WNNOperand wnnGraphBuilderResample2d(WNNGraphBuilder graphBuilder, WNNOperand input, WNNResample2dOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderReshape(WNNGraphBuilder graphBuilder, WNNOperand input, int32_t const * newShape, uint32_t newShapeCount);
WEBNN_EXPORT WNNOperand wnnGraphBuilderSigmoid(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNFusionOperator wnnGraphBuilderSigmoidOperator(WNNGraphBuilder graphBuilder);
WEBNN_EXPORT WNNOperand wnnGraphBuilderSin(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNOperand wnnGraphBuilderSlice(WNNGraphBuilder graphBuilder, WNNOperand input, int32_t const * starts, uint32_t startsCount, int32_t const * sizes, uint32_t sizesCount, WNNSliceOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderSoftmax(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNOperandArray wnnGraphBuilderSplit(WNNGraphBuilder graphBuilder, WNNOperand input, uint32_t const * splits, uint32_t splitsCount, WNNSplitOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderSqueeze(WNNGraphBuilder graphBuilder, WNNOperand input, WNNSqueezeOptions const * options);
WEBNN_EXPORT WNNOperand wnnGraphBuilderSub(WNNGraphBuilder graphBuilder, WNNOperand a, WNNOperand b);
WEBNN_EXPORT WNNOperand wnnGraphBuilderTan(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNOperand wnnGraphBuilderTanh(WNNGraphBuilder graphBuilder, WNNOperand input);
WEBNN_EXPORT WNNFusionOperator wnnGraphBuilderTanhOperator(WNNGraphBuilder graphBuilder);
WEBNN_EXPORT WNNOperand wnnGraphBuilderTranspose(WNNGraphBuilder graphBuilder, WNNOperand input, WNNTransposeOptions const * options);
WEBNN_EXPORT void wnnGraphBuilderReference(WNNGraphBuilder graphBuilder);
WEBNN_EXPORT void wnnGraphBuilderRelease(WNNGraphBuilder graphBuilder);

// Methods of Instance
WEBNN_EXPORT WNNContext wnnInstanceCreateContext(WNNInstance instance, WNNContextOptions const * options);
WEBNN_EXPORT WNNContext wnnInstanceCreateContextWithGpuDevice(WNNInstance instance, WNNGpuDevice const * gpuDevice);
WEBNN_EXPORT WNNGraphBuilder wnnInstanceCreateGraphBuilder(WNNInstance instance, WNNContext context);
WEBNN_EXPORT WNNNamedInputs wnnInstanceCreateNamedInputs(WNNInstance instance);
WEBNN_EXPORT WNNNamedOperands wnnInstanceCreateNamedOperands(WNNInstance instance);
WEBNN_EXPORT WNNNamedOutputs wnnInstanceCreateNamedOutputs(WNNInstance instance);
WEBNN_EXPORT WNNOperatorArray wnnInstanceCreateOperatorArray(WNNInstance instance);
WEBNN_EXPORT void wnnInstanceReference(WNNInstance instance);
WEBNN_EXPORT void wnnInstanceRelease(WNNInstance instance);

// Methods of NamedInputs
WEBNN_EXPORT void wnnNamedInputsSet(WNNNamedInputs namedInputs, char const * name, WNNInput const * input);
WEBNN_EXPORT void wnnNamedInputsReference(WNNNamedInputs namedInputs);
WEBNN_EXPORT void wnnNamedInputsRelease(WNNNamedInputs namedInputs);

// Methods of NamedOperands
WEBNN_EXPORT void wnnNamedOperandsSet(WNNNamedOperands namedOperands, char const * name, WNNOperand operand);
WEBNN_EXPORT void wnnNamedOperandsReference(WNNNamedOperands namedOperands);
WEBNN_EXPORT void wnnNamedOperandsRelease(WNNNamedOperands namedOperands);

// Methods of NamedOutputs
WEBNN_EXPORT void wnnNamedOutputsGet(WNNNamedOutputs namedOutputs, char const * name, WNNArrayBufferView * resource);
WEBNN_EXPORT void wnnNamedOutputsSet(WNNNamedOutputs namedOutputs, char const * name, WNNResource const * resource);
WEBNN_EXPORT void wnnNamedOutputsReference(WNNNamedOutputs namedOutputs);
WEBNN_EXPORT void wnnNamedOutputsRelease(WNNNamedOutputs namedOutputs);

// Methods of Operand
WEBNN_EXPORT void wnnOperandReference(WNNOperand operand);
WEBNN_EXPORT void wnnOperandRelease(WNNOperand operand);

// Methods of OperandArray
WEBNN_EXPORT WNNOperand wnnOperandArrayGet(WNNOperandArray operandArray, size_t index);
WEBNN_EXPORT size_t wnnOperandArraySize(WNNOperandArray operandArray);
WEBNN_EXPORT void wnnOperandArrayReference(WNNOperandArray operandArray);
WEBNN_EXPORT void wnnOperandArrayRelease(WNNOperandArray operandArray);

// Methods of OperatorArray
WEBNN_EXPORT WNNFusionOperator wnnOperatorArrayGet(WNNOperatorArray operatorArray, size_t index);
WEBNN_EXPORT void wnnOperatorArraySet(WNNOperatorArray operatorArray, WNNFusionOperator wnnOperator);
WEBNN_EXPORT size_t wnnOperatorArraySize(WNNOperatorArray operatorArray);
WEBNN_EXPORT void wnnOperatorArrayReference(WNNOperatorArray operatorArray);
WEBNN_EXPORT void wnnOperatorArrayRelease(WNNOperatorArray operatorArray);

#endif  // !defined(WEBNN_SKIP_DECLARATIONS)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WEBNN_H_
