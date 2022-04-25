#include "webnn/webnn_cpp.h"

namespace wnn {

    // AutoPad

    static_assert(sizeof(AutoPad) == sizeof(WNNAutoPad), "sizeof mismatch for AutoPad");
    static_assert(alignof(AutoPad) == alignof(WNNAutoPad), "alignof mismatch for AutoPad");

    static_assert(static_cast<uint32_t>(AutoPad::Explicit) == WNNAutoPad_Explicit, "value mismatch for AutoPad::Explicit");
    static_assert(static_cast<uint32_t>(AutoPad::SameUpper) == WNNAutoPad_SameUpper, "value mismatch for AutoPad::SameUpper");
    static_assert(static_cast<uint32_t>(AutoPad::SameLower) == WNNAutoPad_SameLower, "value mismatch for AutoPad::SameLower");

    // BackendType

    static_assert(sizeof(BackendType) == sizeof(WNNBackendType), "sizeof mismatch for BackendType");
    static_assert(alignof(BackendType) == alignof(WNNBackendType), "alignof mismatch for BackendType");

    static_assert(static_cast<uint32_t>(BackendType::Null) == WNNBackendType_Null, "value mismatch for BackendType::Null");
    static_assert(static_cast<uint32_t>(BackendType::DirectML) == WNNBackendType_DirectML, "value mismatch for BackendType::DirectML");
    static_assert(static_cast<uint32_t>(BackendType::OpenVINO) == WNNBackendType_OpenVINO, "value mismatch for BackendType::OpenVINO");
    static_assert(static_cast<uint32_t>(BackendType::OneDNN) == WNNBackendType_OneDNN, "value mismatch for BackendType::OneDNN");
    static_assert(static_cast<uint32_t>(BackendType::MLAS) == WNNBackendType_MLAS, "value mismatch for BackendType::MLAS");
    static_assert(static_cast<uint32_t>(BackendType::XNNPACK) == WNNBackendType_XNNPACK, "value mismatch for BackendType::XNNPACK");

    // ConvTranspose2dFilterOperandLayout

    static_assert(sizeof(ConvTranspose2dFilterOperandLayout) == sizeof(WNNConvTranspose2dFilterOperandLayout), "sizeof mismatch for ConvTranspose2dFilterOperandLayout");
    static_assert(alignof(ConvTranspose2dFilterOperandLayout) == alignof(WNNConvTranspose2dFilterOperandLayout), "alignof mismatch for ConvTranspose2dFilterOperandLayout");

    static_assert(static_cast<uint32_t>(ConvTranspose2dFilterOperandLayout::Iohw) == WNNConvTranspose2dFilterOperandLayout_Iohw, "value mismatch for ConvTranspose2dFilterOperandLayout::Iohw");
    static_assert(static_cast<uint32_t>(ConvTranspose2dFilterOperandLayout::Hwoi) == WNNConvTranspose2dFilterOperandLayout_Hwoi, "value mismatch for ConvTranspose2dFilterOperandLayout::Hwoi");
    static_assert(static_cast<uint32_t>(ConvTranspose2dFilterOperandLayout::Ohwi) == WNNConvTranspose2dFilterOperandLayout_Ohwi, "value mismatch for ConvTranspose2dFilterOperandLayout::Ohwi");

    // Conv2dFilterOperandLayout

    static_assert(sizeof(Conv2dFilterOperandLayout) == sizeof(WNNConv2dFilterOperandLayout), "sizeof mismatch for Conv2dFilterOperandLayout");
    static_assert(alignof(Conv2dFilterOperandLayout) == alignof(WNNConv2dFilterOperandLayout), "alignof mismatch for Conv2dFilterOperandLayout");

    static_assert(static_cast<uint32_t>(Conv2dFilterOperandLayout::Oihw) == WNNConv2dFilterOperandLayout_Oihw, "value mismatch for Conv2dFilterOperandLayout::Oihw");
    static_assert(static_cast<uint32_t>(Conv2dFilterOperandLayout::Hwio) == WNNConv2dFilterOperandLayout_Hwio, "value mismatch for Conv2dFilterOperandLayout::Hwio");
    static_assert(static_cast<uint32_t>(Conv2dFilterOperandLayout::Ohwi) == WNNConv2dFilterOperandLayout_Ohwi, "value mismatch for Conv2dFilterOperandLayout::Ohwi");
    static_assert(static_cast<uint32_t>(Conv2dFilterOperandLayout::Ihwo) == WNNConv2dFilterOperandLayout_Ihwo, "value mismatch for Conv2dFilterOperandLayout::Ihwo");

    // DevicePreference

    static_assert(sizeof(DevicePreference) == sizeof(WNNDevicePreference), "sizeof mismatch for DevicePreference");
    static_assert(alignof(DevicePreference) == alignof(WNNDevicePreference), "alignof mismatch for DevicePreference");

    static_assert(static_cast<uint32_t>(DevicePreference::Default) == WNNDevicePreference_Default, "value mismatch for DevicePreference::Default");
    static_assert(static_cast<uint32_t>(DevicePreference::Gpu) == WNNDevicePreference_Gpu, "value mismatch for DevicePreference::Gpu");
    static_assert(static_cast<uint32_t>(DevicePreference::Cpu) == WNNDevicePreference_Cpu, "value mismatch for DevicePreference::Cpu");

    // ErrorFilter

    static_assert(sizeof(ErrorFilter) == sizeof(WNNErrorFilter), "sizeof mismatch for ErrorFilter");
    static_assert(alignof(ErrorFilter) == alignof(WNNErrorFilter), "alignof mismatch for ErrorFilter");

    static_assert(static_cast<uint32_t>(ErrorFilter::None) == WNNErrorFilter_None, "value mismatch for ErrorFilter::None");
    static_assert(static_cast<uint32_t>(ErrorFilter::Validation) == WNNErrorFilter_Validation, "value mismatch for ErrorFilter::Validation");
    static_assert(static_cast<uint32_t>(ErrorFilter::OutOfMemory) == WNNErrorFilter_OutOfMemory, "value mismatch for ErrorFilter::OutOfMemory");

    // ErrorType

    static_assert(sizeof(ErrorType) == sizeof(WNNErrorType), "sizeof mismatch for ErrorType");
    static_assert(alignof(ErrorType) == alignof(WNNErrorType), "alignof mismatch for ErrorType");

    static_assert(static_cast<uint32_t>(ErrorType::NoError) == WNNErrorType_NoError, "value mismatch for ErrorType::NoError");
    static_assert(static_cast<uint32_t>(ErrorType::Validation) == WNNErrorType_Validation, "value mismatch for ErrorType::Validation");
    static_assert(static_cast<uint32_t>(ErrorType::OutOfMemory) == WNNErrorType_OutOfMemory, "value mismatch for ErrorType::OutOfMemory");
    static_assert(static_cast<uint32_t>(ErrorType::Unknown) == WNNErrorType_Unknown, "value mismatch for ErrorType::Unknown");
    static_assert(static_cast<uint32_t>(ErrorType::DeviceLost) == WNNErrorType_DeviceLost, "value mismatch for ErrorType::DeviceLost");

    // InputOperandLayout

    static_assert(sizeof(InputOperandLayout) == sizeof(WNNInputOperandLayout), "sizeof mismatch for InputOperandLayout");
    static_assert(alignof(InputOperandLayout) == alignof(WNNInputOperandLayout), "alignof mismatch for InputOperandLayout");

    static_assert(static_cast<uint32_t>(InputOperandLayout::Nchw) == WNNInputOperandLayout_Nchw, "value mismatch for InputOperandLayout::Nchw");
    static_assert(static_cast<uint32_t>(InputOperandLayout::Nhwc) == WNNInputOperandLayout_Nhwc, "value mismatch for InputOperandLayout::Nhwc");

