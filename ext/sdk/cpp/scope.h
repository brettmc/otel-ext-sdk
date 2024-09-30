#ifndef OTEL_EXT_SDK_SCOPE_H
#define OTEL_EXT_SDK_SCOPE_H

#include <opentelemetry/trace/scope.h>
#include <opentelemetry/trace/span.h>
#include <memory>

namespace trace_sdk
{
    class Scope
    {
    public:
        explicit Scope(std::unique_ptr<opentelemetry::v1::trace::Scope>);
        ~Scope();
        void Detach();
        void Test();

    private:
        std::unique_ptr<opentelemetry::v1::trace::Scope> cpp_scope;
        bool detached = false;
    };
} // namespace trace_sdk

#endif //OTEL_EXT_SDK_SCOPE_H
