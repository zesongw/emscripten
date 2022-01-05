#include "webnn/webnn_cpp.h"

namespace ml {

    // AutoPad

    static_assert(sizeof(AutoPad) == sizeof(MLAutoPad), "sizeof mismatch for AutoPad");
    static_assert(alignof(AutoPad) == alignof(MLAutoPad), "alignof mismatch for AutoPad");

    static_assert(static_cast<uint32_t>(AutoPad::Explicit) == MLAutoPad_Explicit, "value mismatch for AutoPad::Explicit");
    static_assert(static_cast<uint32_t>(AutoPad::SameUpper) == MLAutoPad_SameUpper, "value mismatch for AutoPad::SameUpper");
    static_assert(static_cast<uint32_t>(AutoPad::SameLower) == MLAutoPad_SameLower, "value mismatch for AutoPad::SameLower");

    // ComputeGraphStatus

    static_assert(sizeof(ComputeGraphStatus) == sizeof(MLComputeGraphStatus), "sizeof mismatch for ComputeGraphStatus");
    static_assert(alignof(ComputeGraphStatus) == alignof(MLComputeGraphStatus), "alignof mismatch for ComputeGraphStatus");

    static_assert(static_cast<uint32_t>(ComputeGraphStatus::Success) == MLComputeGraphStatus_Success, "value mismatch for ComputeGraphStatus::Success");
    static_assert(static_cast<uint32_t>(ComputeGraphStatus::Error) == MLComputeGraphStatus_Error, "value mismatch for ComputeGraphStatus::Error");
    static_assert(static_cast<uint32_t>(ComputeGraphStatus::ContextLost) == MLComputeGraphStatus_ContextLost, "value mismatch for ComputeGraphStatus::ContextLost");
    static_assert(static_cast<uint32_t>(ComputeGraphStatus::Unknown) == MLComputeGraphStatus_Unknown, "value mismatch for ComputeGraphStatus::Unknown");

    // DevicePreference

    static_assert(sizeof(DevicePreference) == sizeof(MLDevicePreference), "sizeof mismatch for DevicePreference");
    static_assert(alignof(DevicePreference) == alignof(MLDevicePreference), "alignof mismatch for DevicePreference");

    static_assert(static_cast<uint32_t>(DevicePreference::Default) == MLDevicePreference_Default, "value mismatch for DevicePreference::Default");
    static_assert(static_cast<uint32_t>(DevicePreference::Gpu) == MLDevicePreference_Gpu, "value mismatch for DevicePreference::Gpu");
    static_assert(static_cast<uint32_t>(DevicePreference::Cpu) == MLDevicePreference_Cpu, "value mismatch for DevicePreference::Cpu");

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

    // InputOperandLayout

    static_assert(sizeof(InputOperandLayout) == sizeof(MLInputOperandLayout), "sizeof mismatch for InputOperandLayout");
    static_assert(alignof(InputOperandLayout) == alignof(MLInputOperandLayout), "alignof mismatch for InputOperandLayout");

    static_assert(static_cast<uint32_t>(InputOperandLayout::Nchw) == MLInputOperandLayout_Nchw, "value mismatch for InputOperandLayout::Nchw");
    static_assert(static_cast<uint32_t>(InputOperandLayout::Nhwc) == MLInputOperandLayout_Nhwc, "value mismatch for InputOperandLayout::Nhwc");

    // InterpolationMode

    static_assert(sizeof(InterpolationMode) == sizeof(MLInterpolationMode), "sizeof mismatch for InterpolationMode");
    static_assert(alignof(InterpolationMode) == alignof(MLInterpolationMode), "alignof mismatch for InterpolationMode");

    static_assert(static_cast<uint32_t>(InterpolationMode::NearestNeighbor) == MLInterpolationMode_NearestNeighbor, "value mismatch for InterpolationMode::NearestNeighbor");
    static_assert(static_cast<uint32_t>(InterpolationMode::Linear) == MLInterpolationMode_Linear, "value mismatch for InterpolationMode::Linear");

