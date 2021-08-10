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

typedef struct MLContextImpl* MLContext;
typedef struct MLGraphImpl* MLGraph;
typedef struct MLGraphBuilderImpl* MLGraphBuilder;
typedef struct MLNamedInputsImpl* MLNamedInputs;
typedef struct MLNamedOperandsImpl* MLNamedOperands;
typedef struct MLNamedOutputsImpl* MLNamedOutputs;
typedef struct MLOperandImpl* MLOperand;
typedef struct MLOperatorImpl* MLOperator;

typedef enum MLAutoPad {
    MLAutoPad_Explicit = 0x00000000,
    MLAutoPad_SameUpper = 0x00000001,
    MLAutoPad_SameLower = 0x00000002,
    MLAutoPad_Force32 = 0x7FFFFFFF
} MLAutoPad;

typedef enum MLComputeGraphStatus {
    MLComputeGraphStatus_Success = 0x00000000,
    MLComputeGraphStatus_Error = 0x00000001,
    MLComputeGraphStatus_ContextLost = 0x00000002,
    MLComputeGraphStatus_Unknown = 0x00000003,
    MLComputeGraphStatus_Force32 = 0x7FFFFFFF
} MLComputeGraphStatus;

typedef enum MLDevicePreference {
    MLDevicePreference_Default = 0x00000000,
    MLDevicePreference_Gpu = 0x00000001,
    MLDevicePreference_Cpu = 0x00000002,
    MLDevicePreference_Force32 = 0x7FFFFFFF
} MLDevicePreference;

typedef enum MLErrorFilter {
    MLErrorFilter_None = 0x00000000,
    MLErrorFilter_Validation = 0x00000001,
    MLErrorFilter_OutOfMemory = 0x00000002,
    MLErrorFilter_Force32 = 0x7FFFFFFF
} MLErrorFilter;

typedef enum MLErrorType {
    MLErrorType_NoError = 0x00000000,
    MLErrorType_Validation = 0x00000001,
    MLErrorType_OutOfMemory = 0x00000002,
    MLErrorType_Unknown = 0x00000003,
    MLErrorType_DeviceLost = 0x00000004,
    MLErrorType_Force32 = 0x7FFFFFFF
} MLErrorType;

typedef enum MLFilterOperandLayout {
    MLFilterOperandLayout_Oihw = 0x00000000,
    MLFilterOperandLayout_Hwio = 0x00000001,
    MLFilterOperandLayout_Ohwi = 0x00000002,
    MLFilterOperandLayout_Ihwo = 0x00000003,
    MLFilterOperandLayout_Force32 = 0x7FFFFFFF
} MLFilterOperandLayout;

typedef enum MLInputOperandLayout {
    MLInputOperandLayout_Nchw = 0x00000000,
    MLInputOperandLayout_Nhwc = 0x00000001,
    MLInputOperandLayout_Force32 = 0x7FFFFFFF
} MLInputOperandLayout;

typedef enum MLInterpolationMode {
    MLInterpolationMode_NearestNeighbor = 0x00000000,
    MLInterpolationMode_Linear = 0x00000001,
    MLInterpolationMode_Force32 = 0x7FFFFFFF
} MLInterpolationMode;

typedef enum MLOperandType {
    MLOperandType_Float32 = 0x00000000,
    MLOperandType_Float16 = 0x00000001,
    MLOperandType_Int32 = 0x00000002,
    MLOperandType_Uint32 = 0x00000003,
    MLOperandType_Int8 = 0x00000004,
    MLOperandType_Uint8 = 0x00000005,
    MLOperandType_Force32 = 0x7FFFFFFF
} MLOperandType;

typedef enum MLPaddingMode {
    MLPaddingMode_Constant = 0x00000000,
    MLPaddingMode_Edge = 0x00000001,
    MLPaddingMode_Reflection = 0x00000002,
    MLPaddingMode_Symmetric = 0x00000003,
    MLPaddingMode_Force32 = 0x7FFFFFFF
} MLPaddingMode;

typedef enum MLPowerPreference {
    MLPowerPreference_Default = 0x00000000,
    MLPowerPreference_High_performance = 0x00000001,
    MLPowerPreference_Low_power = 0x00000002,
    MLPowerPreference_Force32 = 0x7FFFFFFF
} MLPowerPreference;


