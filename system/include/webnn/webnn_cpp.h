#ifndef WEBNN_CPP_H_
#define WEBNN_CPP_H_

#include "webnn/webnn.h"
#include "webnn/EnumClassBitmasks.h"

#include <limits>

namespace ml {

    enum class AutoPad : uint32_t {
        Explicit = 0x00000000,
        SameUpper = 0x00000001,
        SameLower = 0x00000002,
    };

    enum class ComputeGraphStatus : uint32_t {
        Success = 0x00000000,
        Error = 0x00000001,
        ContextLost = 0x00000002,
        Unknown = 0x00000003,
    };

    enum class DevicePreference : uint32_t {
        Default = 0x00000000,
        Gpu = 0x00000001,
        Cpu = 0x00000002,
    };

    enum class ErrorFilter : uint32_t {
        None = 0x00000000,
        Validation = 0x00000001,
        OutOfMemory = 0x00000002,
    };

    enum class ErrorType : uint32_t {
        NoError = 0x00000000,
        Validation = 0x00000001,
        OutOfMemory = 0x00000002,
        Unknown = 0x00000003,
        DeviceLost = 0x00000004,
    };

    enum class FilterOperandLayout : uint32_t {
        Oihw = 0x00000000,
        Hwio = 0x00000001,
        Ohwi = 0x00000002,
        Ihwo = 0x00000003,
    };

    enum class InputOperandLayout : uint32_t {
        Nchw = 0x00000000,
        Nhwc = 0x00000001,
    };

    enum class InterpolationMode : uint32_t {
        NearestNeighbor = 0x00000000,
        Linear = 0x00000001,
    };

    enum class OperandType : uint32_t {
        Float32 = 0x00000000,
        Float16 = 0x00000001,
        Int32 = 0x00000002,
        Uint32 = 0x00000003,
        Int8 = 0x00000004,
        Uint8 = 0x00000005,
    };

    enum class PaddingMode : uint32_t {
        Constant = 0x00000000,
        Edge = 0x00000001,
        Reflection = 0x00000002,
        Symmetric = 0x00000003,
    };

    enum class PowerPreference : uint32_t {
        Default = 0x00000000,
        High_performance = 0x00000001,
        Low_power = 0x00000002,
    };

    enum class RecurrentNetworkDirection : uint32_t {
        Forward = 0x00000000,
        Backward = 0x00000001,
        Both = 0x00000002,
    };

    enum class RecurrentNetworkWeightLayout : uint32_t {
        Zrn = 0x00000000,
        Rzn = 0x00000001,
    };




    using Proc = WebnnProc;
    using ErrorCallback = MLErrorCallback;

    class Context;
    class Graph;
    class GraphBuilder;
    class NamedInputs;
    class NamedOperands;
    class NamedOutputs;
    class Operand;
    class OperandArray;
    class Operator;
    class OperatorArray;

    struct ArrayBufferView;
    struct BatchNormOptions;
    struct ClampOptions;
    struct ContextOptions;
    struct Conv2dOptions;
    struct GemmOptions;
    struct GruOptions;
    struct InstanceNormOptions;
    struct LeakyReluOptions;
    struct OperandDescriptor;
    struct PadOptions;
    struct Pool2dOptions;
    struct ReduceOptions;
    struct Resample2dOptions;
    struct SliceOptions;
    struct SplitOptions;
    struct SqueezeOptions;
    struct TransposeOptions;
    struct Input;

    template<typename Derived, typename CType>
    class ObjectBase {
      public:
        ObjectBase() = default;
        ObjectBase(CType handle): mHandle(handle) {
            if (mHandle) Derived::WebnnReference(mHandle);
        }
        ~ObjectBase() {
            if (mHandle) Derived::WebnnRelease(mHandle);
        }

        ObjectBase(ObjectBase const& other)
            : ObjectBase(other.GetHandle()) {
        }
        Derived& operator=(ObjectBase const& other) {
            if (&other != this) {
                if (mHandle) Derived::WebnnRelease(mHandle);
                mHandle = other.mHandle;
                if (mHandle) Derived::WebnnReference(mHandle);
            }

            return static_cast<Derived&>(*this);
        }

        ObjectBase(ObjectBase&& other) {
            mHandle = other.mHandle;
            other.mHandle = 0;
        }
        Derived& operator=(ObjectBase&& other) {
            if (&other != this) {
                if (mHandle) Derived::WebnnRelease(mHandle);
                mHandle = other.mHandle;
                other.mHandle = 0;
            }

            return static_cast<Derived&>(*this);
        }

