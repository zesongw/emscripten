#include "webnn/webnn_cpp.h"

namespace ml {

    // AutoPad

    static_assert(sizeof(AutoPad) == sizeof(MLAutoPad), "sizeof mismatch for AutoPad");
    static_assert(alignof(AutoPad) == alignof(MLAutoPad), "alignof mismatch for AutoPad");

    static_assert(static_cast<uint32_t>(AutoPad::Explicit) == MLAutoPad_Explicit, "value mismatch for AutoPad::Explicit");
    static_assert(static_cast<uint32_t>(AutoPad::SameUpper) == MLAutoPad_SameUpper, "value mismatch for AutoPad::SameUpper");
    static_assert(static_cast<uint32_t>(AutoPad::SameLower) == MLAutoPad_SameLower, "value mismatch for AutoPad::SameLower");

    // BuildGraphStatus

    static_assert(sizeof(BuildGraphStatus) == sizeof(MLBuildGraphStatus), "sizeof mismatch for BuildGraphStatus");
    static_assert(alignof(BuildGraphStatus) == alignof(MLBuildGraphStatus), "alignof mismatch for BuildGraphStatus");

    static_assert(static_cast<uint32_t>(BuildGraphStatus::Success) == MLBuildGraphStatus_Success, "value mismatch for BuildGraphStatus::Success");
    static_assert(static_cast<uint32_t>(BuildGraphStatus::Error) == MLBuildGraphStatus_Error, "value mismatch for BuildGraphStatus::Error");
    static_assert(static_cast<uint32_t>(BuildGraphStatus::ContextLost) == MLBuildGraphStatus_ContextLost, "value mismatch for BuildGraphStatus::ContextLost");
    static_assert(static_cast<uint32_t>(BuildGraphStatus::Unknown) == MLBuildGraphStatus_Unknown, "value mismatch for BuildGraphStatus::Unknown");

    // ComputeGraphStatus

    static_assert(sizeof(ComputeGraphStatus) == sizeof(MLComputeGraphStatus), "sizeof mismatch for ComputeGraphStatus");
    static_assert(alignof(ComputeGraphStatus) == alignof(MLComputeGraphStatus), "alignof mismatch for ComputeGraphStatus");

    static_assert(static_cast<uint32_t>(ComputeGraphStatus::Success) == MLComputeGraphStatus_Success, "value mismatch for ComputeGraphStatus::Success");
    static_assert(static_cast<uint32_t>(ComputeGraphStatus::Error) == MLComputeGraphStatus_Error, "value mismatch for ComputeGraphStatus::Error");
    static_assert(static_cast<uint32_t>(ComputeGraphStatus::ContextLost) == MLComputeGraphStatus_ContextLost, "value mismatch for ComputeGraphStatus::ContextLost");
    static_assert(static_cast<uint32_t>(ComputeGraphStatus::Unknown) == MLComputeGraphStatus_Unknown, "value mismatch for ComputeGraphStatus::Unknown");

    // ErrorFilter

    static_assert(sizeof(ErrorFilter) == sizeof(MLErrorFilter), "sizeof mismatch for ErrorFilter");
    static_assert(alignof(ErrorFilter) == alignof(MLErrorFilter), "alignof mismatch for ErrorFilter");

    static_assert(static_cast<uint32_t>(ErrorFilter::None) == MLErrorFilter_None, "value mismatch for ErrorFilter::None");
    static_assert(static_cast<uint32_t>(ErrorFilter::Validation) == MLErrorFilter_Validation, "value mismatch for ErrorFilter::Validation");
    static_assert(static_cast<uint32_t>(ErrorFilter::OutOfMemory) == MLErrorFilter_OutOfMemory, "value mismatch for ErrorFilter::OutOfMemory");

    // ErrorType

    static_assert(sizeof(ErrorType) == sizeof(MLErrorType), "sizeof mismatch for ErrorType");
    static_assert(alignof(ErrorType) == alignof(MLErrorType), "alignof mismatch for ErrorType");