    // OperandType

    static_assert(sizeof(OperandType) == sizeof(MLOperandType), "sizeof mismatch for OperandType");
    static_assert(alignof(OperandType) == alignof(MLOperandType), "alignof mismatch for OperandType");

    static_assert(static_cast<uint32_t>(OperandType::Float32) == MLOperandType_Float32, "value mismatch for OperandType::Float32");
    static_assert(static_cast<uint32_t>(OperandType::Float16) == MLOperandType_Float16, "value mismatch for OperandType::Float16");
    static_assert(static_cast<uint32_t>(OperandType::Int32) == MLOperandType_Int32, "value mismatch for OperandType::Int32");
    static_assert(static_cast<uint32_t>(OperandType::Uint32) == MLOperandType_Uint32, "value mismatch for OperandType::Uint32");
    static_assert(static_cast<uint32_t>(OperandType::Int8) == MLOperandType_Int8, "value mismatch for OperandType::Int8");
    static_assert(static_cast<uint32_t>(OperandType::Uint8) == MLOperandType_Uint8, "value mismatch for OperandType::Uint8");

    // PaddingMode

    static_assert(sizeof(PaddingMode) == sizeof(MLPaddingMode), "sizeof mismatch for PaddingMode");
    static_assert(alignof(PaddingMode) == alignof(MLPaddingMode), "alignof mismatch for PaddingMode");

    static_assert(static_cast<uint32_t>(PaddingMode::Constant) == MLPaddingMode_Constant, "value mismatch for PaddingMode::Constant");
    static_assert(static_cast<uint32_t>(PaddingMode::Edge) == MLPaddingMode_Edge, "value mismatch for PaddingMode::Edge");
    static_assert(static_cast<uint32_t>(PaddingMode::Reflection) == MLPaddingMode_Reflection, "value mismatch for PaddingMode::Reflection");
    static_assert(static_cast<uint32_t>(PaddingMode::Symmetric) == MLPaddingMode_Symmetric, "value mismatch for PaddingMode::Symmetric");

    // PowerPreference

    static_assert(sizeof(PowerPreference) == sizeof(MLPowerPreference), "sizeof mismatch for PowerPreference");
    static_assert(alignof(PowerPreference) == alignof(MLPowerPreference), "alignof mismatch for PowerPreference");

    static_assert(static_cast<uint32_t>(PowerPreference::Default) == MLPowerPreference_Default, "value mismatch for PowerPreference::Default");
    static_assert(static_cast<uint32_t>(PowerPreference::High_performance) == MLPowerPreference_High_performance, "value mismatch for PowerPreference::High_performance");
    static_assert(static_cast<uint32_t>(PowerPreference::Low_power) == MLPowerPreference_Low_power, "value mismatch for PowerPreference::Low_power");

    // RecurrentNetworkDirection

    static_assert(sizeof(RecurrentNetworkDirection) == sizeof(MLRecurrentNetworkDirection), "sizeof mismatch for RecurrentNetworkDirection");
    static_assert(alignof(RecurrentNetworkDirection) == alignof(MLRecurrentNetworkDirection), "alignof mismatch for RecurrentNetworkDirection");

    static_assert(static_cast<uint32_t>(RecurrentNetworkDirection::Forward) == MLRecurrentNetworkDirection_Forward, "value mismatch for RecurrentNetworkDirection::Forward");
    static_assert(static_cast<uint32_t>(RecurrentNetworkDirection::Backward) == MLRecurrentNetworkDirection_Backward, "value mismatch for RecurrentNetworkDirection::Backward");
    static_assert(static_cast<uint32_t>(RecurrentNetworkDirection::Both) == MLRecurrentNetworkDirection_Both, "value mismatch for RecurrentNetworkDirection::Both");

    // RecurrentNetworkWeightLayout

