#ifndef OTEL_EXT_SDK_SPAN_H
#define OTEL_EXT_SDK_SPAN_H

#include <memory>
#include "opentelemetry/sdk/trace/tracer.h"
#include "opentelemetry/trace/scope.h"
#include "opentelemetry/trace/span.h"
#include "opentelemetry/trace/span_context.h"
#include "opentelemetry/trace/span_metadata.h"

namespace trace_sdk {
    class Span {
    public:
        Span(opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span>);
        ~Span(); // Destructor

        opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> GetInternal();
        void UpdateName(char *name);
        void SetStatus(char *status, char *description);
        void End();
        std::unique_ptr<opentelemetry::v1::trace::Scope> Activate();
        std::shared_ptr<opentelemetry::v1::trace::SpanContext> GetContext();
    private:
        opentelemetry::trace::StatusCode _GetStatusCode(char *status);
        opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> cpp_span;
        opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Tracer> cpp_tracer;
        std::shared_ptr<opentelemetry::v1::trace::SpanContext> cpp_span_context;
    };
}

#endif //OTEL_EXT_SDK_SPAN_H