    // InterpolationMode

    static_assert(sizeof(InterpolationMode) == sizeof(WNNInterpolationMode), "sizeof mismatch for InterpolationMode");
    static_assert(alignof(InterpolationMode) == alignof(WNNInterpolationMode), "alignof mismatch for InterpolationMode");

    static_assert(static_cast<uint32_t>(InterpolationMode::NearestNeighbor) == WNNInterpolationMode_NearestNeighbor, "value mismatch for InterpolationMode::NearestNeighbor");
    static_assert(static_cast<uint32_t>(InterpolationMode::Linear) == WNNInterpolationMode_Linear, "value mismatch for InterpolationMode::Linear");

    // OperandType

    static_assert(sizeof(OperandType) == sizeof(WNNOperandType), "sizeof mismatch for OperandType");
    static_assert(alignof(OperandType) == alignof(WNNOperandType), "alignof mismatch for OperandType");

    static_assert(static_cast<uint32_t>(OperandType::Float32) == WNNOperandType_Float32, "value mismatch for OperandType::Float32");
    static_assert(static_cast<uint32_t>(OperandType::Float16) == WNNOperandType_Float16, "value mismatch for OperandType::Float16");
    static_assert(static_cast<uint32_t>(OperandType::Int32) == WNNOperandType_Int32, "value mismatch for OperandType::Int32");
    static_assert(static_cast<uint32_t>(OperandType::Uint32) == WNNOperandType_Uint32, "value mismatch for OperandType::Uint32");
    static_assert(static_cast<uint32_t>(OperandType::Int8) == WNNOperandType_Int8, "value mismatch for OperandType::Int8");
    static_assert(static_cast<uint32_t>(OperandType::Uint8) == WNNOperandType_Uint8, "value mismatch for OperandType::Uint8");

    // PaddingMode

    static_assert(sizeof(PaddingMode) == sizeof(WNNPaddingMode), "sizeof mismatch for PaddingMode");
    static_assert(alignof(PaddingMode) == alignof(WNNPaddingMode), "alignof mismatch for PaddingMode");

    static_assert(static_cast<uint32_t>(PaddingMode::Constant) == WNNPaddingMode_Constant, "value mismatch for PaddingMode::Constant");
    static_assert(static_cast<uint32_t>(PaddingMode::Edge) == WNNPaddingMode_Edge, "value mismatch for PaddingMode::Edge");
    static_assert(static_cast<uint32_t>(PaddingMode::Reflection) == WNNPaddingMode_Reflection, "value mismatch for PaddingMode::Reflection");
    static_assert(static_cast<uint32_t>(PaddingMode::Symmetric) == WNNPaddingMode_Symmetric, "value mismatch for PaddingMode::Symmetric");

    // PowerPreference

    static_assert(sizeof(PowerPreference) == sizeof(WNNPowerPreference), "sizeof mismatch for PowerPreference");
    static_assert(alignof(PowerPreference) == alignof(WNNPowerPreference), "alignof mismatch for PowerPreference");

    static_assert(static_cast<uint32_t>(PowerPreference::Default) == WNNPowerPreference_Default, "value mismatch for PowerPreference::Default");
    static_assert(static_cast<uint32_t>(PowerPreference::High_performance) == WNNPowerPreference_High_performance, "value mismatch for PowerPreference::High_performance");
    static_assert(static_cast<uint32_t>(PowerPreference::Low_power) == WNNPowerPreference_Low_power, "value mismatch for PowerPreference::Low_power");

    // RecurrentNetworkDirection

    static_assert(sizeof(RecurrentNetworkDirection) == sizeof(WNNRecurrentNetworkDirection), "sizeof mismatch for RecurrentNetworkDirection");
    static_assert(alignof(RecurrentNetworkDirection) == alignof(WNNRecurrentNetworkDirection), "alignof mismatch for RecurrentNetworkDirection");

    static_assert(static_cast<uint32_t>(RecurrentNetworkDirection::Forward) == WNNRecurrentNetworkDirection_Forward, "value mismatch for RecurrentNetworkDirection::Forward");
    static_assert(static_cast<uint32_t>(RecurrentNetworkDirection::Backward) == WNNRecurrentNetworkDirection_Backward, "value mismatch for RecurrentNetworkDirection::Backward");
    static_assert(static_cast<uint32_t>(RecurrentNetworkDirection::Both) == WNNRecurrentNetworkDirection_Both, "value mismatch for RecurrentNetworkDirection::Both");

    // RecurrentNetworkWeightLayout

    static_assert(sizeof(RecurrentNetworkWeightLayout) == sizeof(WNNRecurrentNetworkWeightLayout), "sizeof mismatch for RecurrentNetworkWeightLayout");
    static_assert(alignof(RecurrentNetworkWeightLayout) == alignof(WNNRecurrentNetworkWeightLayout), "alignof mismatch for RecurrentNetworkWeightLayout");

    static_assert(static_cast<uint32_t>(RecurrentNetworkWeightLayout::Zrn) == WNNRecurrentNetworkWeightLayout_Zrn, "value mismatch for RecurrentNetworkWeightLayout::Zrn");
    static_assert(static_cast<uint32_t>(RecurrentNetworkWeightLayout::Rzn) == WNNRecurrentNetworkWeightLayout_Rzn, "value mismatch for RecurrentNetworkWeightLayout::Rzn");

    // RoundingType

    static_assert(sizeof(RoundingType) == sizeof(WNNRoundingType), "sizeof mismatch for RoundingType");
    static_assert(alignof(RoundingType) == alignof(WNNRoundingType), "alignof mismatch for RoundingType");

    static_assert(static_cast<uint32_t>(RoundingType::Floor) == WNNRoundingType_Floor, "value mismatch for RoundingType::Floor");
    static_assert(static_cast<uint32_t>(RoundingType::Ceil) == WNNRoundingType_Ceil, "value mismatch for RoundingType::Ceil");

    // ChainedStruct


    // ArrayBufferView

    static_assert(sizeof(ArrayBufferView) == sizeof(WNNArrayBufferView), "sizeof mismatch for ArrayBufferView");
    static_assert(alignof(ArrayBufferView) == alignof(WNNArrayBufferView), "alignof mismatch for ArrayBufferView");

    static_assert(offsetof(ArrayBufferView, buffer) == offsetof(WNNArrayBufferView, buffer),
            "offsetof mismatch for ArrayBufferView::buffer");
    static_assert(offsetof(ArrayBufferView, byteLength) == offsetof(WNNArrayBufferView, byteLength),
            "offsetof mismatch for ArrayBufferView::byteLength");
    static_assert(offsetof(ArrayBufferView, byteOffset) == offsetof(WNNArrayBufferView, byteOffset),
            "offsetof mismatch for ArrayBufferView::byteOffset");

    // BatchNormOptions

    static_assert(sizeof(BatchNormOptions) == sizeof(WNNBatchNormOptions), "sizeof mismatch for BatchNormOptions");
    static_assert(alignof(BatchNormOptions) == alignof(WNNBatchNormOptions), "alignof mismatch for BatchNormOptions");

    static_assert(offsetof(BatchNormOptions, scale) == offsetof(WNNBatchNormOptions, scale),
            "offsetof mismatch for BatchNormOptions::scale");
    static_assert(offsetof(BatchNormOptions, bias) == offsetof(WNNBatchNormOptions, bias),
            "offsetof mismatch for BatchNormOptions::bias");
    static_assert(offsetof(BatchNormOptions, axis) == offsetof(WNNBatchNormOptions, axis),
            "offsetof mismatch for BatchNormOptions::axis");
    static_assert(offsetof(BatchNormOptions, epsilon) == offsetof(WNNBatchNormOptions, epsilon),
            "offsetof mismatch for BatchNormOptions::epsilon");
    static_assert(offsetof(BatchNormOptions, activation) == offsetof(WNNBatchNormOptions, activation),
            "offsetof mismatch for BatchNormOptions::activation");