    static_assert(sizeof(RecurrentNetworkWeightLayout) == sizeof(MLRecurrentNetworkWeightLayout), "sizeof mismatch for RecurrentNetworkWeightLayout");
    static_assert(alignof(RecurrentNetworkWeightLayout) == alignof(MLRecurrentNetworkWeightLayout), "alignof mismatch for RecurrentNetworkWeightLayout");

    static_assert(static_cast<uint32_t>(RecurrentNetworkWeightLayout::Zrn) == MLRecurrentNetworkWeightLayout_Zrn, "value mismatch for RecurrentNetworkWeightLayout::Zrn");
    static_assert(static_cast<uint32_t>(RecurrentNetworkWeightLayout::Rzn) == MLRecurrentNetworkWeightLayout_Rzn, "value mismatch for RecurrentNetworkWeightLayout::Rzn");

    // ChainedStruct


    // ArrayBufferView

    static_assert(sizeof(ArrayBufferView) == sizeof(MLArrayBufferView), "sizeof mismatch for ArrayBufferView");
    static_assert(alignof(ArrayBufferView) == alignof(MLArrayBufferView), "alignof mismatch for ArrayBufferView");

    static_assert(offsetof(ArrayBufferView, buffer) == offsetof(MLArrayBufferView, buffer),
            "offsetof mismatch for ArrayBufferView::buffer");
    static_assert(offsetof(ArrayBufferView, byteLength) == offsetof(MLArrayBufferView, byteLength),
            "offsetof mismatch for ArrayBufferView::byteLength");
    static_assert(offsetof(ArrayBufferView, byteOffset) == offsetof(MLArrayBufferView, byteOffset),
            "offsetof mismatch for ArrayBufferView::byteOffset");

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

    static_assert(offsetof(ContextOptions, devicePreference) == offsetof(MLContextOptions, devicePreference),
            "offsetof mismatch for ContextOptions::devicePreference");
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
    static_assert(offsetof(Conv2dOptions, outputPaddingCount) == offsetof(MLConv2dOptions, outputPaddingCount),
            "offsetof mismatch for Conv2dOptions::outputPaddingCount");
    static_assert(offsetof(Conv2dOptions, outputPadding) == offsetof(MLConv2dOptions, outputPadding),
            "offsetof mismatch for Conv2dOptions::outputPadding");
    static_assert(offsetof(Conv2dOptions, outputSizesCount) == offsetof(MLConv2dOptions, outputSizesCount),
            "offsetof mismatch for Conv2dOptions::outputSizesCount");
    static_assert(offsetof(Conv2dOptions, outputSizes) == offsetof(MLConv2dOptions, outputSizes),
            "offsetof mismatch for Conv2dOptions::outputSizes");
    static_assert(offsetof(Conv2dOptions, autoPad) == offsetof(MLConv2dOptions, autoPad),
            "offsetof mismatch for Conv2dOptions::autoPad");
    static_assert(offsetof(Conv2dOptions, transpose) == offsetof(MLConv2dOptions, transpose),
            "offsetof mismatch for Conv2dOptions::transpose");
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

    // GruOptions

    static_assert(sizeof(GruOptions) == sizeof(MLGruOptions), "sizeof mismatch for GruOptions");
    static_assert(alignof(GruOptions) == alignof(MLGruOptions), "alignof mismatch for GruOptions");

    static_assert(offsetof(GruOptions, bias) == offsetof(MLGruOptions, bias),
            "offsetof mismatch for GruOptions::bias");
    static_assert(offsetof(GruOptions, recurrentBias) == offsetof(MLGruOptions, recurrentBias),
            "offsetof mismatch for GruOptions::recurrentBias");
    static_assert(offsetof(GruOptions, initialHiddenState) == offsetof(MLGruOptions, initialHiddenState),
            "offsetof mismatch for GruOptions::initialHiddenState");
    static_assert(offsetof(GruOptions, resetAfter) == offsetof(MLGruOptions, resetAfter),
            "offsetof mismatch for GruOptions::resetAfter");
    static_assert(offsetof(GruOptions, returnSequence) == offsetof(MLGruOptions, returnSequence),
            "offsetof mismatch for GruOptions::returnSequence");
    static_assert(offsetof(GruOptions, direction) == offsetof(MLGruOptions, direction),
            "offsetof mismatch for GruOptions::direction");
    static_assert(offsetof(GruOptions, layout) == offsetof(MLGruOptions, layout),
            "offsetof mismatch for GruOptions::layout");
    static_assert(offsetof(GruOptions, activations) == offsetof(MLGruOptions, activations),
            "offsetof mismatch for GruOptions::activations");