        ObjectBase(std::nullptr_t) {}
        Derived& operator=(std::nullptr_t) {
            if (mHandle != nullptr) {
                Derived::WebnnRelease(mHandle);
                mHandle = nullptr;
            }
            return static_cast<Derived&>(*this);
        }

        bool operator==(std::nullptr_t) const {
            return mHandle == nullptr;
        }
        bool operator!=(std::nullptr_t) const {
            return mHandle != nullptr;
        }

        explicit operator bool() const {
            return mHandle != nullptr;
        }
        CType GetHandle() const {
            return mHandle;
        }
        CType Release() {
            CType result = mHandle;
            mHandle = 0;
            return result;
        }
        static Derived Acquire(CType handle) {
            Derived result;
            result.mHandle = handle;
            return result;
        }

      protected:
        CType mHandle = nullptr;
    };



    class Context : public ObjectBase<Context, MLContext> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        bool PopErrorScope(ErrorCallback callback, void * userdata) const;
        void PushErrorScope(ErrorFilter filter) const;
        void SetUncapturedErrorCallback(ErrorCallback callback, void * userdata) const;

      private:
        friend ObjectBase<Context, MLContext>;
        static void WebnnReference(MLContext handle);
        static void WebnnRelease(MLContext handle);
    };

    class Graph : public ObjectBase<Graph, MLGraph> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        ComputeGraphStatus Compute(NamedInputs const& inputs, NamedOutputs const& outputs) const;

      private:
        friend ObjectBase<Graph, MLGraph>;
        static void WebnnReference(MLGraph handle);
        static void WebnnRelease(MLGraph handle);
    };

    class GraphBuilder : public ObjectBase<GraphBuilder, MLGraphBuilder> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Operand Abs(Operand const& input) const;
        Operand Add(Operand const& a, Operand const& b) const;
        Operand AveragePool2d(Operand const& input, Pool2dOptions const * options = nullptr) const;
        Operand BatchNorm(Operand const& input, Operand const& mean, Operand const& variance, BatchNormOptions const * options = nullptr) const;
        Graph Build(NamedOperands const& namedOperands) const;
        Operand Ceil(Operand const& input) const;
        Operand Clamp(Operand const& input, ClampOptions const * options = nullptr) const;
        Operator ClampOperator(ClampOptions const * options = nullptr) const;
        Operand Concat(uint32_t inputsCount, Operand const * inputs, uint32_t axis) const;
        Operand Constant(OperandDescriptor const * desc, ArrayBufferView const * value) const;
        Operand Conv2d(Operand const& input, Operand const& filter, Conv2dOptions const * options = nullptr) const;
        Operand Cos(Operand const& input) const;
        Operand Div(Operand const& a, Operand const& b) const;
        Operand Exp(Operand const& input) const;
        Operand Floor(Operand const& input) const;
        Operand Gemm(Operand const& a, Operand const& b, GemmOptions const * options = nullptr) const;
        OperandArray Gru(Operand const& input, Operand const& weight, Operand const& recurrentWeight, int32_t steps, int32_t hiddenSize, GruOptions const * options = nullptr) const;
        Operand HardSwish(Operand const& input) const;
        Operator HardSwishOperator() const;
        Operand Input(char const * name, OperandDescriptor const * desc) const;
        Operand InstanceNorm(Operand const& input, InstanceNormOptions const * options = nullptr) const;
        Operand L2Pool2d(Operand const& input, Pool2dOptions const * options = nullptr) const;
        Operand LeakyRelu(Operand const& input, LeakyReluOptions const * options = nullptr) const;
        Operator LeakyReluOperator(LeakyReluOptions const * options = nullptr) const;
        Operand Log(Operand const& input) const;
        Operand Matmul(Operand const& a, Operand const& b) const;
        Operand Max(Operand const& a, Operand const& b) const;
        Operand MaxPool2d(Operand const& input, Pool2dOptions const * options = nullptr) const;
        Operand Min(Operand const& a, Operand const& b) const;
        Operand Mul(Operand const& a, Operand const& b) const;
        Operand Neg(Operand const& input) const;
        Operand Pad(Operand const& input, Operand const& padding, PadOptions const * options = nullptr) const;
        Operand Pow(Operand const& a, Operand const& b) const;
        Operand ReduceL1(Operand const& input, ReduceOptions const * options = nullptr) const;
        Operand ReduceL2(Operand const& input, ReduceOptions const * options = nullptr) const;
        Operand ReduceMax(Operand const& input, ReduceOptions const * options = nullptr) const;
        Operand ReduceMean(Operand const& input, ReduceOptions const * options = nullptr) const;
        Operand ReduceMin(Operand const& input, ReduceOptions const * options = nullptr) const;
        Operand ReduceProduct(Operand const& input, ReduceOptions const * options = nullptr) const;
        Operand ReduceSum(Operand const& input, ReduceOptions const * options = nullptr) const;
        Operand Relu(Operand const& input) const;
        Operator ReluOperator() const;
        Operand Resample2d(Operand const& input, Resample2dOptions const * options = nullptr) const;
        Operand Reshape(Operand const& input, int32_t const * newShape, uint32_t newShapeCount) const;
        Operand Sigmoid(Operand const& input) const;
        Operator SigmoidOperator() const;
        Operand Sin(Operand const& input) const;
        Operand Slice(Operand const& input, int32_t const * starts, uint32_t startsCount, int32_t const * sizes, uint32_t sizesCount, SliceOptions const * options = nullptr) const;
        Operand Softmax(Operand const& input) const;
        OperandArray Split(Operand const& input, uint32_t const * splits, uint32_t splitsCount, SplitOptions const * options = nullptr) const;
        Operand Squeeze(Operand const& input, SqueezeOptions const * options = nullptr) const;
        Operand Sub(Operand const& a, Operand const& b) const;
        Operand Tan(Operand const& input) const;
        Operand Tanh(Operand const& input) const;
        Operator TanhOperator() const;
        Operand Transpose(Operand const& input, TransposeOptions const * options = nullptr) const;

      private:
        friend ObjectBase<GraphBuilder, MLGraphBuilder>;
        static void WebnnReference(MLGraphBuilder handle);
        static void WebnnRelease(MLGraphBuilder handle);
    };

    class NamedInputs : public ObjectBase<NamedInputs, MLNamedInputs> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Set(char const * name, Input const * input) const;

      private:
        friend ObjectBase<NamedInputs, MLNamedInputs>;
        static void WebnnReference(MLNamedInputs handle);
        static void WebnnRelease(MLNamedInputs handle);
    };

    class NamedOperands : public ObjectBase<NamedOperands, MLNamedOperands> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Set(char const * name, Operand const& operand) const;

      private:
        friend ObjectBase<NamedOperands, MLNamedOperands>;
        static void WebnnReference(MLNamedOperands handle);
        static void WebnnRelease(MLNamedOperands handle);
    };

    class NamedOutputs : public ObjectBase<NamedOutputs, MLNamedOutputs> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        void Set(char const * name, ArrayBufferView const * resource) const;

      private:
        friend ObjectBase<NamedOutputs, MLNamedOutputs>;
        static void WebnnReference(MLNamedOutputs handle);
        static void WebnnRelease(MLNamedOutputs handle);
    };

    class Operand : public ObjectBase<Operand, MLOperand> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;


      private:
        friend ObjectBase<Operand, MLOperand>;
        static void WebnnReference(MLOperand handle);
        static void WebnnRelease(MLOperand handle);
    };

    class OperandArray : public ObjectBase<OperandArray, MLOperandArray> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Operand Get(size_t index) const;
        size_t Size() const;

      private:
        friend ObjectBase<OperandArray, MLOperandArray>;
        static void WebnnReference(MLOperandArray handle);
        static void WebnnRelease(MLOperandArray handle);
    };

    class Operator : public ObjectBase<Operator, MLOperator> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;


      private:
        friend ObjectBase<Operator, MLOperator>;
        static void WebnnReference(MLOperator handle);
        static void WebnnRelease(MLOperator handle);
    };

    class OperatorArray : public ObjectBase<OperatorArray, MLOperatorArray> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Operator Get(size_t index) const;
        void Set(Operator const& mlOperator) const;
        size_t Size() const;

      private:
        friend ObjectBase<OperatorArray, MLOperatorArray>;
        static void WebnnReference(MLOperatorArray handle);
        static void WebnnRelease(MLOperatorArray handle);
    };


    struct ChainedStruct {
        ChainedStruct const * nextInChain = nullptr;
        // SType sType = SType::Invalid;
    };

    struct ArrayBufferView {
        void * buffer;
        size_t byteLength;
        size_t byteOffset = 0;
    };

    struct BatchNormOptions {
        Operand scale;
        Operand bias;
        uint32_t axis = 1;
        float epsilon = 1e-05;
        Operator activation;
    };

    struct ClampOptions {
        float minValue = std::numeric_limits<float>::lowest();
        float maxValue = std::numeric_limits<float>::max();
    };

    struct ContextOptions {
        DevicePreference devicePreference = DevicePreference::Default;
        PowerPreference powerPreference = PowerPreference::Default;
    };

    struct Conv2dOptions {
        uint32_t paddingCount = 0;
        int32_t const * padding = nullptr;
        uint32_t stridesCount = 0;
        int32_t const * strides = nullptr;
        uint32_t dilationsCount = 0;
        int32_t const * dilations = nullptr;
        uint32_t outputPaddingCount = 0;
        int32_t const * outputPadding = nullptr;
        uint32_t outputSizesCount = 0;
        int32_t const * outputSizes = nullptr;
        AutoPad autoPad = AutoPad::Explicit;
        bool transpose = false;
        int32_t groups = 1;
        InputOperandLayout inputLayout = InputOperandLayout::Nchw;
        FilterOperandLayout filterLayout = FilterOperandLayout::Oihw;
        Operand bias;
        Operator activation;
    };

    struct GemmOptions {
        Operand c;
        float alpha = 1.0;
        float beta = 1.0;
        bool aTranspose = false;
        bool bTranspose = false;
    };

    struct GruOptions {
        Operand bias;
        Operand recurrentBias;
        Operand initialHiddenState;
        bool resetAfter = true;
        bool returnSequence = false;
        RecurrentNetworkDirection direction = RecurrentNetworkDirection::Forward;
        RecurrentNetworkWeightLayout layout = RecurrentNetworkWeightLayout::Zrn;
        OperatorArray activations;
    };

    struct InstanceNormOptions {
        Operand scale;
        Operand bias;
        float epsilon = 1e-05;
        InputOperandLayout layout = InputOperandLayout::Nchw;
    };

    struct LeakyReluOptions {
        float alpha = 0.01;
    };

    struct OperandDescriptor {
        OperandType type;
        int32_t const * dimensions;
        uint32_t dimensionsCount = 0;
    };

    struct PadOptions {
        PaddingMode mode = PaddingMode::Constant;
        float value = 0;
    };

    struct Pool2dOptions {
        uint32_t windowDimensionsCount = 0;
        int32_t const * windowDimensions = nullptr;
        uint32_t paddingCount = 0;
        int32_t const * padding = nullptr;
        uint32_t stridesCount = 0;
        int32_t const * strides = nullptr;
        uint32_t dilationsCount = 0;
        int32_t const * dilations = nullptr;
        AutoPad autoPad = AutoPad::Explicit;
        InputOperandLayout layout = InputOperandLayout::Nchw;
    };

    struct ReduceOptions {
        uint32_t axesCount = 0;
        int32_t const * axes = nullptr;
        bool keepDimensions = false;
    };

    struct Resample2dOptions {
        InterpolationMode mode = InterpolationMode::NearestNeighbor;
        uint32_t scalesCount = 0;
        float const * scales = nullptr;
        uint32_t sizesCount = 0;
        int32_t const * sizes = nullptr;
        uint32_t axesCount = 0;
        int32_t const * axes = nullptr;
    };

    struct SliceOptions {
        uint32_t axesCount = 0;
        int32_t const * axes = nullptr;
    };

    struct SplitOptions {
        int32_t axis = 0;
    };

    struct SqueezeOptions {
        uint32_t axesCount = 0;
        int32_t const * axes = nullptr;
    };

    struct TransposeOptions {
        uint32_t permutationCount = 0;
        int32_t const * permutation = nullptr;
    };

    struct Input {
        ArrayBufferView resource;
        int32_t const * dimensions = nullptr;
        uint32_t dimensionsCount = 0;
    };


    GraphBuilder CreateGraphBuilder(Context context);
    NamedInputs CreateNamedInputs();
    NamedOperands CreateNamedOperands();
    NamedOutputs CreateNamedOutputs();
    OperatorArray CreateOperatorArray();

}  // namespace webnn

#endif // WEBNN_CPP_H_