    // ClampOptions

    static_assert(sizeof(ClampOptions) == sizeof(WNNClampOptions), "sizeof mismatch for ClampOptions");
    static_assert(alignof(ClampOptions) == alignof(WNNClampOptions), "alignof mismatch for ClampOptions");

    static_assert(offsetof(ClampOptions, minValue) == offsetof(WNNClampOptions, minValue),
            "offsetof mismatch for ClampOptions::minValue");
    static_assert(offsetof(ClampOptions, maxValue) == offsetof(WNNClampOptions, maxValue),
            "offsetof mismatch for ClampOptions::maxValue");

    // ContextOptions

    static_assert(sizeof(ContextOptions) == sizeof(WNNContextOptions), "sizeof mismatch for ContextOptions");
    static_assert(alignof(ContextOptions) == alignof(WNNContextOptions), "alignof mismatch for ContextOptions");

    static_assert(offsetof(ContextOptions, devicePreference) == offsetof(WNNContextOptions, devicePreference),
            "offsetof mismatch for ContextOptions::devicePreference");
    static_assert(offsetof(ContextOptions, powerPreference) == offsetof(WNNContextOptions, powerPreference),
            "offsetof mismatch for ContextOptions::powerPreference");

    // ConvTranspose2dOptions

    static_assert(sizeof(ConvTranspose2dOptions) == sizeof(WNNConvTranspose2dOptions), "sizeof mismatch for ConvTranspose2dOptions");
    static_assert(alignof(ConvTranspose2dOptions) == alignof(WNNConvTranspose2dOptions), "alignof mismatch for ConvTranspose2dOptions");

    static_assert(offsetof(ConvTranspose2dOptions, paddingCount) == offsetof(WNNConvTranspose2dOptions, paddingCount),
            "offsetof mismatch for ConvTranspose2dOptions::paddingCount");
    static_assert(offsetof(ConvTranspose2dOptions, padding) == offsetof(WNNConvTranspose2dOptions, padding),
            "offsetof mismatch for ConvTranspose2dOptions::padding");
    static_assert(offsetof(ConvTranspose2dOptions, stridesCount) == offsetof(WNNConvTranspose2dOptions, stridesCount),
            "offsetof mismatch for ConvTranspose2dOptions::stridesCount");
    static_assert(offsetof(ConvTranspose2dOptions, strides) == offsetof(WNNConvTranspose2dOptions, strides),
            "offsetof mismatch for ConvTranspose2dOptions::strides");
    static_assert(offsetof(ConvTranspose2dOptions, dilationsCount) == offsetof(WNNConvTranspose2dOptions, dilationsCount),
            "offsetof mismatch for ConvTranspose2dOptions::dilationsCount");
    static_assert(offsetof(ConvTranspose2dOptions, dilations) == offsetof(WNNConvTranspose2dOptions, dilations),
            "offsetof mismatch for ConvTranspose2dOptions::dilations");
    static_assert(offsetof(ConvTranspose2dOptions, outputPaddingCount) == offsetof(WNNConvTranspose2dOptions, outputPaddingCount),
            "offsetof mismatch for ConvTranspose2dOptions::outputPaddingCount");
    static_assert(offsetof(ConvTranspose2dOptions, outputPadding) == offsetof(WNNConvTranspose2dOptions, outputPadding),
            "offsetof mismatch for ConvTranspose2dOptions::outputPadding");
    static_assert(offsetof(ConvTranspose2dOptions, outputSizesCount) == offsetof(WNNConvTranspose2dOptions, outputSizesCount),
            "offsetof mismatch for ConvTranspose2dOptions::outputSizesCount");
    static_assert(offsetof(ConvTranspose2dOptions, outputSizes) == offsetof(WNNConvTranspose2dOptions, outputSizes),
            "offsetof mismatch for ConvTranspose2dOptions::outputSizes");
    static_assert(offsetof(ConvTranspose2dOptions, autoPad) == offsetof(WNNConvTranspose2dOptions, autoPad),
            "offsetof mismatch for ConvTranspose2dOptions::autoPad");
    static_assert(offsetof(ConvTranspose2dOptions, groups) == offsetof(WNNConvTranspose2dOptions, groups),
            "offsetof mismatch for ConvTranspose2dOptions::groups");
    static_assert(offsetof(ConvTranspose2dOptions, inputLayout) == offsetof(WNNConvTranspose2dOptions, inputLayout),
            "offsetof mismatch for ConvTranspose2dOptions::inputLayout");
    static_assert(offsetof(ConvTranspose2dOptions, filterLayout) == offsetof(WNNConvTranspose2dOptions, filterLayout),
            "offsetof mismatch for ConvTranspose2dOptions::filterLayout");
    static_assert(offsetof(ConvTranspose2dOptions, bias) == offsetof(WNNConvTranspose2dOptions, bias),
            "offsetof mismatch for ConvTranspose2dOptions::bias");
    static_assert(offsetof(ConvTranspose2dOptions, activation) == offsetof(WNNConvTranspose2dOptions, activation),
            "offsetof mismatch for ConvTranspose2dOptions::activation");

    // Conv2dOptions

    static_assert(sizeof(Conv2dOptions) == sizeof(WNNConv2dOptions), "sizeof mismatch for Conv2dOptions");
    static_assert(alignof(Conv2dOptions) == alignof(WNNConv2dOptions), "alignof mismatch for Conv2dOptions");

    static_assert(offsetof(Conv2dOptions, paddingCount) == offsetof(WNNConv2dOptions, paddingCount),
            "offsetof mismatch for Conv2dOptions::paddingCount");
    static_assert(offsetof(Conv2dOptions, padding) == offsetof(WNNConv2dOptions, padding),
            "offsetof mismatch for Conv2dOptions::padding");
    static_assert(offsetof(Conv2dOptions, stridesCount) == offsetof(WNNConv2dOptions, stridesCount),
            "offsetof mismatch for Conv2dOptions::stridesCount");
    static_assert(offsetof(Conv2dOptions, strides) == offsetof(WNNConv2dOptions, strides),
            "offsetof mismatch for Conv2dOptions::strides");
    static_assert(offsetof(Conv2dOptions, dilationsCount) == offsetof(WNNConv2dOptions, dilationsCount),
            "offsetof mismatch for Conv2dOptions::dilationsCount");
    static_assert(offsetof(Conv2dOptions, dilations) == offsetof(WNNConv2dOptions, dilations),
            "offsetof mismatch for Conv2dOptions::dilations");
    static_assert(offsetof(Conv2dOptions, autoPad) == offsetof(WNNConv2dOptions, autoPad),
            "offsetof mismatch for Conv2dOptions::autoPad");
    static_assert(offsetof(Conv2dOptions, groups) == offsetof(WNNConv2dOptions, groups),
            "offsetof mismatch for Conv2dOptions::groups");
    static_assert(offsetof(Conv2dOptions, inputLayout) == offsetof(WNNConv2dOptions, inputLayout),
            "offsetof mismatch for Conv2dOptions::inputLayout");
    static_assert(offsetof(Conv2dOptions, filterLayout) == offsetof(WNNConv2dOptions, filterLayout),
            "offsetof mismatch for Conv2dOptions::filterLayout");
    static_assert(offsetof(Conv2dOptions, bias) == offsetof(WNNConv2dOptions, bias),
            "offsetof mismatch for Conv2dOptions::bias");
    static_assert(offsetof(Conv2dOptions, activation) == offsetof(WNNConv2dOptions, activation),
            "offsetof mismatch for Conv2dOptions::activation");

    // GemmOptions

    static_assert(sizeof(GemmOptions) == sizeof(WNNGemmOptions), "sizeof mismatch for GemmOptions");
    static_assert(alignof(GemmOptions) == alignof(WNNGemmOptions), "alignof mismatch for GemmOptions");

