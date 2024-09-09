#ifndef OTEL_EXT_SDK_SPAN_H
#define OTEL_EXT_SDK_SPAN_H

#include <memory>
#include "opentelemetry/sdk/trace/tracer.h"
#include "opentelemetry/trace/span.h"

namespace trace_sdk {
    class Span {
    public:
        Span(opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> span);
        ~Span(); // Destructor

        void DoSomething();  // Placeholder function
        void End();
    private:
        opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> cpp_span;
    };
}

#endif //OTEL_EXT_SDK_SPAN_H