    static_assert(static_cast<uint32_t>(ErrorType::NoError) == MLErrorType_NoError, "value mismatch for ErrorType::NoError");
    static_assert(static_cast<uint32_t>(ErrorType::Validation) == MLErrorType_Validation, "value mismatch for ErrorType::Validation");
    static_assert(static_cast<uint32_t>(ErrorType::OutOfMemory) == MLErrorType_OutOfMemory, "value mismatch for ErrorType::OutOfMemory");
    static_assert(static_cast<uint32_t>(ErrorType::Unknown) == MLErrorType_Unknown, "value mismatch for ErrorType::Unknown");
    static_assert(static_cast<uint32_t>(ErrorType::DeviceLost) == MLErrorType_DeviceLost, "value mismatch for ErrorType::DeviceLost");

    // FilterOperandLayout

    static_assert(sizeof(FilterOperandLayout) == sizeof(MLFilterOperandLayout), "sizeof mismatch for FilterOperandLayout");
    static_assert(alignof(FilterOperandLayout) == alignof(MLFilterOperandLayout), "alignof mismatch for FilterOperandLayout");

    static_assert(static_cast<uint32_t>(FilterOperandLayout::Oihw) == MLFilterOperandLayout_Oihw, "value mismatch for FilterOperandLayout::Oihw");
    static_assert(static_cast<uint32_t>(FilterOperandLayout::Hwio) == MLFilterOperandLayout_Hwio, "value mismatch for FilterOperandLayout::Hwio");
    static_assert(static_cast<uint32_t>(FilterOperandLayout::Ohwi) == MLFilterOperandLayout_Ohwi, "value mismatch for FilterOperandLayout::Ohwi");
    static_assert(static_cast<uint32_t>(FilterOperandLayout::Ihwo) == MLFilterOperandLayout_Ihwo, "value mismatch for FilterOperandLayout::Ihwo");

    // FusedActivation

    static_assert(sizeof(FusedActivation) == sizeof(MLFusedActivation), "sizeof mismatch for FusedActivation");
    static_assert(alignof(FusedActivation) == alignof(MLFusedActivation), "alignof mismatch for FusedActivation");

    static_assert(static_cast<uint32_t>(FusedActivation::None) == MLFusedActivation_None, "value mismatch for FusedActivation::None");
    static_assert(static_cast<uint32_t>(FusedActivation::Relu) == MLFusedActivation_Relu, "value mismatch for FusedActivation::Relu");

    // InputOperandLayout

    static_assert(sizeof(InputOperandLayout) == sizeof(MLInputOperandLayout), "sizeof mismatch for InputOperandLayout");
    static_assert(alignof(InputOperandLayout) == alignof(MLInputOperandLayout), "alignof mismatch for InputOperandLayout");

    static_assert(static_cast<uint32_t>(InputOperandLayout::Nchw) == MLInputOperandLayout_Nchw, "value mismatch for InputOperandLayout::Nchw");
    static_assert(static_cast<uint32_t>(InputOperandLayout::Nhwc) == MLInputOperandLayout_Nhwc, "value mismatch for InputOperandLayout::Nhwc");

    // OperandType

    static_assert(sizeof(OperandType) == sizeof(MLOperandType), "sizeof mismatch for OperandType");
    static_assert(alignof(OperandType) == alignof(MLOperandType), "alignof mismatch for OperandType");

    static_assert(static_cast<uint32_t>(OperandType::Float32) == MLOperandType_Float32, "value mismatch for OperandType::Float32");
    static_assert(static_cast<uint32_t>(OperandType::Float16) == MLOperandType_Float16, "value mismatch for OperandType::Float16");
    static_assert(static_cast<uint32_t>(OperandType::Int32) == MLOperandType_Int32, "value mismatch for OperandType::Int32");
    static_assert(static_cast<uint32_t>(OperandType::Uint32) == MLOperandType_Uint32, "value mismatch for OperandType::Uint32");
    static_assert(static_cast<uint32_t>(OperandType::Int8) == MLOperandType_Int8, "value mismatch for OperandType::Int8");
    static_assert(static_cast<uint32_t>(OperandType::Uint8) == MLOperandType_Uint8, "value mismatch for OperandType::Uint8");