    // InstanceNormOptions

    static_assert(sizeof(InstanceNormOptions) == sizeof(MLInstanceNormOptions), "sizeof mismatch for InstanceNormOptions");
    static_assert(alignof(InstanceNormOptions) == alignof(MLInstanceNormOptions), "alignof mismatch for InstanceNormOptions");

    static_assert(offsetof(InstanceNormOptions, scale) == offsetof(MLInstanceNormOptions, scale),
            "offsetof mismatch for InstanceNormOptions::scale");
    static_assert(offsetof(InstanceNormOptions, bias) == offsetof(MLInstanceNormOptions, bias),
            "offsetof mismatch for InstanceNormOptions::bias");
    static_assert(offsetof(InstanceNormOptions, epsilon) == offsetof(MLInstanceNormOptions, epsilon),
            "offsetof mismatch for InstanceNormOptions::epsilon");
    static_assert(offsetof(InstanceNormOptions, layout) == offsetof(MLInstanceNormOptions, layout),
            "offsetof mismatch for InstanceNormOptions::layout");

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

    // PadOptions

    static_assert(sizeof(PadOptions) == sizeof(MLPadOptions), "sizeof mismatch for PadOptions");
    static_assert(alignof(PadOptions) == alignof(MLPadOptions), "alignof mismatch for PadOptions");

    static_assert(offsetof(PadOptions, mode) == offsetof(MLPadOptions, mode),
            "offsetof mismatch for PadOptions::mode");
    static_assert(offsetof(PadOptions, value) == offsetof(MLPadOptions, value),
            "offsetof mismatch for PadOptions::value");

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

    // ReduceOptions

    static_assert(sizeof(ReduceOptions) == sizeof(MLReduceOptions), "sizeof mismatch for ReduceOptions");
    static_assert(alignof(ReduceOptions) == alignof(MLReduceOptions), "alignof mismatch for ReduceOptions");

    static_assert(offsetof(ReduceOptions, axesCount) == offsetof(MLReduceOptions, axesCount),
            "offsetof mismatch for ReduceOptions::axesCount");
    static_assert(offsetof(ReduceOptions, axes) == offsetof(MLReduceOptions, axes),
            "offsetof mismatch for ReduceOptions::axes");
    static_assert(offsetof(ReduceOptions, keepDimensions) == offsetof(MLReduceOptions, keepDimensions),
            "offsetof mismatch for ReduceOptions::keepDimensions");

    // Resample2dOptions

    static_assert(sizeof(Resample2dOptions) == sizeof(MLResample2dOptions), "sizeof mismatch for Resample2dOptions");
    static_assert(alignof(Resample2dOptions) == alignof(MLResample2dOptions), "alignof mismatch for Resample2dOptions");

    static_assert(offsetof(Resample2dOptions, mode) == offsetof(MLResample2dOptions, mode),
            "offsetof mismatch for Resample2dOptions::mode");
    static_assert(offsetof(Resample2dOptions, scalesCount) == offsetof(MLResample2dOptions, scalesCount),
            "offsetof mismatch for Resample2dOptions::scalesCount");
    static_assert(offsetof(Resample2dOptions, scales) == offsetof(MLResample2dOptions, scales),
            "offsetof mismatch for Resample2dOptions::scales");
    static_assert(offsetof(Resample2dOptions, sizesCount) == offsetof(MLResample2dOptions, sizesCount),
            "offsetof mismatch for Resample2dOptions::sizesCount");
    static_assert(offsetof(Resample2dOptions, sizes) == offsetof(MLResample2dOptions, sizes),
            "offsetof mismatch for Resample2dOptions::sizes");
    static_assert(offsetof(Resample2dOptions, axesCount) == offsetof(MLResample2dOptions, axesCount),
            "offsetof mismatch for Resample2dOptions::axesCount");
    static_assert(offsetof(Resample2dOptions, axes) == offsetof(MLResample2dOptions, axes),
            "offsetof mismatch for Resample2dOptions::axes");

