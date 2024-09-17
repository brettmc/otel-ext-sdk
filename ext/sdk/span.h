#ifndef OTEL_EXT_SDK_SPAN_H
#define OTEL_EXT_SDK_SPAN_H

#ifdef __cplusplus
#include <memory>
#include "opentelemetry/sdk/trace/tracer.h"
#include "opentelemetry/trace/scope.h"
#include "opentelemetry/trace/span.h"
#include "opentelemetry/trace/span_metadata.h"
#include "opentelemetry/context/runtime_context.h"

namespace trace_sdk {
    class Span {
    public:
        Span(opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> span);
        ~Span(); // Destructor

        void DoSomething();  // Placeholder function
        void UpdateName(char *name);
        void SetStatus(char *status, char *description);
        void End();
        //opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Scope> Activate();
        opentelemetry::v1::nostd::unique_ptr<opentelemetry::v1::context::Token> Activate();
    private:
        opentelemetry::trace::StatusCode _GetStatusCode(char *status);
        opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> cpp_span;
    };
}

#endif //__cplusplus
#endif //OTEL_EXT_SDK_SPAN_H
