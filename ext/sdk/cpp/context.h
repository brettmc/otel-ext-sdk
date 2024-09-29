#ifndef OTEL_EXT_SDK_CONTEXT_H
#define OTEL_EXT_SDK_CONTEXT_H

#include "php.h"
#include <opentelemetry/trace/scope.h>
#include <opentelemetry/context/context.h>
#include "opentelemetry/context/runtime_context.h"
#include <memory>

namespace trace_sdk
{
    class Context
    {
    public:
        //Context();
        Context(std::shared_ptr<opentelemetry::context::Context>);
        ~Context();
        //void Detach();
        static void Test();
        static Context *GetCurrent();
        zval GetValue(char *key);
        Context *SetValue(char *key, zval* value);
    private:
        opentelemetry::v1::context::ContextValue FromZval(zval *value);
        zval ToZval(opentelemetry::v1::context::ContextValue value);
        std::shared_ptr<opentelemetry::context::Context> cpp_context;
    };
} // namespace trace_sdk

#endif //OTEL_EXT_SDK_CONTEXT_H
