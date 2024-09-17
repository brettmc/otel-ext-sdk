#ifndef OTEL_EXT_SDK_SCOPE_H
#define OTEL_EXT_SDK_SCOPE_H

#include <iterator>
#include <opentelemetry/trace/scope.h>
#include <opentelemetry/context/runtime_context.h>
#include <opentelemetry/trace/span.h>
#include <memory>

namespace trace_sdk
{
    class Scope
    {
    private:
        bool detached = false;
        opentelemetry::v1::nostd::unique_ptr<opentelemetry::v1::context::Token> token;
        //opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Scope> scope;

    public:
        Scope(opentelemetry::v1::nostd::unique_ptr<opentelemetry::v1::context::Token>);
        ~Scope();
        bool Detach();
    };
} // namespace trace_sdk

#endif //OTEL_EXT_SDK_SCOPE_H