    // PowerPreference

    static_assert(sizeof(PowerPreference) == sizeof(MLPowerPreference), "sizeof mismatch for PowerPreference");
    static_assert(alignof(PowerPreference) == alignof(MLPowerPreference), "alignof mismatch for PowerPreference");

    static_assert(static_cast<uint32_t>(PowerPreference::Default) == MLPowerPreference_Default, "value mismatch for PowerPreference::Default");
    static_assert(static_cast<uint32_t>(PowerPreference::High_performance) == MLPowerPreference_High_performance, "value mismatch for PowerPreference::High_performance");
    static_assert(static_cast<uint32_t>(PowerPreference::Low_power) == MLPowerPreference_Low_power, "value mismatch for PowerPreference::Low_power");

    // ChainedStruct


    // BatchNormOptions

    static_assert(sizeof(BatchNormOptions) == sizeof(MLBatchNormOptions), "sizeof mismatch for BatchNormOptions");
    static_assert(alignof(BatchNormOptions) == alignof(MLBatchNormOptions), "alignof mismatch for BatchNormOptions");

    static_assert(offsetof(BatchNormOptions, scale) == offsetof(MLBatchNormOptions, scale),
            "offsetof mismatch for BatchNormOptions::scale");
    static_assert(offsetof(BatchNormOptions, bias) == offsetof(MLBatchNormOptions, bias),
            "offsetof mismatch for BatchNormOptions::bias");
    static_assert(offsetof(BatchNormOptions, axis) == offsetof(MLBatchNormOptions, axis),
            "offsetof mismatch for BatchNormOptions::axis");
    static_assert(offsetof(BatchNormOptions, epsilon) == offsetof(MLBatchNormOptions, epsilon),
            "offsetof mismatch for BatchNormOptions::epsilon");
    static_assert(offsetof(BatchNormOptions, activation) == offsetof(MLBatchNormOptions, activation),
            "offsetof mismatch for BatchNormOptions::activation");

    // ClampOptions

    static_assert(sizeof(ClampOptions) == sizeof(MLClampOptions), "sizeof mismatch for ClampOptions");
    static_assert(alignof(ClampOptions) == alignof(MLClampOptions), "alignof mismatch for ClampOptions");

    static_assert(offsetof(ClampOptions, minValue) == offsetof(MLClampOptions, minValue),
            "offsetof mismatch for ClampOptions::minValue");
    static_assert(offsetof(ClampOptions, maxValue) == offsetof(MLClampOptions, maxValue),
            "offsetof mismatch for ClampOptions::maxValue");

    // ContextOptions

    static_assert(sizeof(ContextOptions) == sizeof(MLContextOptions), "sizeof mismatch for ContextOptions");
    static_assert(alignof(ContextOptions) == alignof(MLContextOptions), "alignof mismatch for ContextOptions");

    static_assert(offsetof(ContextOptions, powerPreference) == offsetof(MLContextOptions, powerPreference),
            "offsetof mismatch for ContextOptions::powerPreference");

    // Conv2dOptions

    static_assert(sizeof(Conv2dOptions) == sizeof(MLConv2dOptions), "sizeof mismatch for Conv2dOptions");
    static_assert(alignof(Conv2dOptions) == alignof(MLConv2dOptions), "alignof mismatch for Conv2dOptions");