    static_assert(offsetof(GemmOptions, c) == offsetof(WNNGemmOptions, c),
            "offsetof mismatch for GemmOptions::c");
    static_assert(offsetof(GemmOptions, alpha) == offsetof(WNNGemmOptions, alpha),
            "offsetof mismatch for GemmOptions::alpha");
    static_assert(offsetof(GemmOptions, beta) == offsetof(WNNGemmOptions, beta),
            "offsetof mismatch for GemmOptions::beta");
    static_assert(offsetof(GemmOptions, aTranspose) == offsetof(WNNGemmOptions, aTranspose),
            "offsetof mismatch for GemmOptions::aTranspose");
    static_assert(offsetof(GemmOptions, bTranspose) == offsetof(WNNGemmOptions, bTranspose),
            "offsetof mismatch for GemmOptions::bTranspose");

    // GpuBufferView

    static_assert(sizeof(GpuBufferView) == sizeof(WNNGpuBufferView), "sizeof mismatch for GpuBufferView");
    static_assert(alignof(GpuBufferView) == alignof(WNNGpuBufferView), "alignof mismatch for GpuBufferView");

    static_assert(offsetof(GpuBufferView, buffer) == offsetof(WNNGpuBufferView, buffer),
            "offsetof mismatch for GpuBufferView::buffer");
    static_assert(offsetof(GpuBufferView, id) == offsetof(WNNGpuBufferView, id),
            "offsetof mismatch for GpuBufferView::id");
    static_assert(offsetof(GpuBufferView, generation) == offsetof(WNNGpuBufferView, generation),
            "offsetof mismatch for GpuBufferView::generation");
    static_assert(offsetof(GpuBufferView, size) == offsetof(WNNGpuBufferView, size),
            "offsetof mismatch for GpuBufferView::size");
    static_assert(offsetof(GpuBufferView, offset) == offsetof(WNNGpuBufferView, offset),
            "offsetof mismatch for GpuBufferView::offset");

    // GpuDevice

    static_assert(sizeof(GpuDevice) == sizeof(WNNGpuDevice), "sizeof mismatch for GpuDevice");
    static_assert(alignof(GpuDevice) == alignof(WNNGpuDevice), "alignof mismatch for GpuDevice");

    static_assert(offsetof(GpuDevice, device) == offsetof(WNNGpuDevice, device),
            "offsetof mismatch for GpuDevice::device");
    static_assert(offsetof(GpuDevice, id) == offsetof(WNNGpuDevice, id),
            "offsetof mismatch for GpuDevice::id");
    static_assert(offsetof(GpuDevice, generation) == offsetof(WNNGpuDevice, generation),
            "offsetof mismatch for GpuDevice::generation");

    // GruOptions

    static_assert(sizeof(GruOptions) == sizeof(WNNGruOptions), "sizeof mismatch for GruOptions");
    static_assert(alignof(GruOptions) == alignof(WNNGruOptions), "alignof mismatch for GruOptions");

    static_assert(offsetof(GruOptions, bias) == offsetof(WNNGruOptions, bias),
            "offsetof mismatch for GruOptions::bias");
    static_assert(offsetof(GruOptions, recurrentBias) == offsetof(WNNGruOptions, recurrentBias),
            "offsetof mismatch for GruOptions::recurrentBias");
    static_assert(offsetof(GruOptions, initialHiddenState) == offsetof(WNNGruOptions, initialHiddenState),
            "offsetof mismatch for GruOptions::initialHiddenState");
    static_assert(offsetof(GruOptions, resetAfter) == offsetof(WNNGruOptions, resetAfter),
            "offsetof mismatch for GruOptions::resetAfter");
    static_assert(offsetof(GruOptions, returnSequence) == offsetof(WNNGruOptions, returnSequence),
            "offsetof mismatch for GruOptions::returnSequence");
    static_assert(offsetof(GruOptions, direction) == offsetof(WNNGruOptions, direction),
            "offsetof mismatch for GruOptions::direction");
    static_assert(offsetof(GruOptions, layout) == offsetof(WNNGruOptions, layout),
            "offsetof mismatch for GruOptions::layout");
    static_assert(offsetof(GruOptions, activations) == offsetof(WNNGruOptions, activations),
            "offsetof mismatch for GruOptions::activations");

    // InstanceDescriptor

    static_assert(sizeof(InstanceDescriptor) == sizeof(WNNInstanceDescriptor), "sizeof mismatch for InstanceDescriptor");
    static_assert(alignof(InstanceDescriptor) == alignof(WNNInstanceDescriptor), "alignof mismatch for InstanceDescriptor");


    // InstanceNormOptions

    static_assert(sizeof(InstanceNormOptions) == sizeof(WNNInstanceNormOptions), "sizeof mismatch for InstanceNormOptions");
    static_assert(alignof(InstanceNormOptions) == alignof(WNNInstanceNormOptions), "alignof mismatch for InstanceNormOptions");

    static_assert(offsetof(InstanceNormOptions, scale) == offsetof(WNNInstanceNormOptions, scale),
            "offsetof mismatch for InstanceNormOptions::scale");
    static_assert(offsetof(InstanceNormOptions, bias) == offsetof(WNNInstanceNormOptions, bias),
            "offsetof mismatch for InstanceNormOptions::bias");
    static_assert(offsetof(InstanceNormOptions, epsilon) == offsetof(WNNInstanceNormOptions, epsilon),
            "offsetof mismatch for InstanceNormOptions::epsilon");
    static_assert(offsetof(InstanceNormOptions, layout) == offsetof(WNNInstanceNormOptions, layout),
            "offsetof mismatch for InstanceNormOptions::layout");

    // LeakyReluOptions

    static_assert(sizeof(LeakyReluOptions) == sizeof(WNNLeakyReluOptions), "sizeof mismatch for LeakyReluOptions");
    static_assert(alignof(LeakyReluOptions) == alignof(WNNLeakyReluOptions), "alignof mismatch for LeakyReluOptions");

    static_assert(offsetof(LeakyReluOptions, alpha) == offsetof(WNNLeakyReluOptions, alpha),
            "offsetof mismatch for LeakyReluOptions::alpha");

    // OperandDescriptor

    static_assert(sizeof(OperandDescriptor) == sizeof(WNNOperandDescriptor), "sizeof mismatch for OperandDescriptor");
    static_assert(alignof(OperandDescriptor) == alignof(WNNOperandDescriptor), "alignof mismatch for OperandDescriptor");

    static_assert(offsetof(OperandDescriptor, type) == offsetof(WNNOperandDescriptor, type),
            "offsetof mismatch for OperandDescriptor::type");
    static_assert(offsetof(OperandDescriptor, dimensions) == offsetof(WNNOperandDescriptor, dimensions),
            "offsetof mismatch for OperandDescriptor::dimensions");
    static_assert(offsetof(OperandDescriptor, dimensionsCount) == offsetof(WNNOperandDescriptor, dimensionsCount),
            "offsetof mismatch for OperandDescriptor::dimensionsCount");

    // PadOptions

    static_assert(sizeof(PadOptions) == sizeof(WNNPadOptions), "sizeof mismatch for PadOptions");
    static_assert(alignof(PadOptions) == alignof(WNNPadOptions), "alignof mismatch for PadOptions");

    static_assert(offsetof(PadOptions, mode) == offsetof(WNNPadOptions, mode),
            "offsetof mismatch for PadOptions::mode");
    static_assert(offsetof(PadOptions, value) == offsetof(WNNPadOptions, value),
            "offsetof mismatch for PadOptions::value");

    // Pool2dOptions