    // SliceOptions

    static_assert(sizeof(SliceOptions) == sizeof(MLSliceOptions), "sizeof mismatch for SliceOptions");
    static_assert(alignof(SliceOptions) == alignof(MLSliceOptions), "alignof mismatch for SliceOptions");

    static_assert(offsetof(SliceOptions, axesCount) == offsetof(MLSliceOptions, axesCount),
            "offsetof mismatch for SliceOptions::axesCount");
    static_assert(offsetof(SliceOptions, axes) == offsetof(MLSliceOptions, axes),
            "offsetof mismatch for SliceOptions::axes");

    // SplitOptions

    static_assert(sizeof(SplitOptions) == sizeof(MLSplitOptions), "sizeof mismatch for SplitOptions");
    static_assert(alignof(SplitOptions) == alignof(MLSplitOptions), "alignof mismatch for SplitOptions");

    static_assert(offsetof(SplitOptions, axis) == offsetof(MLSplitOptions, axis),
            "offsetof mismatch for SplitOptions::axis");

    // SqueezeOptions

    static_assert(sizeof(SqueezeOptions) == sizeof(MLSqueezeOptions), "sizeof mismatch for SqueezeOptions");
    static_assert(alignof(SqueezeOptions) == alignof(MLSqueezeOptions), "alignof mismatch for SqueezeOptions");

    static_assert(offsetof(SqueezeOptions, axesCount) == offsetof(MLSqueezeOptions, axesCount),
            "offsetof mismatch for SqueezeOptions::axesCount");
    static_assert(offsetof(SqueezeOptions, axes) == offsetof(MLSqueezeOptions, axes),
            "offsetof mismatch for SqueezeOptions::axes");

    // TransposeOptions

    static_assert(sizeof(TransposeOptions) == sizeof(MLTransposeOptions), "sizeof mismatch for TransposeOptions");
    static_assert(alignof(TransposeOptions) == alignof(MLTransposeOptions), "alignof mismatch for TransposeOptions");

    static_assert(offsetof(TransposeOptions, permutationCount) == offsetof(MLTransposeOptions, permutationCount),
            "offsetof mismatch for TransposeOptions::permutationCount");
    static_assert(offsetof(TransposeOptions, permutation) == offsetof(MLTransposeOptions, permutation),
            "offsetof mismatch for TransposeOptions::permutation");

    // Input

    static_assert(sizeof(Input) == sizeof(MLInput), "sizeof mismatch for Input");
    static_assert(alignof(Input) == alignof(MLInput), "alignof mismatch for Input");

    static_assert(offsetof(Input, resource) == offsetof(MLInput, resource),
            "offsetof mismatch for Input::resource");
    static_assert(offsetof(Input, dimensions) == offsetof(MLInput, dimensions),
            "offsetof mismatch for Input::dimensions");
    static_assert(offsetof(Input, dimensionsCount) == offsetof(MLInput, dimensionsCount),
            "offsetof mismatch for Input::dimensionsCount");

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