    static_assert(offsetof(Conv2dOptions, paddingCount) == offsetof(MLConv2dOptions, paddingCount),
            "offsetof mismatch for Conv2dOptions::paddingCount");
    static_assert(offsetof(Conv2dOptions, padding) == offsetof(MLConv2dOptions, padding),
            "offsetof mismatch for Conv2dOptions::padding");
    static_assert(offsetof(Conv2dOptions, stridesCount) == offsetof(MLConv2dOptions, stridesCount),
            "offsetof mismatch for Conv2dOptions::stridesCount");
    static_assert(offsetof(Conv2dOptions, strides) == offsetof(MLConv2dOptions, strides),
            "offsetof mismatch for Conv2dOptions::strides");
    static_assert(offsetof(Conv2dOptions, dilationsCount) == offsetof(MLConv2dOptions, dilationsCount),
            "offsetof mismatch for Conv2dOptions::dilationsCount");
    static_assert(offsetof(Conv2dOptions, dilations) == offsetof(MLConv2dOptions, dilations),
            "offsetof mismatch for Conv2dOptions::dilations");
    static_assert(offsetof(Conv2dOptions, autoPad) == offsetof(MLConv2dOptions, autoPad),
            "offsetof mismatch for Conv2dOptions::autoPad");
    static_assert(offsetof(Conv2dOptions, groups) == offsetof(MLConv2dOptions, groups),
            "offsetof mismatch for Conv2dOptions::groups");
    static_assert(offsetof(Conv2dOptions, inputLayout) == offsetof(MLConv2dOptions, inputLayout),
            "offsetof mismatch for Conv2dOptions::inputLayout");
    static_assert(offsetof(Conv2dOptions, filterLayout) == offsetof(MLConv2dOptions, filterLayout),
            "offsetof mismatch for Conv2dOptions::filterLayout");
    static_assert(offsetof(Conv2dOptions, bias) == offsetof(MLConv2dOptions, bias),
            "offsetof mismatch for Conv2dOptions::bias");
    static_assert(offsetof(Conv2dOptions, activation) == offsetof(MLConv2dOptions, activation),
            "offsetof mismatch for Conv2dOptions::activation");

    // GemmOptions

    static_assert(sizeof(GemmOptions) == sizeof(MLGemmOptions), "sizeof mismatch for GemmOptions");
    static_assert(alignof(GemmOptions) == alignof(MLGemmOptions), "alignof mismatch for GemmOptions");

    static_assert(offsetof(GemmOptions, c) == offsetof(MLGemmOptions, c),
            "offsetof mismatch for GemmOptions::c");
    static_assert(offsetof(GemmOptions, alpha) == offsetof(MLGemmOptions, alpha),
            "offsetof mismatch for GemmOptions::alpha");
    static_assert(offsetof(GemmOptions, beta) == offsetof(MLGemmOptions, beta),
            "offsetof mismatch for GemmOptions::beta");
    static_assert(offsetof(GemmOptions, aTranspose) == offsetof(MLGemmOptions, aTranspose),
            "offsetof mismatch for GemmOptions::aTranspose");
    static_assert(offsetof(GemmOptions, bTranspose) == offsetof(MLGemmOptions, bTranspose),
            "offsetof mismatch for GemmOptions::bTranspose");

    // Input

    static_assert(sizeof(Input) == sizeof(MLInput), "sizeof mismatch for Input");
    static_assert(alignof(Input) == alignof(MLInput), "alignof mismatch for Input");

    static_assert(offsetof(Input, buffer) == offsetof(MLInput, buffer),
            "offsetof mismatch for Input::buffer");
    static_assert(offsetof(Input, size) == offsetof(MLInput, size),
            "offsetof mismatch for Input::size");
    static_assert(offsetof(Input, dimensions) == offsetof(MLInput, dimensions),
            "offsetof mismatch for Input::dimensions");
    static_assert(offsetof(Input, dimensionsCount) == offsetof(MLInput, dimensionsCount),
            "offsetof mismatch for Input::dimensionsCount");

    // LeakyReluOptions

    static_assert(sizeof(LeakyReluOptions) == sizeof(MLLeakyReluOptions), "sizeof mismatch for LeakyReluOptions");
    static_assert(alignof(LeakyReluOptions) == alignof(MLLeakyReluOptions), "alignof mismatch for LeakyReluOptions");

    static_assert(offsetof(LeakyReluOptions, alpha) == offsetof(MLLeakyReluOptions, alpha),
            "offsetof mismatch for LeakyReluOptions::alpha");

    // OperandDescriptor

    static_assert(sizeof(OperandDescriptor) == sizeof(MLOperandDescriptor), "sizeof mismatch for OperandDescriptor");
    static_assert(alignof(OperandDescriptor) == alignof(MLOperandDescriptor), "alignof mismatch for OperandDescriptor");