typedef struct MLArrayBufferView {
    void * buffer;
    size_t byteLength;
    size_t byteOffset;
} MLArrayBufferView;

typedef struct MLBatchNormOptions {
    MLOperand scale;
    MLOperand bias;
    uint32_t axis;
    float epsilon;
} MLBatchNormOptions;

typedef struct MLClampOptions {
    MLOperand minValue;
    MLOperand maxValue;
} MLClampOptions;

typedef struct MLContextOptions {
    MLDevicePreference devicePreference;
    MLPowerPreference powerPreference;
} MLContextOptions;

typedef struct MLConv2dOptions {
    uint32_t paddingCount;
    int32_t const * padding;
    uint32_t stridesCount;
    int32_t const * strides;
    uint32_t dilationsCount;
    int32_t const * dilations;
    MLAutoPad autoPad;
    int32_t groups;
    MLInputOperandLayout inputLayout;
    MLFilterOperandLayout filterLayout;
} MLConv2dOptions;

typedef struct MLGemmOptions {
    MLOperand c;
    float alpha;
    float beta;
    bool aTranspose;
    bool bTranspose;
} MLGemmOptions;

typedef struct MLInstanceNormOptions {
    MLOperand scale;
    MLOperand bias;
    float epsilon;
    MLInputOperandLayout layout;
} MLInstanceNormOptions;

typedef struct MLLeakyReluOptions {
    float alpha;
} MLLeakyReluOptions;

typedef struct MLOperandDescriptor {
    MLOperandType type;
    int32_t const * dimensions;
    uint32_t dimensionsCount;
} MLOperandDescriptor;

typedef struct MLPadOptions {
    MLPaddingMode mode;
    float value;
} MLPadOptions;

typedef struct MLPool2dOptions {
    uint32_t windowDimensionsCount;
    int32_t const * windowDimensions;
    uint32_t paddingCount;
    int32_t const * padding;
    uint32_t stridesCount;
    int32_t const * strides;
    uint32_t dilationsCount;
    int32_t const * dilations;
    MLAutoPad autoPad;
    MLInputOperandLayout layout;
} MLPool2dOptions;

typedef struct MLReduceMeanOptions {
    uint32_t axesCount;
    int32_t const * axes;
    bool keepDimensions;
} MLReduceMeanOptions;

typedef struct MLResampleOptions {
    MLInterpolationMode mode;
    uint32_t scalesCount;
    float const * scales;
    uint32_t sizesCount;
    int32_t const * sizes;
} MLResampleOptions;

typedef struct MLTransposeOptions {
    uint32_t permutationCount;
    int32_t const * permutation;
} MLTransposeOptions;

typedef struct MLInput {
    MLArrayBufferView resource;
    int32_t const * dimensions;
    uint32_t dimensionsCount;
} MLInput;


