#ifndef OTEL_EXT_SDK_SPAN_CONTEXT_H
#define OTEL_EXT_SDK_SPAN_CONTEXT_H

#include <memory>
#include "opentelemetry/trace/span_context.h"

namespace trace_sdk {
    class SpanContext {
    public:
        SpanContext(opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::SpanContext> span_context);
        ~SpanContext(); // Destructor

        void DoSomething();  // Placeholder function
        std::string GetTraceId();
        std::string GetSpanId();
        int GetTraceFlags();
        bool IsSampled();
    private:
        opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::SpanContext> cpp_span_context;
    };
}

#endif //OTEL_EXT_SDK_SPAN_CONTEXT_H