    static_assert(offsetof(OperandDescriptor, type) == offsetof(MLOperandDescriptor, type),
            "offsetof mismatch for OperandDescriptor::type");
    static_assert(offsetof(OperandDescriptor, dimensions) == offsetof(MLOperandDescriptor, dimensions),
            "offsetof mismatch for OperandDescriptor::dimensions");
    static_assert(offsetof(OperandDescriptor, dimensionsCount) == offsetof(MLOperandDescriptor, dimensionsCount),
            "offsetof mismatch for OperandDescriptor::dimensionsCount");

    // Output

    static_assert(sizeof(Output) == sizeof(MLOutput), "sizeof mismatch for Output");
    static_assert(alignof(Output) == alignof(MLOutput), "alignof mismatch for Output");

    static_assert(offsetof(Output, buffer) == offsetof(MLOutput, buffer),
            "offsetof mismatch for Output::buffer");
    static_assert(offsetof(Output, size) == offsetof(MLOutput, size),
            "offsetof mismatch for Output::size");
    static_assert(offsetof(Output, dimensions) == offsetof(MLOutput, dimensions),
            "offsetof mismatch for Output::dimensions");
    static_assert(offsetof(Output, dimensionsCount) == offsetof(MLOutput, dimensionsCount),
            "offsetof mismatch for Output::dimensionsCount");

    // Pool2dOptions

    static_assert(sizeof(Pool2dOptions) == sizeof(MLPool2dOptions), "sizeof mismatch for Pool2dOptions");
    static_assert(alignof(Pool2dOptions) == alignof(MLPool2dOptions), "alignof mismatch for Pool2dOptions");

    static_assert(offsetof(Pool2dOptions, windowDimensionsCount) == offsetof(MLPool2dOptions, windowDimensionsCount),
            "offsetof mismatch for Pool2dOptions::windowDimensionsCount");
    static_assert(offsetof(Pool2dOptions, windowDimensions) == offsetof(MLPool2dOptions, windowDimensions),
            "offsetof mismatch for Pool2dOptions::windowDimensions");
    static_assert(offsetof(Pool2dOptions, paddingCount) == offsetof(MLPool2dOptions, paddingCount),
            "offsetof mismatch for Pool2dOptions::paddingCount");
    static_assert(offsetof(Pool2dOptions, padding) == offsetof(MLPool2dOptions, padding),
            "offsetof mismatch for Pool2dOptions::padding");
    static_assert(offsetof(Pool2dOptions, stridesCount) == offsetof(MLPool2dOptions, stridesCount),
            "offsetof mismatch for Pool2dOptions::stridesCount");
    static_assert(offsetof(Pool2dOptions, strides) == offsetof(MLPool2dOptions, strides),
            "offsetof mismatch for Pool2dOptions::strides");
    static_assert(offsetof(Pool2dOptions, dilationsCount) == offsetof(MLPool2dOptions, dilationsCount),
            "offsetof mismatch for Pool2dOptions::dilationsCount");
    static_assert(offsetof(Pool2dOptions, dilations) == offsetof(MLPool2dOptions, dilations),
            "offsetof mismatch for Pool2dOptions::dilations");
    static_assert(offsetof(Pool2dOptions, autoPad) == offsetof(MLPool2dOptions, autoPad),
            "offsetof mismatch for Pool2dOptions::autoPad");
    static_assert(offsetof(Pool2dOptions, layout) == offsetof(MLPool2dOptions, layout),
            "offsetof mismatch for Pool2dOptions::layout");

    // TransposeOptions

    static_assert(sizeof(TransposeOptions) == sizeof(MLTransposeOptions), "sizeof mismatch for TransposeOptions");
    static_assert(alignof(TransposeOptions) == alignof(MLTransposeOptions), "alignof mismatch for TransposeOptions");

    static_assert(offsetof(TransposeOptions, permutationCount) == offsetof(MLTransposeOptions, permutationCount),
            "offsetof mismatch for TransposeOptions::permutationCount");
    static_assert(offsetof(TransposeOptions, permutation) == offsetof(MLTransposeOptions, permutation),
            "offsetof mismatch for TransposeOptions::permutation");