    static_assert(sizeof(Pool2dOptions) == sizeof(WNNPool2dOptions), "sizeof mismatch for Pool2dOptions");
    static_assert(alignof(Pool2dOptions) == alignof(WNNPool2dOptions), "alignof mismatch for Pool2dOptions");

    static_assert(offsetof(Pool2dOptions, windowDimensionsCount) == offsetof(WNNPool2dOptions, windowDimensionsCount),
            "offsetof mismatch for Pool2dOptions::windowDimensionsCount");
    static_assert(offsetof(Pool2dOptions, windowDimensions) == offsetof(WNNPool2dOptions, windowDimensions),
            "offsetof mismatch for Pool2dOptions::windowDimensions");
    static_assert(offsetof(Pool2dOptions, paddingCount) == offsetof(WNNPool2dOptions, paddingCount),
            "offsetof mismatch for Pool2dOptions::paddingCount");
    static_assert(offsetof(Pool2dOptions, padding) == offsetof(WNNPool2dOptions, padding),
            "offsetof mismatch for Pool2dOptions::padding");
    static_assert(offsetof(Pool2dOptions, stridesCount) == offsetof(WNNPool2dOptions, stridesCount),
            "offsetof mismatch for Pool2dOptions::stridesCount");
    static_assert(offsetof(Pool2dOptions, strides) == offsetof(WNNPool2dOptions, strides),
            "offsetof mismatch for Pool2dOptions::strides");
    static_assert(offsetof(Pool2dOptions, dilationsCount) == offsetof(WNNPool2dOptions, dilationsCount),
            "offsetof mismatch for Pool2dOptions::dilationsCount");
    static_assert(offsetof(Pool2dOptions, dilations) == offsetof(WNNPool2dOptions, dilations),
            "offsetof mismatch for Pool2dOptions::dilations");
    static_assert(offsetof(Pool2dOptions, autoPad) == offsetof(WNNPool2dOptions, autoPad),
            "offsetof mismatch for Pool2dOptions::autoPad");
    static_assert(offsetof(Pool2dOptions, layout) == offsetof(WNNPool2dOptions, layout),
            "offsetof mismatch for Pool2dOptions::layout");
    static_assert(offsetof(Pool2dOptions, roundingType) == offsetof(WNNPool2dOptions, roundingType),
            "offsetof mismatch for Pool2dOptions::roundingType");
    static_assert(offsetof(Pool2dOptions, outputSizesCount) == offsetof(WNNPool2dOptions, outputSizesCount),
            "offsetof mismatch for Pool2dOptions::outputSizesCount");
    static_assert(offsetof(Pool2dOptions, outputSizes) == offsetof(WNNPool2dOptions, outputSizes),
            "offsetof mismatch for Pool2dOptions::outputSizes");

    // ReduceOptions

    static_assert(sizeof(ReduceOptions) == sizeof(WNNReduceOptions), "sizeof mismatch for ReduceOptions");
    static_assert(alignof(ReduceOptions) == alignof(WNNReduceOptions), "alignof mismatch for ReduceOptions");

    static_assert(offsetof(ReduceOptions, axesCount) == offsetof(WNNReduceOptions, axesCount),
            "offsetof mismatch for ReduceOptions::axesCount");
    static_assert(offsetof(ReduceOptions, axes) == offsetof(WNNReduceOptions, axes),
            "offsetof mismatch for ReduceOptions::axes");
    static_assert(offsetof(ReduceOptions, keepDimensions) == offsetof(WNNReduceOptions, keepDimensions),
            "offsetof mismatch for ReduceOptions::keepDimensions");

    // Resample2dOptions

    static_assert(sizeof(Resample2dOptions) == sizeof(WNNResample2dOptions), "sizeof mismatch for Resample2dOptions");
    static_assert(alignof(Resample2dOptions) == alignof(WNNResample2dOptions), "alignof mismatch for Resample2dOptions");

    static_assert(offsetof(Resample2dOptions, mode) == offsetof(WNNResample2dOptions, mode),
            "offsetof mismatch for Resample2dOptions::mode");
    static_assert(offsetof(Resample2dOptions, scalesCount) == offsetof(WNNResample2dOptions, scalesCount),
            "offsetof mismatch for Resample2dOptions::scalesCount");
    static_assert(offsetof(Resample2dOptions, scales) == offsetof(WNNResample2dOptions, scales),
            "offsetof mismatch for Resample2dOptions::scales");
    static_assert(offsetof(Resample2dOptions, sizesCount) == offsetof(WNNResample2dOptions, sizesCount),
            "offsetof mismatch for Resample2dOptions::sizesCount");
    static_assert(offsetof(Resample2dOptions, sizes) == offsetof(WNNResample2dOptions, sizes),
            "offsetof mismatch for Resample2dOptions::sizes");
    static_assert(offsetof(Resample2dOptions, axesCount) == offsetof(WNNResample2dOptions, axesCount),
            "offsetof mismatch for Resample2dOptions::axesCount");
    static_assert(offsetof(Resample2dOptions, axes) == offsetof(WNNResample2dOptions, axes),
            "offsetof mismatch for Resample2dOptions::axes");

    // SliceOptions

    static_assert(sizeof(SliceOptions) == sizeof(WNNSliceOptions), "sizeof mismatch for SliceOptions");
    static_assert(alignof(SliceOptions) == alignof(WNNSliceOptions), "alignof mismatch for SliceOptions");

    static_assert(offsetof(SliceOptions, axesCount) == offsetof(WNNSliceOptions, axesCount),
            "offsetof mismatch for SliceOptions::axesCount");
    static_assert(offsetof(SliceOptions, axes) == offsetof(WNNSliceOptions, axes),
            "offsetof mismatch for SliceOptions::axes");

    // SplitOptions

    static_assert(sizeof(SplitOptions) == sizeof(WNNSplitOptions), "sizeof mismatch for SplitOptions");
    static_assert(alignof(SplitOptions) == alignof(WNNSplitOptions), "alignof mismatch for SplitOptions");

    static_assert(offsetof(SplitOptions, axis) == offsetof(WNNSplitOptions, axis),
            "offsetof mismatch for SplitOptions::axis");

    // SqueezeOptions

    static_assert(sizeof(SqueezeOptions) == sizeof(WNNSqueezeOptions), "sizeof mismatch for SqueezeOptions");
    static_assert(alignof(SqueezeOptions) == alignof(WNNSqueezeOptions), "alignof mismatch for SqueezeOptions");

    static_assert(offsetof(SqueezeOptions, axesCount) == offsetof(WNNSqueezeOptions, axesCount),
            "offsetof mismatch for SqueezeOptions::axesCount");
    static_assert(offsetof(SqueezeOptions, axes) == offsetof(WNNSqueezeOptions, axes),
            "offsetof mismatch for SqueezeOptions::axes");

    // TransposeOptions

    static_assert(sizeof(TransposeOptions) == sizeof(WNNTransposeOptions), "sizeof mismatch for TransposeOptions");
    static_assert(alignof(TransposeOptions) == alignof(WNNTransposeOptions), "alignof mismatch for TransposeOptions");

    static_assert(offsetof(TransposeOptions, permutationCount) == offsetof(WNNTransposeOptions, permutationCount),
            "offsetof mismatch for TransposeOptions::permutationCount");
    static_assert(offsetof(TransposeOptions, permutation) == offsetof(WNNTransposeOptions, permutation),
            "offsetof mismatch for TransposeOptions::permutation");

    // Resource

    static_assert(sizeof(Resource) == sizeof(WNNResource), "sizeof mismatch for Resource");
    static_assert(alignof(Resource) == alignof(WNNResource), "alignof mismatch for Resource");

    static_assert(offsetof(Resource, arrayBufferView) == offsetof(WNNResource, arrayBufferView),
            "offsetof mismatch for Resource::arrayBufferView");
    static_assert(offsetof(Resource, gpuBufferView) == offsetof(WNNResource, gpuBufferView),
            "offsetof mismatch for Resource::gpuBufferView");