#ifdef __cplusplus
extern "C" {
#endif

typedef void (*MLErrorCallback)(MLErrorType type, char const * message, void * userdata);

typedef void (*WebnnProc)(void);

#if !defined(WEBNN_SKIP_PROCS)

typedef MLGraphBuilder (*WebnnProcCreateGraphBuilder)(MLContext context);
typedef MLNamedInputs (*WebnnProcCreateNamedInputs)();
typedef MLNamedOperands (*WebnnProcCreateNamedOperands)();
typedef MLNamedOutputs (*WebnnProcCreateNamedOutputs)();

// Procs of Context
typedef bool (*WebnnProcContextPopErrorScope)(MLContext context, MLErrorCallback callback, void * userdata);
typedef void (*WebnnProcContextPushErrorScope)(MLContext context, MLErrorFilter filter);
typedef void (*WebnnProcContextSetUncapturedErrorCallback)(MLContext context, MLErrorCallback callback, void * userdata);
typedef void (*WebnnProcContextReference)(MLContext context);
typedef void (*WebnnProcContextRelease)(MLContext context);

// Procs of Graph
typedef MLComputeGraphStatus (*WebnnProcGraphCompute)(MLGraph graph, MLNamedInputs inputs, MLNamedOutputs outputs);
typedef void (*WebnnProcGraphReference)(MLGraph graph);
typedef void (*WebnnProcGraphRelease)(MLGraph graph);

// Procs of GraphBuilder
typedef MLOperand (*WebnnProcGraphBuilderAdd)(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b);
typedef MLOperand (*WebnnProcGraphBuilderAveragePool2d)(MLGraphBuilder graphBuilder, MLOperand input, MLPool2dOptions const * options);
typedef MLOperand (*WebnnProcGraphBuilderBatchNorm)(MLGraphBuilder graphBuilder, MLOperand input, MLOperand mean, MLOperand variance, MLBatchNormOptions const * options);
typedef MLGraph (*WebnnProcGraphBuilderBuild)(MLGraphBuilder graphBuilder, MLNamedOperands namedOperands);
typedef MLOperand (*WebnnProcGraphBuilderClamp)(MLGraphBuilder graphBuilder, MLOperand input, MLClampOptions const * options);
typedef MLOperand (*WebnnProcGraphBuilderConcat)(MLGraphBuilder graphBuilder, uint32_t inputsCount, MLOperand const * inputs, uint32_t axis);
typedef MLOperand (*WebnnProcGraphBuilderConstant)(MLGraphBuilder graphBuilder, MLOperandDescriptor const * desc, MLArrayBufferView const * value);
typedef MLOperand (*WebnnProcGraphBuilderConv2d)(MLGraphBuilder graphBuilder, MLOperand input, MLOperand filter, MLConv2dOptions const * options);
typedef MLOperand (*WebnnProcGraphBuilderDiv)(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b);
typedef MLOperand (*WebnnProcGraphBuilderGemm)(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b, MLGemmOptions const * options);
typedef MLOperand (*WebnnProcGraphBuilderInput)(MLGraphBuilder graphBuilder, char const * name, MLOperandDescriptor const * desc);
typedef MLOperand (*WebnnProcGraphBuilderInstanceNorm)(MLGraphBuilder graphBuilder, MLOperand input, MLInstanceNormOptions const * options);
typedef MLOperand (*WebnnProcGraphBuilderLeakyRelu)(MLGraphBuilder graphBuilder, MLOperand input, MLLeakyReluOptions const * options);
typedef MLOperand (*WebnnProcGraphBuilderMatmul)(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b);
typedef MLOperand (*WebnnProcGraphBuilderMaxPool2d)(MLGraphBuilder graphBuilder, MLOperand input, MLPool2dOptions const * options);
typedef MLOperand (*WebnnProcGraphBuilderMul)(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b);
typedef MLOperand (*WebnnProcGraphBuilderPad)(MLGraphBuilder graphBuilder, MLOperand input, MLOperand padding, MLPadOptions const * options);
typedef MLOperand (*WebnnProcGraphBuilderReduceMean)(MLGraphBuilder graphBuilder, MLOperand input, MLReduceMeanOptions const * options);
typedef MLOperand (*WebnnProcGraphBuilderRelu)(MLGraphBuilder graphBuilder, MLOperand input);
typedef MLOperand (*WebnnProcGraphBuilderResample)(MLGraphBuilder graphBuilder, MLOperand input, MLResampleOptions const * options);
typedef MLOperand (*WebnnProcGraphBuilderReshape)(MLGraphBuilder graphBuilder, MLOperand input, int32_t const * newShape, uint32_t newShapeCount);
typedef MLOperand (*WebnnProcGraphBuilderSigmoid)(MLGraphBuilder graphBuilder, MLOperand input);
typedef MLOperand (*WebnnProcGraphBuilderSoftmax)(MLGraphBuilder graphBuilder, MLOperand input);
typedef MLOperand (*WebnnProcGraphBuilderSub)(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b);
typedef MLOperand (*WebnnProcGraphBuilderTanh)(MLGraphBuilder graphBuilder, MLOperand input);
typedef MLOperand (*WebnnProcGraphBuilderTranspose)(MLGraphBuilder graphBuilder, MLOperand input, MLTransposeOptions const * options);
typedef void (*WebnnProcGraphBuilderReference)(MLGraphBuilder graphBuilder);
typedef void (*WebnnProcGraphBuilderRelease)(MLGraphBuilder graphBuilder);

// Procs of NamedInputs
typedef void (*WebnnProcNamedInputsSet)(MLNamedInputs namedInputs, char const * name, MLInput const * input);
typedef void (*WebnnProcNamedInputsReference)(MLNamedInputs namedInputs);
typedef void (*WebnnProcNamedInputsRelease)(MLNamedInputs namedInputs);

// Procs of NamedOperands
typedef void (*WebnnProcNamedOperandsSet)(MLNamedOperands namedOperands, char const * name, MLOperand operand);
typedef void (*WebnnProcNamedOperandsReference)(MLNamedOperands namedOperands);
typedef void (*WebnnProcNamedOperandsRelease)(MLNamedOperands namedOperands);

// Procs of NamedOutputs
typedef void (*WebnnProcNamedOutputsSet)(MLNamedOutputs namedOutputs, char const * name, MLArrayBufferView const * resource);
typedef void (*WebnnProcNamedOutputsReference)(MLNamedOutputs namedOutputs);
typedef void (*WebnnProcNamedOutputsRelease)(MLNamedOutputs namedOutputs);

// Procs of Operand
typedef void (*WebnnProcOperandReference)(MLOperand operand);
typedef void (*WebnnProcOperandRelease)(MLOperand operand);

// Procs of Operator
typedef void (*WebnnProcOperatorReference)(MLOperator mlOperator);
typedef void (*WebnnProcOperatorRelease)(MLOperator mlOperator);

#endif  // !defined(WEBNN_SKIP_PROCS)

#if !defined(WEBNN_SKIP_DECLARATIONS)

WEBNN_EXPORT MLGraphBuilder webnnCreateGraphBuilder(MLContext context);
WEBNN_EXPORT MLNamedInputs webnnCreateNamedInputs();
WEBNN_EXPORT MLNamedOperands webnnCreateNamedOperands();
WEBNN_EXPORT MLNamedOutputs webnnCreateNamedOutputs();

// Methods of Context
WEBNN_EXPORT bool mlContextPopErrorScope(MLContext context, MLErrorCallback callback, void * userdata);
WEBNN_EXPORT void mlContextPushErrorScope(MLContext context, MLErrorFilter filter);
WEBNN_EXPORT void mlContextSetUncapturedErrorCallback(MLContext context, MLErrorCallback callback, void * userdata);
WEBNN_EXPORT void mlContextReference(MLContext context);
WEBNN_EXPORT void mlContextRelease(MLContext context);

// Methods of Graph
WEBNN_EXPORT MLComputeGraphStatus mlGraphCompute(MLGraph graph, MLNamedInputs inputs, MLNamedOutputs outputs);
WEBNN_EXPORT void mlGraphReference(MLGraph graph);
WEBNN_EXPORT void mlGraphRelease(MLGraph graph);

// Methods of GraphBuilder
WEBNN_EXPORT MLOperand mlGraphBuilderAdd(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b);
WEBNN_EXPORT MLOperand mlGraphBuilderAveragePool2d(MLGraphBuilder graphBuilder, MLOperand input, MLPool2dOptions const * options);
WEBNN_EXPORT MLOperand mlGraphBuilderBatchNorm(MLGraphBuilder graphBuilder, MLOperand input, MLOperand mean, MLOperand variance, MLBatchNormOptions const * options);
WEBNN_EXPORT MLGraph mlGraphBuilderBuild(MLGraphBuilder graphBuilder, MLNamedOperands namedOperands);
WEBNN_EXPORT MLOperand mlGraphBuilderClamp(MLGraphBuilder graphBuilder, MLOperand input, MLClampOptions const * options);
WEBNN_EXPORT MLOperand mlGraphBuilderConcat(MLGraphBuilder graphBuilder, uint32_t inputsCount, MLOperand const * inputs, uint32_t axis);
WEBNN_EXPORT MLOperand mlGraphBuilderConstant(MLGraphBuilder graphBuilder, MLOperandDescriptor const * desc, MLArrayBufferView const * value);
WEBNN_EXPORT MLOperand mlGraphBuilderConv2d(MLGraphBuilder graphBuilder, MLOperand input, MLOperand filter, MLConv2dOptions const * options);
WEBNN_EXPORT MLOperand mlGraphBuilderDiv(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b);
WEBNN_EXPORT MLOperand mlGraphBuilderGemm(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b, MLGemmOptions const * options);
WEBNN_EXPORT MLOperand mlGraphBuilderInput(MLGraphBuilder graphBuilder, char const * name, MLOperandDescriptor const * desc);
WEBNN_EXPORT MLOperand mlGraphBuilderInstanceNorm(MLGraphBuilder graphBuilder, MLOperand input, MLInstanceNormOptions const * options);
WEBNN_EXPORT MLOperand mlGraphBuilderLeakyRelu(MLGraphBuilder graphBuilder, MLOperand input, MLLeakyReluOptions const * options);
WEBNN_EXPORT MLOperand mlGraphBuilderMatmul(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b);
WEBNN_EXPORT MLOperand mlGraphBuilderMaxPool2d(MLGraphBuilder graphBuilder, MLOperand input, MLPool2dOptions const * options);
WEBNN_EXPORT MLOperand mlGraphBuilderMul(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b);
WEBNN_EXPORT MLOperand mlGraphBuilderPad(MLGraphBuilder graphBuilder, MLOperand input, MLOperand padding, MLPadOptions const * options);
WEBNN_EXPORT MLOperand mlGraphBuilderReduceMean(MLGraphBuilder graphBuilder, MLOperand input, MLReduceMeanOptions const * options);
WEBNN_EXPORT MLOperand mlGraphBuilderRelu(MLGraphBuilder graphBuilder, MLOperand input);
WEBNN_EXPORT MLOperand mlGraphBuilderResample(MLGraphBuilder graphBuilder, MLOperand input, MLResampleOptions const * options);
WEBNN_EXPORT MLOperand mlGraphBuilderReshape(MLGraphBuilder graphBuilder, MLOperand input, int32_t const * newShape, uint32_t newShapeCount);
WEBNN_EXPORT MLOperand mlGraphBuilderSigmoid(MLGraphBuilder graphBuilder, MLOperand input);
WEBNN_EXPORT MLOperand mlGraphBuilderSoftmax(MLGraphBuilder graphBuilder, MLOperand input);
WEBNN_EXPORT MLOperand mlGraphBuilderSub(MLGraphBuilder graphBuilder, MLOperand a, MLOperand b);
WEBNN_EXPORT MLOperand mlGraphBuilderTanh(MLGraphBuilder graphBuilder, MLOperand input);
WEBNN_EXPORT MLOperand mlGraphBuilderTranspose(MLGraphBuilder graphBuilder, MLOperand input, MLTransposeOptions const * options);
WEBNN_EXPORT void mlGraphBuilderReference(MLGraphBuilder graphBuilder);
WEBNN_EXPORT void mlGraphBuilderRelease(MLGraphBuilder graphBuilder);

// Methods of NamedInputs
WEBNN_EXPORT void mlNamedInputsSet(MLNamedInputs namedInputs, char const * name, MLInput const * input);
WEBNN_EXPORT void mlNamedInputsReference(MLNamedInputs namedInputs);
WEBNN_EXPORT void mlNamedInputsRelease(MLNamedInputs namedInputs);

// Methods of NamedOperands
WEBNN_EXPORT void mlNamedOperandsSet(MLNamedOperands namedOperands, char const * name, MLOperand operand);
WEBNN_EXPORT void mlNamedOperandsReference(MLNamedOperands namedOperands);
WEBNN_EXPORT void mlNamedOperandsRelease(MLNamedOperands namedOperands);

// Methods of NamedOutputs
WEBNN_EXPORT void mlNamedOutputsSet(MLNamedOutputs namedOutputs, char const * name, MLArrayBufferView const * resource);
WEBNN_EXPORT void mlNamedOutputsReference(MLNamedOutputs namedOutputs);
WEBNN_EXPORT void mlNamedOutputsRelease(MLNamedOutputs namedOutputs);

// Methods of Operand
WEBNN_EXPORT void mlOperandReference(MLOperand operand);
WEBNN_EXPORT void mlOperandRelease(MLOperand operand);

// Methods of Operator
WEBNN_EXPORT void mlOperatorReference(MLOperator mlOperator);
WEBNN_EXPORT void mlOperatorRelease(MLOperator mlOperator);

#endif  // !defined(WEBNN_SKIP_DECLARATIONS)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WEBNN_H_