    // Context

    static_assert(sizeof(Context) == sizeof(MLContext), "sizeof mismatch for Context");
    static_assert(alignof(Context) == alignof(MLContext), "alignof mismatch for Context");

    bool Context::PopErrorScope(ErrorCallback callback, void * userdata) const {
        auto result = mlContextPopErrorScope(GetHandle(), callback, reinterpret_cast<void * >(userdata));
        return result;
    }
    void Context::PushErrorScope(ErrorFilter filter) const {
        mlContextPushErrorScope(GetHandle(), static_cast<MLErrorFilter>(filter));
    }
    void Context::SetUncapturedErrorCallback(ErrorCallback callback, void * userdata) const {
        mlContextSetUncapturedErrorCallback(GetHandle(), callback, reinterpret_cast<void * >(userdata));
    }
    void Context::WebnnReference(MLContext handle) {
        if (handle != nullptr) {
            mlContextReference(handle);
        }
    }
    void Context::WebnnRelease(MLContext handle) {
        if (handle != nullptr) {
            mlContextRelease(handle);
        }
    }

    // Graph

    static_assert(sizeof(Graph) == sizeof(MLGraph), "sizeof mismatch for Graph");
    static_assert(alignof(Graph) == alignof(MLGraph), "alignof mismatch for Graph");

    void Graph::Compute(NamedInputs const& inputs, ComputeGraphCallback callback, void * userdata, NamedOutputs const& outputs) const {
        mlGraphCompute(GetHandle(), inputs.GetHandle(), callback, reinterpret_cast<void * >(userdata), outputs.GetHandle());
    }
    ComputeGraphStatus Graph::ComputeSync(NamedInputs const& inputs, NamedOutputs const& outputs) const {
        auto result = mlGraphComputeSync(GetHandle(), inputs.GetHandle(), outputs.GetHandle());
        return static_cast<ComputeGraphStatus>(result);
    }
    void Graph::WebnnReference(MLGraph handle) {
        if (handle != nullptr) {
            mlGraphReference(handle);
        }
    }
    void Graph::WebnnRelease(MLGraph handle) {
        if (handle != nullptr) {
            mlGraphRelease(handle);
        }
    }

    // GraphBuilder

    static_assert(sizeof(GraphBuilder) == sizeof(MLGraphBuilder), "sizeof mismatch for GraphBuilder");
    static_assert(alignof(GraphBuilder) == alignof(MLGraphBuilder), "alignof mismatch for GraphBuilder");