    // Input

    static_assert(sizeof(Input) == sizeof(WNNInput), "sizeof mismatch for Input");
    static_assert(alignof(Input) == alignof(WNNInput), "alignof mismatch for Input");

    static_assert(offsetof(Input, resource) == offsetof(WNNInput, resource),
            "offsetof mismatch for Input::resource");
    static_assert(offsetof(Input, dimensions) == offsetof(WNNInput, dimensions),
            "offsetof mismatch for Input::dimensions");
    static_assert(offsetof(Input, dimensionsCount) == offsetof(WNNInput, dimensionsCount),
            "offsetof mismatch for Input::dimensionsCount");

    // Context

    static_assert(sizeof(Context) == sizeof(WNNContext), "sizeof mismatch for Context");
    static_assert(alignof(Context) == alignof(WNNContext), "alignof mismatch for Context");

    void Context::InjectError(ErrorType type, char const * message) const {
        wnnContextInjectError(GetHandle(), static_cast<WNNErrorType>(type), reinterpret_cast<char const * >(message));
    }
    bool Context::PopErrorScope(ErrorCallback callback, void * userdata) const {
        auto result = wnnContextPopErrorScope(GetHandle(), callback, reinterpret_cast<void * >(userdata));
        return result;
    }
    void Context::PushErrorScope(ErrorFilter filter) const {
        wnnContextPushErrorScope(GetHandle(), static_cast<WNNErrorFilter>(filter));
    }
    void Context::SetUncapturedErrorCallback(ErrorCallback callback, void * userdata) const {
        wnnContextSetUncapturedErrorCallback(GetHandle(), callback, reinterpret_cast<void * >(userdata));
    }
    void Context::WebnnReference(WNNContext handle) {
        if (handle != nullptr) {
            wnnContextReference(handle);
        }
    }
    void Context::WebnnRelease(WNNContext handle) {
        if (handle != nullptr) {
            wnnContextRelease(handle);
        }
    }

    // FusionOperator

    static_assert(sizeof(FusionOperator) == sizeof(WNNFusionOperator), "sizeof mismatch for FusionOperator");
    static_assert(alignof(FusionOperator) == alignof(WNNFusionOperator), "alignof mismatch for FusionOperator");

    void FusionOperator::WebnnReference(WNNFusionOperator handle) {
        if (handle != nullptr) {
            wnnFusionOperatorReference(handle);
        }
    }
    void FusionOperator::WebnnRelease(WNNFusionOperator handle) {
        if (handle != nullptr) {
            wnnFusionOperatorRelease(handle);
        }
    }

    // Graph

    static_assert(sizeof(Graph) == sizeof(WNNGraph), "sizeof mismatch for Graph");
    static_assert(alignof(Graph) == alignof(WNNGraph), "alignof mismatch for Graph");

    void Graph::Compute(NamedInputs const& inputs, NamedOutputs const& outputs) const {
        wnnGraphCompute(GetHandle(), inputs.GetHandle(), outputs.GetHandle());
    }
    void Graph::ComputeAsync(NamedInputs const& inputs, NamedOutputs const& outputs, ComputeAsyncCallback callback, void * userdata) const {
        wnnGraphComputeAsync(GetHandle(), inputs.GetHandle(), outputs.GetHandle(), callback, reinterpret_cast<void * >(userdata));
    }
    void Graph::WebnnReference(WNNGraph handle) {
        if (handle != nullptr) {
            wnnGraphReference(handle);
        }
    }
    void Graph::WebnnRelease(WNNGraph handle) {
        if (handle != nullptr) {
            wnnGraphRelease(handle);
        }
    }

    // GraphBuilder

    static_assert(sizeof(GraphBuilder) == sizeof(WNNGraphBuilder), "sizeof mismatch for GraphBuilder");
    static_assert(alignof(GraphBuilder) == alignof(WNNGraphBuilder), "alignof mismatch for GraphBuilder");

