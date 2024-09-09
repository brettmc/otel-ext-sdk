#ifndef OPENTELEMETRY_SDK_TRACER_H
#define OPENTELEMETRY_SDK_TRACER_H

#include <memory>
#include "opentelemetry/sdk/trace/tracer.h"

namespace trace_sdk {
    class Tracer {
    public:
        Tracer(opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Tracer> tracer);
        ~Tracer(); // Destructor

        void DoSomething();  // Placeholder function
        opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> StartSpan();
        opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Tracer> GetTracer();
    private:
        opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Tracer> cpp_tracer;
    };
}
#endif //OPENTELEMETRY_SDK_TRACER_H
