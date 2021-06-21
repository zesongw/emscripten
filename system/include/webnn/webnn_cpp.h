#ifndef WEBNN_CPP_H_
#define WEBNN_CPP_H_

#include "webnn/webnn.h"
#include "webnn/EnumClassBitmasks.h"

namespace ml {

    enum class AutoPad : uint32_t {
        Explicit = 0x00000000,
        SameUpper = 0x00000001,
        SameLower = 0x00000002,
    };

    enum class BuildGraphStatus : uint32_t {
        Success = 0x00000000,
        Error = 0x00000001,
        ContextLost = 0x00000002,
        Unknown = 0x00000003,
    };

    enum class ComputeGraphStatus : uint32_t {
        Success = 0x00000000,
        Error = 0x00000001,
        ContextLost = 0x00000002,
        Unknown = 0x00000003,
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

    enum class FusedActivation : uint32_t {
        None = 0x00000000,
        Relu = 0x00000001,
    };

    enum class InputOperandLayout : uint32_t {
        Nchw = 0x00000000,
        Nhwc = 0x00000001,
    };

    enum class OperandType : uint32_t {
        Float32 = 0x00000000,
        Float16 = 0x00000001,
        Int32 = 0x00000002,
        Uint32 = 0x00000003,
        Int8 = 0x00000004,
        Uint8 = 0x00000005,
    };

    enum class PowerPreference : uint32_t {
        Default = 0x00000000,
        High_performance = 0x00000001,
        Low_power = 0x00000002,
    };




    using Proc = WebnnProc;
    using BuildGraphCallback = MLBuildGraphCallback;
    using ComputeGraphCallback = MLComputeGraphCallback;
    using ErrorCallback = MLErrorCallback;

    class Context;
    class Graph;
    class GraphBuilder;
    class NamedInputs;
    class NamedOperands;
    class NamedOutputs;
    class NamedResults;
    class Operand;
    class Result;

    struct BatchNormOptions;
    struct ClampOptions;
    struct ContextOptions;
    struct Conv2dOptions;
    struct GemmOptions;
    struct Input;
    struct LeakyReluOptions;
    struct OperandDescriptor;
    struct Output;
    struct Pool2dOptions;
    struct TransposeOptions;

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

        void Compute(NamedInputs const& inputs, ComputeGraphCallback callback, void * userdata, NamedOutputs const& outputs) const;
        ComputeGraphStatus ComputeSync(NamedInputs const& inputs, NamedOutputs const& outputs) const;

      private:
        friend ObjectBase<Graph, MLGraph>;
        static void WebnnReference(MLGraph handle);
        static void WebnnRelease(MLGraph handle);
    };

    class GraphBuilder : public ObjectBase<GraphBuilder, MLGraphBuilder> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Operand Add(Operand const& a, Operand const& b) const;
        Operand AveragePool2d(Operand const& input, Pool2dOptions const * options = nullptr) const;
        Operand BatchNorm(Operand const& input, Operand const& mean, Operand const& variance, BatchNormOptions const * options = nullptr) const;
        void Build(NamedOperands const& namedOperands, BuildGraphCallback callback, void * userdata) const;
        Graph BuildSync(NamedOperands const& namedOperands) const;
        Operand Clamp(Operand const& input, ClampOptions const * options = nullptr) const;
        Operand Concat(uint32_t inputsCount, Operand const * inputs, uint32_t axis) const;
        Operand Constant(OperandDescriptor const * desc, void const * value, size_t size) const;
        Operand Conv2d(Operand const& input, Operand const& filter, Conv2dOptions const * options = nullptr) const;
        Operand Gemm(Operand const& a, Operand const& b, GemmOptions const * options = nullptr) const;
        Operand Input(char const * name, OperandDescriptor const * desc) const;
        Operand LeakyRelu(Operand const& input, LeakyReluOptions const * options = nullptr) const;
        Operand Matmul(Operand const& a, Operand const& b) const;
        Operand MaxPool2d(Operand const& input, Pool2dOptions const * options = nullptr) const;
        Operand Mul(Operand const& a, Operand const& b) const;
        Operand Relu(Operand const& input) const;
        Operand Reshape(Operand const& input, int32_t const * newShape, uint32_t newShapeCount) const;
        Operand Softmax(Operand const& input) const;
        Operand Sub(Operand const& a, Operand const& b) const;
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

        void Set(char const * name, Output const * output) const;

      private:
        friend ObjectBase<NamedOutputs, MLNamedOutputs>;
        static void WebnnReference(MLNamedOutputs handle);
        static void WebnnRelease(MLNamedOutputs handle);
    };

    class NamedResults : public ObjectBase<NamedResults, MLNamedResults> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        Result Get(char const * name) const;

      private:
        friend ObjectBase<NamedResults, MLNamedResults>;
        static void WebnnReference(MLNamedResults handle);
        static void WebnnRelease(MLNamedResults handle);
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

    class Result : public ObjectBase<Result, MLResult> {
      public:
        using ObjectBase::ObjectBase;
        using ObjectBase::operator=;

        const void* Buffer() const;
        uint32_t BufferSize() const;
        const int32_t* Dimensions() const;
        uint32_t DimensionsSize() const;

      private:
        friend ObjectBase<Result, MLResult>;
        static void WebnnReference(MLResult handle);
        static void WebnnRelease(MLResult handle);
    };


    struct ChainedStruct {
        ChainedStruct const * nextInChain = nullptr;
        // SType sType = SType::Invalid;
    };

    struct BatchNormOptions {
        Operand scale;
        Operand bias;
        uint32_t axis = 1;
        float epsilon = 1e-05;
        FusedActivation activation = FusedActivation::None;
    };

    struct ClampOptions {
        Operand minValue;
        Operand maxValue;
    };

    struct ContextOptions {
        PowerPreference powerPreference = PowerPreference::Default;
    };

    struct Conv2dOptions {
        uint32_t paddingCount = 0;
        int32_t const * padding = nullptr;
        uint32_t stridesCount = 0;
        int32_t const * strides = nullptr;
        uint32_t dilationsCount = 0;
        int32_t const * dilations = nullptr;
        AutoPad autoPad = AutoPad::Explicit;
        int32_t groups = 1;
        InputOperandLayout inputLayout = InputOperandLayout::Nchw;
        FilterOperandLayout filterLayout = FilterOperandLayout::Oihw;
        Operand bias;
        FusedActivation activation = FusedActivation::None;
    };

    struct GemmOptions {
        Operand c;
        float alpha = 1.0;
        float beta = 1.0;
        bool aTranspose = false;
        bool bTranspose = false;
    };

    struct Input {
        void const * buffer;
        size_t size;
        int32_t const * dimensions = nullptr;
        uint32_t dimensionsCount = 0;
    };

    struct LeakyReluOptions {
        float alpha = 0.01;
    };

    struct OperandDescriptor {
        OperandType type;
        int32_t const * dimensions;
        uint32_t dimensionsCount = 0;
    };

    struct Output {
        void * buffer = nullptr;
        size_t size;
        int32_t const * dimensions = nullptr;
        uint32_t dimensionsCount = 0;
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

    struct TransposeOptions {
        uint32_t permutationCount = 0;
        int32_t const * permutation = nullptr;
    };


    GraphBuilder CreateGraphBuilder(Context context);
    NamedInputs CreateNamedInputs();
    NamedOperands CreateNamedOperands();
    NamedOutputs CreateNamedOutputs();

}  // namespace webnn

#endif // WEBNN_CPP_H_