    Operand GraphBuilder::Abs(Operand const& input) const {
        auto result = wnnGraphBuilderAbs(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Add(Operand const& a, Operand const& b) const {
        auto result = wnnGraphBuilderAdd(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::AveragePool2d(Operand const& input, Pool2dOptions const * options) const {
        auto result = wnnGraphBuilderAveragePool2d(GetHandle(), input.GetHandle(), reinterpret_cast<WNNPool2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::BatchNorm(Operand const& input, Operand const& mean, Operand const& variance, BatchNormOptions const * options) const {
        auto result = wnnGraphBuilderBatchNorm(GetHandle(), input.GetHandle(), mean.GetHandle(), variance.GetHandle(), reinterpret_cast<WNNBatchNormOptions const * >(options));
        return Operand::Acquire(result);
    }
    Graph GraphBuilder::Build(NamedOperands const& namedOperands) const {
        auto result = wnnGraphBuilderBuild(GetHandle(), namedOperands.GetHandle());
        return Graph::Acquire(result);
    }
    Operand GraphBuilder::Ceil(Operand const& input) const {
        auto result = wnnGraphBuilderCeil(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Clamp(Operand const& input, ClampOptions const * options) const {
        auto result = wnnGraphBuilderClamp(GetHandle(), input.GetHandle(), reinterpret_cast<WNNClampOptions const * >(options));
        return Operand::Acquire(result);
    }
    FusionOperator GraphBuilder::ClampOperator(ClampOptions const * options) const {
        auto result = wnnGraphBuilderClampOperator(GetHandle(), reinterpret_cast<WNNClampOptions const * >(options));
        return FusionOperator::Acquire(result);
    }
    Operand GraphBuilder::Concat(uint32_t inputsCount, Operand const * inputs, uint32_t axis) const {
        auto result = wnnGraphBuilderConcat(GetHandle(), inputsCount, reinterpret_cast<WNNOperand const * >(inputs), axis);
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Constant(OperandDescriptor const * desc, ArrayBufferView const * value) const {
        auto result = wnnGraphBuilderConstant(GetHandle(), reinterpret_cast<WNNOperandDescriptor const * >(desc), reinterpret_cast<WNNArrayBufferView const * >(value));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ConstantWithGpuBuffer(OperandDescriptor const * desc, GpuBufferView const * value) const {
        auto result = wnnGraphBuilderConstantWithGpuBuffer(GetHandle(), reinterpret_cast<WNNOperandDescriptor const * >(desc), reinterpret_cast<WNNGpuBufferView const * >(value));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ConvTranspose2d(Operand const& input, Operand const& filter, ConvTranspose2dOptions const * options) const {
        auto result = wnnGraphBuilderConvTranspose2d(GetHandle(), input.GetHandle(), filter.GetHandle(), reinterpret_cast<WNNConvTranspose2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Conv2d(Operand const& input, Operand const& filter, Conv2dOptions const * options) const {
        auto result = wnnGraphBuilderConv2d(GetHandle(), input.GetHandle(), filter.GetHandle(), reinterpret_cast<WNNConv2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Cos(Operand const& input) const {
        auto result = wnnGraphBuilderCos(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Div(Operand const& a, Operand const& b) const {
        auto result = wnnGraphBuilderDiv(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Exp(Operand const& input) const {
        auto result = wnnGraphBuilderExp(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Floor(Operand const& input) const {
        auto result = wnnGraphBuilderFloor(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Gemm(Operand const& a, Operand const& b, GemmOptions const * options) const {
        auto result = wnnGraphBuilderGemm(GetHandle(), a.GetHandle(), b.GetHandle(), reinterpret_cast<WNNGemmOptions const * >(options));
        return Operand::Acquire(result);
    }
    OperandArray GraphBuilder::Gru(Operand const& input, Operand const& weight, Operand const& recurrentWeight, int32_t steps, int32_t hiddenSize, GruOptions const * options) const {
        auto result = wnnGraphBuilderGru(GetHandle(), input.GetHandle(), weight.GetHandle(), recurrentWeight.GetHandle(), steps, hiddenSize, reinterpret_cast<WNNGruOptions const * >(options));
        return OperandArray::Acquire(result);
    }
    Operand GraphBuilder::HardSwish(Operand const& input) const {
        auto result = wnnGraphBuilderHardSwish(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    FusionOperator GraphBuilder::HardSwishOperator() const {
        auto result = wnnGraphBuilderHardSwishOperator(GetHandle());
        return FusionOperator::Acquire(result);
    }
    Operand GraphBuilder::Input(char const * name, OperandDescriptor const * desc) const {
        auto result = wnnGraphBuilderInput(GetHandle(), reinterpret_cast<char const * >(name), reinterpret_cast<WNNOperandDescriptor const * >(desc));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::InstanceNorm(Operand const& input, InstanceNormOptions const * options) const {
        auto result = wnnGraphBuilderInstanceNorm(GetHandle(), input.GetHandle(), reinterpret_cast<WNNInstanceNormOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::L2Pool2d(Operand const& input, Pool2dOptions const * options) const {
        auto result = wnnGraphBuilderL2Pool2d(GetHandle(), input.GetHandle(), reinterpret_cast<WNNPool2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::LeakyRelu(Operand const& input, LeakyReluOptions const * options) const {
        auto result = wnnGraphBuilderLeakyRelu(GetHandle(), input.GetHandle(), reinterpret_cast<WNNLeakyReluOptions const * >(options));
        return Operand::Acquire(result);
    }
    FusionOperator GraphBuilder::LeakyReluOperator(LeakyReluOptions const * options) const {
        auto result = wnnGraphBuilderLeakyReluOperator(GetHandle(), reinterpret_cast<WNNLeakyReluOptions const * >(options));
        return FusionOperator::Acquire(result);
    }
    Operand GraphBuilder::Log(Operand const& input) const {
        auto result = wnnGraphBuilderLog(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Matmul(Operand const& a, Operand const& b) const {
        auto result = wnnGraphBuilderMatmul(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Max(Operand const& a, Operand const& b) const {
        auto result = wnnGraphBuilderMax(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::MaxPool2d(Operand const& input, Pool2dOptions const * options) const {
        auto result = wnnGraphBuilderMaxPool2d(GetHandle(), input.GetHandle(), reinterpret_cast<WNNPool2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Min(Operand const& a, Operand const& b) const {
        auto result = wnnGraphBuilderMin(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Mul(Operand const& a, Operand const& b) const {
        auto result = wnnGraphBuilderMul(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Neg(Operand const& input) const {
        auto result = wnnGraphBuilderNeg(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Pad(Operand const& input, Operand const& padding, PadOptions const * options) const {
        auto result = wnnGraphBuilderPad(GetHandle(), input.GetHandle(), padding.GetHandle(), reinterpret_cast<WNNPadOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Pow(Operand const& a, Operand const& b) const {
        auto result = wnnGraphBuilderPow(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceArgMax(Operand const& input, ReduceOptions const * options) const {
        auto result = wnnGraphBuilderReduceArgMax(GetHandle(), input.GetHandle(), reinterpret_cast<WNNReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceArgMin(Operand const& input, ReduceOptions const * options) const {
        auto result = wnnGraphBuilderReduceArgMin(GetHandle(), input.GetHandle(), reinterpret_cast<WNNReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceL1(Operand const& input, ReduceOptions const * options) const {
        auto result = wnnGraphBuilderReduceL1(GetHandle(), input.GetHandle(), reinterpret_cast<WNNReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceL2(Operand const& input, ReduceOptions const * options) const {
        auto result = wnnGraphBuilderReduceL2(GetHandle(), input.GetHandle(), reinterpret_cast<WNNReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceMax(Operand const& input, ReduceOptions const * options) const {
        auto result = wnnGraphBuilderReduceMax(GetHandle(), input.GetHandle(), reinterpret_cast<WNNReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceMean(Operand const& input, ReduceOptions const * options) const {
        auto result = wnnGraphBuilderReduceMean(GetHandle(), input.GetHandle(), reinterpret_cast<WNNReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceMin(Operand const& input, ReduceOptions const * options) const {
        auto result = wnnGraphBuilderReduceMin(GetHandle(), input.GetHandle(), reinterpret_cast<WNNReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceProduct(Operand const& input, ReduceOptions const * options) const {
        auto result = wnnGraphBuilderReduceProduct(GetHandle(), input.GetHandle(), reinterpret_cast<WNNReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::ReduceSum(Operand const& input, ReduceOptions const * options) const {
        auto result = wnnGraphBuilderReduceSum(GetHandle(), input.GetHandle(), reinterpret_cast<WNNReduceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Relu(Operand const& input) const {
        auto result = wnnGraphBuilderRelu(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    FusionOperator GraphBuilder::ReluOperator() const {
        auto result = wnnGraphBuilderReluOperator(GetHandle());
        return FusionOperator::Acquire(result);
    }
    Operand GraphBuilder::Resample2d(Operand const& input, Resample2dOptions const * options) const {
        auto result = wnnGraphBuilderResample2d(GetHandle(), input.GetHandle(), reinterpret_cast<WNNResample2dOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Reshape(Operand const& input, int32_t const * newShape, uint32_t newShapeCount) const {
        auto result = wnnGraphBuilderReshape(GetHandle(), input.GetHandle(), reinterpret_cast<int32_t const * >(newShape), newShapeCount);
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Sigmoid(Operand const& input) const {
        auto result = wnnGraphBuilderSigmoid(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    FusionOperator GraphBuilder::SigmoidOperator() const {
        auto result = wnnGraphBuilderSigmoidOperator(GetHandle());
        return FusionOperator::Acquire(result);
    }
    Operand GraphBuilder::Sin(Operand const& input) const {
        auto result = wnnGraphBuilderSin(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Slice(Operand const& input, int32_t const * starts, uint32_t startsCount, int32_t const * sizes, uint32_t sizesCount, SliceOptions const * options) const {
        auto result = wnnGraphBuilderSlice(GetHandle(), input.GetHandle(), reinterpret_cast<int32_t const * >(starts), startsCount, reinterpret_cast<int32_t const * >(sizes), sizesCount, reinterpret_cast<WNNSliceOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Softmax(Operand const& input) const {
        auto result = wnnGraphBuilderSoftmax(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    OperandArray GraphBuilder::Split(Operand const& input, uint32_t const * splits, uint32_t splitsCount, SplitOptions const * options) const {
        auto result = wnnGraphBuilderSplit(GetHandle(), input.GetHandle(), reinterpret_cast<uint32_t const * >(splits), splitsCount, reinterpret_cast<WNNSplitOptions const * >(options));
        return OperandArray::Acquire(result);
    }
    Operand GraphBuilder::Squeeze(Operand const& input, SqueezeOptions const * options) const {
        auto result = wnnGraphBuilderSqueeze(GetHandle(), input.GetHandle(), reinterpret_cast<WNNSqueezeOptions const * >(options));
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Sub(Operand const& a, Operand const& b) const {
        auto result = wnnGraphBuilderSub(GetHandle(), a.GetHandle(), b.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Tan(Operand const& input) const {
        auto result = wnnGraphBuilderTan(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    Operand GraphBuilder::Tanh(Operand const& input) const {
        auto result = wnnGraphBuilderTanh(GetHandle(), input.GetHandle());
        return Operand::Acquire(result);
    }
    FusionOperator GraphBuilder::TanhOperator() const {
        auto result = wnnGraphBuilderTanhOperator(GetHandle());
        return FusionOperator::Acquire(result);
    }
    Operand GraphBuilder::Transpose(Operand const& input, TransposeOptions const * options) const {
        auto result = wnnGraphBuilderTranspose(GetHandle(), input.GetHandle(), reinterpret_cast<WNNTransposeOptions const * >(options));
        return Operand::Acquire(result);
    }
    void GraphBuilder::WebnnReference(WNNGraphBuilder handle) {
        if (handle != nullptr) {
            wnnGraphBuilderReference(handle);
        }
    }
    void GraphBuilder::WebnnRelease(WNNGraphBuilder handle) {
        if (handle != nullptr) {
            wnnGraphBuilderRelease(handle);
        }
    }

    // Instance

    static_assert(sizeof(Instance) == sizeof(WNNInstance), "sizeof mismatch for Instance");
    static_assert(alignof(Instance) == alignof(WNNInstance), "alignof mismatch for Instance");

    Context Instance::CreateContext(ContextOptions const * options) const {
        auto result = wnnInstanceCreateContext(GetHandle(), reinterpret_cast<WNNContextOptions const * >(options));
        return Context::Acquire(result);
    }
    Context Instance::CreateContextWithGpuDevice(GpuDevice const * gpuDevice) const {
        auto result = wnnInstanceCreateContextWithGpuDevice(GetHandle(), reinterpret_cast<WNNGpuDevice const * >(gpuDevice));
        return Context::Acquire(result);
    }
    GraphBuilder Instance::CreateGraphBuilder(Context const& context) const {
        auto result = wnnInstanceCreateGraphBuilder(GetHandle(), context.GetHandle());
        return GraphBuilder::Acquire(result);
    }
    NamedInputs Instance::CreateNamedInputs() const {
        auto result = wnnInstanceCreateNamedInputs(GetHandle());
        return NamedInputs::Acquire(result);
    }
    NamedOperands Instance::CreateNamedOperands() const {
        auto result = wnnInstanceCreateNamedOperands(GetHandle());
        return NamedOperands::Acquire(result);
    }
    NamedOutputs Instance::CreateNamedOutputs() const {
        auto result = wnnInstanceCreateNamedOutputs(GetHandle());
        return NamedOutputs::Acquire(result);
    }
    OperatorArray Instance::CreateOperatorArray() const {
        auto result = wnnInstanceCreateOperatorArray(GetHandle());
        return OperatorArray::Acquire(result);
    }
    void Instance::WebnnReference(WNNInstance handle) {
        if (handle != nullptr) {
            wnnInstanceReference(handle);
        }
    }
    void Instance::WebnnRelease(WNNInstance handle) {
        if (handle != nullptr) {
            wnnInstanceRelease(handle);
        }
    }

    // NamedInputs

    static_assert(sizeof(NamedInputs) == sizeof(WNNNamedInputs), "sizeof mismatch for NamedInputs");
    static_assert(alignof(NamedInputs) == alignof(WNNNamedInputs), "alignof mismatch for NamedInputs");

    void NamedInputs::Set(char const * name, Input const * input) const {
        wnnNamedInputsSet(GetHandle(), reinterpret_cast<char const * >(name), reinterpret_cast<WNNInput const * >(input));
    }
    void NamedInputs::WebnnReference(WNNNamedInputs handle) {
        if (handle != nullptr) {
            wnnNamedInputsReference(handle);
        }
    }
    void NamedInputs::WebnnRelease(WNNNamedInputs handle) {
        if (handle != nullptr) {
            wnnNamedInputsRelease(handle);
        }
    }

    // NamedOperands

    static_assert(sizeof(NamedOperands) == sizeof(WNNNamedOperands), "sizeof mismatch for NamedOperands");
    static_assert(alignof(NamedOperands) == alignof(WNNNamedOperands), "alignof mismatch for NamedOperands");

    void NamedOperands::Set(char const * name, Operand const& operand) const {
        wnnNamedOperandsSet(GetHandle(), reinterpret_cast<char const * >(name), operand.GetHandle());
    }
    void NamedOperands::WebnnReference(WNNNamedOperands handle) {
        if (handle != nullptr) {
            wnnNamedOperandsReference(handle);
        }
    }
    void NamedOperands::WebnnRelease(WNNNamedOperands handle) {
        if (handle != nullptr) {
            wnnNamedOperandsRelease(handle);
        }
    }

    // NamedOutputs

    static_assert(sizeof(NamedOutputs) == sizeof(WNNNamedOutputs), "sizeof mismatch for NamedOutputs");
    static_assert(alignof(NamedOutputs) == alignof(WNNNamedOutputs), "alignof mismatch for NamedOutputs");

    void NamedOutputs::Get(char const * name, ArrayBufferView * resource) const {
        wnnNamedOutputsGet(GetHandle(), reinterpret_cast<char const * >(name), reinterpret_cast<WNNArrayBufferView * >(resource));
    }
    void NamedOutputs::Set(char const * name, Resource const * resource) const {
        wnnNamedOutputsSet(GetHandle(), reinterpret_cast<char const * >(name), reinterpret_cast<WNNResource const * >(resource));
    }
    void NamedOutputs::WebnnReference(WNNNamedOutputs handle) {
        if (handle != nullptr) {
            wnnNamedOutputsReference(handle);
        }
    }
    void NamedOutputs::WebnnRelease(WNNNamedOutputs handle) {
        if (handle != nullptr) {
            wnnNamedOutputsRelease(handle);
        }
    }

    // Operand

    static_assert(sizeof(Operand) == sizeof(WNNOperand), "sizeof mismatch for Operand");
    static_assert(alignof(Operand) == alignof(WNNOperand), "alignof mismatch for Operand");

    void Operand::WebnnReference(WNNOperand handle) {
        if (handle != nullptr) {
            wnnOperandReference(handle);
        }
    }
    void Operand::WebnnRelease(WNNOperand handle) {
        if (handle != nullptr) {
            wnnOperandRelease(handle);
        }
    }

    // OperandArray

    static_assert(sizeof(OperandArray) == sizeof(WNNOperandArray), "sizeof mismatch for OperandArray");
    static_assert(alignof(OperandArray) == alignof(WNNOperandArray), "alignof mismatch for OperandArray");

    Operand OperandArray::Get(size_t index) const {
        auto result = wnnOperandArrayGet(GetHandle(), index);
        return Operand::Acquire(result);
    }
    size_t OperandArray::Size() const {
        auto result = wnnOperandArraySize(GetHandle());
        return result;
    }
    void OperandArray::WebnnReference(WNNOperandArray handle) {
        if (handle != nullptr) {
            wnnOperandArrayReference(handle);
        }
    }
    void OperandArray::WebnnRelease(WNNOperandArray handle) {
        if (handle != nullptr) {
            wnnOperandArrayRelease(handle);
        }
    }

    // OperatorArray

    static_assert(sizeof(OperatorArray) == sizeof(WNNOperatorArray), "sizeof mismatch for OperatorArray");
    static_assert(alignof(OperatorArray) == alignof(WNNOperatorArray), "alignof mismatch for OperatorArray");

    FusionOperator OperatorArray::Get(size_t index) const {
        auto result = wnnOperatorArrayGet(GetHandle(), index);
        return FusionOperator::Acquire(result);
    }
    void OperatorArray::Set(FusionOperator const& wnnOperator) const {
        wnnOperatorArraySet(GetHandle(), wnnOperator.GetHandle());
    }
    size_t OperatorArray::Size() const {
        auto result = wnnOperatorArraySize(GetHandle());
        return result;
    }
    void OperatorArray::WebnnReference(WNNOperatorArray handle) {
        if (handle != nullptr) {
            wnnOperatorArrayReference(handle);
        }
    }
    void OperatorArray::WebnnRelease(WNNOperatorArray handle) {
        if (handle != nullptr) {
            wnnOperatorArrayRelease(handle);
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