    Operand GraphBuilder::Add(Operand const& a, Operand const& b) const {
        auto result = mlGraphBuilderAdd(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::AveragePool2d(Operand const& input, Pool2dOptions const * options) const {
        auto result = mlGraphBuilderAveragePool2d(GetHandle(), input.GetHandle(), reinterpret_cast<MLPool2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::BatchNorm(Operand const& input, Operand const& mean, Operand const& variance, BatchNormOptions const * options) const {
        auto result = mlGraphBuilderBatchNorm(GetHandle(), input.GetHandle(), mean.GetHandle(), variance.GetHandle(), reinterpret_cast<MLBatchNormOptions const * >(options));
        return Operand::Acquire(result);
    }
    void GraphBuilder::Build(NamedOperands const& namedOperands, BuildGraphCallback callback, void * userdata) const {
        mlGraphBuilderBuild(GetHandle(), namedOperands.GetHandle(), callback, reinterpret_cast<void * >(userdata));
    }
    Graph GraphBuilder::BuildSync(NamedOperands const& namedOperands) const {
        auto result = mlGraphBuilderBuildSync(GetHandle(), namedOperands.GetHandle());
        return Graph::Acquire(result);
    }
    Operand GraphBuilder::Clamp(Operand const& input, ClampOptions const * options) const {
        auto result = mlGraphBuilderClamp(GetHandle(), input.GetHandle(), reinterpret_cast<MLClampOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Concat(uint32_t inputsCount, Operand const * inputs, uint32_t axis) const {
        auto result = mlGraphBuilderConcat(GetHandle(), inputsCount, reinterpret_cast<MLOperand const * >(inputs), axis);
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Constant(OperandDescriptor const * desc, void const * value, size_t size) const {
        auto result = mlGraphBuilderConstant(GetHandle(), reinterpret_cast<MLOperandDescriptor const * >(desc), reinterpret_cast<void const * >(value), size);
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Conv2d(Operand const& input, Operand const& filter, Conv2dOptions const * options) const {
        auto result = mlGraphBuilderConv2d(GetHandle(), input.GetHandle(), filter.GetHandle(), reinterpret_cast<MLConv2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Gemm(Operand const& a, Operand const& b, GemmOptions const * options) const {
        auto result = mlGraphBuilderGemm(GetHandle(), a.GetHandle(), b.GetHandle(), reinterpret_cast<MLGemmOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Input(char const * name, OperandDescriptor const * desc) const {
        auto result = mlGraphBuilderInput(GetHandle(), reinterpret_cast<char const * >(name), reinterpret_cast<MLOperandDescriptor const * >(desc));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::LeakyRelu(Operand const& input, LeakyReluOptions const * options) const {
        auto result = mlGraphBuilderLeakyRelu(GetHandle(), input.GetHandle(), reinterpret_cast<MLLeakyReluOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Matmul(Operand const& a, Operand const& b) const {
        auto result = mlGraphBuilderMatmul(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::MaxPool2d(Operand const& input, Pool2dOptions const * options) const {
        auto result = mlGraphBuilderMaxPool2d(GetHandle(), input.GetHandle(), reinterpret_cast<MLPool2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Mul(Operand const& a, Operand const& b) const {
        auto result = mlGraphBuilderMul(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Relu(Operand const& input) const {
        auto result = mlGraphBuilderRelu(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Reshape(Operand const& input, int32_t const * newShape, uint32_t newShapeCount) const {
        auto result = mlGraphBuilderReshape(GetHandle(), input.GetHandle(), reinterpret_cast<int32_t const * >(newShape), newShapeCount);
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Softmax(Operand const& input) const {
        auto result = mlGraphBuilderSoftmax(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Sub(Operand const& a, Operand const& b) const {
        auto result = mlGraphBuilderSub(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Transpose(Operand const& input, TransposeOptions const * options) const {
        auto result = mlGraphBuilderTranspose(GetHandle(), input.GetHandle(), reinterpret_cast<MLTransposeOptions const * >(options));
        return Operand::Acquire(result);
    }
    void GraphBuilder::WebnnReference(MLGraphBuilder handle) {
        if (handle != nullptr) {
            mlGraphBuilderReference(handle);
        }
    }
    void GraphBuilder::WebnnRelease(MLGraphBuilder handle) {
        if (handle != nullptr) {
            mlGraphBuilderRelease(handle);
        }
    }

    // NamedInputs

    static_assert(sizeof(NamedInputs) == sizeof(MLNamedInputs), "sizeof mismatch for NamedInputs");
    static_assert(alignof(NamedInputs) == alignof(MLNamedInputs), "alignof mismatch for NamedInputs");

    void NamedInputs::Set(char const * name, Input const * input) const {
        mlNamedInputsSet(GetHandle(), reinterpret_cast<char const * >(name), reinterpret_cast<MLInput const * >(input));
    }
    void NamedInputs::WebnnReference(MLNamedInputs handle) {
        if (handle != nullptr) {
            mlNamedInputsReference(handle);
        }
    }
    void NamedInputs::WebnnRelease(MLNamedInputs handle) {
        if (handle != nullptr) {
            mlNamedInputsRelease(handle);
        }
    }

    // NamedOperands

    static_assert(sizeof(NamedOperands) == sizeof(MLNamedOperands), "sizeof mismatch for NamedOperands");
    static_assert(alignof(NamedOperands) == alignof(MLNamedOperands), "alignof mismatch for NamedOperands");

    void NamedOperands::Set(char const * name, Operand const& operand) const {
        mlNamedOperandsSet(GetHandle(), reinterpret_cast<char const * >(name), operand.GetHandle());
    }
    void NamedOperands::WebnnReference(MLNamedOperands handle) {
        if (handle != nullptr) {
            mlNamedOperandsReference(handle);
        }
    }
    void NamedOperands::WebnnRelease(MLNamedOperands handle) {
        if (handle != nullptr) {
            mlNamedOperandsRelease(handle);
        }
    }

    // NamedOutputs

    static_assert(sizeof(NamedOutputs) == sizeof(MLNamedOutputs), "sizeof mismatch for NamedOutputs");
    static_assert(alignof(NamedOutputs) == alignof(MLNamedOutputs), "alignof mismatch for NamedOutputs");

    void NamedOutputs::Set(char const * name, Output const * output) const {
        mlNamedOutputsSet(GetHandle(), reinterpret_cast<char const * >(name), reinterpret_cast<MLOutput const * >(output));
    }
    void NamedOutputs::WebnnReference(MLNamedOutputs handle) {
        if (handle != nullptr) {
            mlNamedOutputsReference(handle);
        }
    }
    void NamedOutputs::WebnnRelease(MLNamedOutputs handle) {
        if (handle != nullptr) {
            mlNamedOutputsRelease(handle);
        }
    }

    // NamedResults

    static_assert(sizeof(NamedResults) == sizeof(MLNamedResults), "sizeof mismatch for NamedResults");
    static_assert(alignof(NamedResults) == alignof(MLNamedResults), "alignof mismatch for NamedResults");

    Result NamedResults::Get(char const * name) const {
        auto result = mlNamedResultsGet(GetHandle(), reinterpret_cast<char const * >(name));
        return Result::Acquire(result);
    }
    void NamedResults::WebnnReference(MLNamedResults handle) {
        if (handle != nullptr) {
            mlNamedResultsReference(handle);
        }
    }
    void NamedResults::WebnnRelease(MLNamedResults handle) {
        if (handle != nullptr) {
            mlNamedResultsRelease(handle);
        }
    }

    // Operand

    static_assert(sizeof(Operand) == sizeof(MLOperand), "sizeof mismatch for Operand");
    static_assert(alignof(Operand) == alignof(MLOperand), "alignof mismatch for Operand");

    void Operand::WebnnReference(MLOperand handle) {
        if (handle != nullptr) {
            mlOperandReference(handle);
        }
    }
    void Operand::WebnnRelease(MLOperand handle) {
        if (handle != nullptr) {
            mlOperandRelease(handle);
        }
    }

    // Result

    static_assert(sizeof(Result) == sizeof(MLResult), "sizeof mismatch for Result");
    static_assert(alignof(Result) == alignof(MLResult), "alignof mismatch for Result");

    const void* Result::Buffer() const {
        auto result = mlResultBuffer(GetHandle());
        return result;
    }
    uint32_t Result::BufferSize() const {
        auto result = mlResultBufferSize(GetHandle());
        return result;
    }
    const int32_t* Result::Dimensions() const {
        auto result = mlResultDimensions(GetHandle());
        return result;
    }
    uint32_t Result::DimensionsSize() const {
        auto result = mlResultDimensionsSize(GetHandle());
        return result;
    }
    void Result::WebnnReference(MLResult handle) {
        if (handle != nullptr) {
            mlResultReference(handle);
        }
    }
    void Result::WebnnRelease(MLResult handle) {
        if (handle != nullptr) {
            mlResultRelease(handle);
        }
    }

    GraphBuilder CreateGraphBuilder(Context context) {
        return GraphBuilder::Acquire(webnnCreateGraphBuilder(context.GetHandle()));
    }

    NamedInputs CreateNamedInputs() {
        return NamedInputs::Acquire(webnnCreateNamedInputs());
    }

    NamedOperands CreateNamedOperands() {
        return NamedOperands::Acquire(webnnCreateNamedOperands());
    }

    NamedOutputs CreateNamedOutputs() {
        return NamedOutputs::Acquire(webnnCreateNamedOutputs());
    }

}