    ComputeGraphStatus Graph::Compute(NamedInputs const& inputs, NamedOutputs const& outputs) const {
        auto result = mlGraphCompute(GetHandle(), inputs.GetHandle(), outputs.GetHandle());
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

    Operand GraphBuilder::Abs(Operand const& input) const {
        auto result = mlGraphBuilderAbs(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
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
    Graph GraphBuilder::Build(NamedOperands const& namedOperands) const {
        auto result = mlGraphBuilderBuild(GetHandle(), namedOperands.GetHandle());
        return Graph::Acquire(result);
    }
    Operand GraphBuilder::Ceil(Operand const& input) const {
        auto result = mlGraphBuilderCeil(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Clamp(Operand const& input, ClampOptions const * options) const {
        auto result = mlGraphBuilderClamp(GetHandle(), input.GetHandle(), reinterpret_cast<MLClampOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operator GraphBuilder::ClampOperator(ClampOptions const * options) const {
        auto result = mlGraphBuilderClampOperator(GetHandle(), reinterpret_cast<MLClampOptions const * >(options));
        return Operator::Acquire(result);
    }
    Operand GraphBuilder::Concat(uint32_t inputsCount, Operand const * inputs, uint32_t axis) const {
        auto result = mlGraphBuilderConcat(GetHandle(), inputsCount, reinterpret_cast<MLOperand const * >(inputs), axis);
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Constant(OperandDescriptor const * desc, ArrayBufferView const * value) const {
        auto result = mlGraphBuilderConstant(GetHandle(), reinterpret_cast<MLOperandDescriptor const * >(desc), reinterpret_cast<MLArrayBufferView const * >(value));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Conv2d(Operand const& input, Operand const& filter, Conv2dOptions const * options) const {
        auto result = mlGraphBuilderConv2d(GetHandle(), input.GetHandle(), filter.GetHandle(), reinterpret_cast<MLConv2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Cos(Operand const& input) const {
        auto result = mlGraphBuilderCos(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Div(Operand const& a, Operand const& b) const {
        auto result = mlGraphBuilderDiv(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Exp(Operand const& input) const {
        auto result = mlGraphBuilderExp(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Floor(Operand const& input) const {
        auto result = mlGraphBuilderFloor(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Gemm(Operand const& a, Operand const& b, GemmOptions const * options) const {
        auto result = mlGraphBuilderGemm(GetHandle(), a.GetHandle(), b.GetHandle(), reinterpret_cast<MLGemmOptions const * >(options));
        return Operand::Acquire(result);
    }
    OperandArray GraphBuilder::Gru(Operand const& input, Operand const& weight, Operand const& recurrentWeight, int32_t steps, int32_t hiddenSize, GruOptions const * options) const {
        auto result = mlGraphBuilderGru(GetHandle(), input.GetHandle(), weight.GetHandle(), recurrentWeight.GetHandle(), steps, hiddenSize, reinterpret_cast<MLGruOptions const * >(options));
        return OperandArray::Acquire(result);
    }
    Operand GraphBuilder::HardSwish(Operand const& input) const {
        auto result = mlGraphBuilderHardSwish(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operator GraphBuilder::HardSwishOperator() const {
        auto result = mlGraphBuilderHardSwishOperator(GetHandle());
        return Operator::Acquire(result);
    }
    Operand GraphBuilder::Input(char const * name, OperandDescriptor const * desc) const {
        auto result = mlGraphBuilderInput(GetHandle(), reinterpret_cast<char const * >(name), reinterpret_cast<MLOperandDescriptor const * >(desc));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::InstanceNorm(Operand const& input, InstanceNormOptions const * options) const {
        auto result = mlGraphBuilderInstanceNorm(GetHandle(), input.GetHandle(), reinterpret_cast<MLInstanceNormOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::L2Pool2d(Operand const& input, Pool2dOptions const * options) const {
        auto result = mlGraphBuilderL2Pool2d(GetHandle(), input.GetHandle(), reinterpret_cast<MLPool2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::LeakyRelu(Operand const& input, LeakyReluOptions const * options) const {
        auto result = mlGraphBuilderLeakyRelu(GetHandle(), input.GetHandle(), reinterpret_cast<MLLeakyReluOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operator GraphBuilder::LeakyReluOperator(LeakyReluOptions const * options) const {
        auto result = mlGraphBuilderLeakyReluOperator(GetHandle(), reinterpret_cast<MLLeakyReluOptions const * >(options));
        return Operator::Acquire(result);
    }
    Operand GraphBuilder::Log(Operand const& input) const {
        auto result = mlGraphBuilderLog(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Matmul(Operand const& a, Operand const& b) const {
        auto result = mlGraphBuilderMatmul(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Max(Operand const& a, Operand const& b) const {
        auto result = mlGraphBuilderMax(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::MaxPool2d(Operand const& input, Pool2dOptions const * options) const {
        auto result = mlGraphBuilderMaxPool2d(GetHandle(), input.GetHandle(), reinterpret_cast<MLPool2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Min(Operand const& a, Operand const& b) const {
        auto result = mlGraphBuilderMin(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Mul(Operand const& a, Operand const& b) const {
        auto result = mlGraphBuilderMul(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Neg(Operand const& input) const {
        auto result = mlGraphBuilderNeg(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Pad(Operand const& input, Operand const& padding, PadOptions const * options) const {
        auto result = mlGraphBuilderPad(GetHandle(), input.GetHandle(), padding.GetHandle(), reinterpret_cast<MLPadOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Pow(Operand const& a, Operand const& b) const {
        auto result = mlGraphBuilderPow(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceL1(Operand const& input, ReduceOptions const * options) const {
        auto result = mlGraphBuilderReduceL1(GetHandle(), input.GetHandle(), reinterpret_cast<MLReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceL2(Operand const& input, ReduceOptions const * options) const {
        auto result = mlGraphBuilderReduceL2(GetHandle(), input.GetHandle(), reinterpret_cast<MLReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceMax(Operand const& input, ReduceOptions const * options) const {
        auto result = mlGraphBuilderReduceMax(GetHandle(), input.GetHandle(), reinterpret_cast<MLReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceMean(Operand const& input, ReduceOptions const * options) const {
        auto result = mlGraphBuilderReduceMean(GetHandle(), input.GetHandle(), reinterpret_cast<MLReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceMin(Operand const& input, ReduceOptions const * options) const {
        auto result = mlGraphBuilderReduceMin(GetHandle(), input.GetHandle(), reinterpret_cast<MLReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceProduct(Operand const& input, ReduceOptions const * options) const {
        auto result = mlGraphBuilderReduceProduct(GetHandle(), input.GetHandle(), reinterpret_cast<MLReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceSum(Operand const& input, ReduceOptions const * options) const {
        auto result = mlGraphBuilderReduceSum(GetHandle(), input.GetHandle(), reinterpret_cast<MLReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Relu(Operand const& input) const {
        auto result = mlGraphBuilderRelu(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operator GraphBuilder::ReluOperator() const {
        auto result = mlGraphBuilderReluOperator(GetHandle());
        return Operator::Acquire(result);
    }
    Operand GraphBuilder::Resample2d(Operand const& input, Resample2dOptions const * options) const {
        auto result = mlGraphBuilderResample2d(GetHandle(), input.GetHandle(), reinterpret_cast<MLResample2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Reshape(Operand const& input, int32_t const * newShape, uint32_t newShapeCount) const {
        auto result = mlGraphBuilderReshape(GetHandle(), input.GetHandle(), reinterpret_cast<int32_t const * >(newShape), newShapeCount);
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Sigmoid(Operand const& input) const {
        auto result = mlGraphBuilderSigmoid(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operator GraphBuilder::SigmoidOperator() const {
        auto result = mlGraphBuilderSigmoidOperator(GetHandle());
        return Operator::Acquire(result);
    }
    Operand GraphBuilder::Sin(Operand const& input) const {
        auto result = mlGraphBuilderSin(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Slice(Operand const& input, int32_t const * starts, uint32_t startsCount, int32_t const * sizes, uint32_t sizesCount, SliceOptions const * options) const {
        auto result = mlGraphBuilderSlice(GetHandle(), input.GetHandle(), reinterpret_cast<int32_t const * >(starts), startsCount, reinterpret_cast<int32_t const * >(sizes), sizesCount, reinterpret_cast<MLSliceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Softmax(Operand const& input) const {
        auto result = mlGraphBuilderSoftmax(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    OperandArray GraphBuilder::Split(Operand const& input, uint32_t const * splits, uint32_t splitsCount, SplitOptions const * options) const {
        auto result = mlGraphBuilderSplit(GetHandle(), input.GetHandle(), reinterpret_cast<uint32_t const * >(splits), splitsCount, reinterpret_cast<MLSplitOptions const * >(options));
        return OperandArray::Acquire(result);
    }
    Operand GraphBuilder::Squeeze(Operand const& input, SqueezeOptions const * options) const {
        auto result = mlGraphBuilderSqueeze(GetHandle(), input.GetHandle(), reinterpret_cast<MLSqueezeOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Sub(Operand const& a, Operand const& b) const {
        auto result = mlGraphBuilderSub(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Tan(Operand const& input) const {
        auto result = mlGraphBuilderTan(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Tanh(Operand const& input) const {
        auto result = mlGraphBuilderTanh(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operator GraphBuilder::TanhOperator() const {
        auto result = mlGraphBuilderTanhOperator(GetHandle());
        return Operator::Acquire(result);
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

    void NamedOutputs::Set(char const * name, ArrayBufferView const * resource) const {
        mlNamedOutputsSet(GetHandle(), reinterpret_cast<char const * >(name), reinterpret_cast<MLArrayBufferView const * >(resource));
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

    // OperandArray

    static_assert(sizeof(OperandArray) == sizeof(MLOperandArray), "sizeof mismatch for OperandArray");
    static_assert(alignof(OperandArray) == alignof(MLOperandArray), "alignof mismatch for OperandArray");

    Operand OperandArray::Get(size_t index) const {
        auto result = mlOperandArrayGet(GetHandle(), index);
        return Operand::Acquire(result);
    }
    size_t OperandArray::Size() const {
        auto result = mlOperandArraySize(GetHandle());
        return result;
    }
    void OperandArray::WebnnReference(MLOperandArray handle) {
        if (handle != nullptr) {
            mlOperandArrayReference(handle);
        }
    }
    void OperandArray::WebnnRelease(MLOperandArray handle) {
        if (handle != nullptr) {
            mlOperandArrayRelease(handle);
        }
    }

    // Operator

    static_assert(sizeof(Operator) == sizeof(MLOperator), "sizeof mismatch for Operator");
    static_assert(alignof(Operator) == alignof(MLOperator), "alignof mismatch for Operator");

    void Operator::WebnnReference(MLOperator handle) {
        if (handle != nullptr) {
            mlOperatorReference(handle);
        }
    }
    void Operator::WebnnRelease(MLOperator handle) {
        if (handle != nullptr) {
            mlOperatorRelease(handle);
        }
    }

    // OperatorArray

    static_assert(sizeof(OperatorArray) == sizeof(MLOperatorArray), "sizeof mismatch for OperatorArray");
    static_assert(alignof(OperatorArray) == alignof(MLOperatorArray), "alignof mismatch for OperatorArray");

    Operator OperatorArray::Get(size_t index) const {
        auto result = mlOperatorArrayGet(GetHandle(), index);
        return Operator::Acquire(result);
    }
    void OperatorArray::Set(Operator const& mlOperator) const {
        mlOperatorArraySet(GetHandle(), mlOperator.GetHandle());
    }
    size_t OperatorArray::Size() const {
        auto result = mlOperatorArraySize(GetHandle());
        return result;
    }
    void OperatorArray::WebnnReference(MLOperatorArray handle) {
        if (handle != nullptr) {
            mlOperatorArrayReference(handle);
        }
    }
    void OperatorArray::WebnnRelease(MLOperatorArray handle) {
        if (handle != nullptr) {
            mlOperatorArrayRelease(handle);
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

    OperatorArray CreateOperatorArray() {
        return OperatorArray::Acquire(webnnCreateOperatorArray());
    }

}
