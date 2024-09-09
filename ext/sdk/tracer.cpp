#include "tracer.h"
#include "php.h"

namespace trace_sdk {
    Tracer::Tracer(opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Tracer> tracer) : cpp_tracer(tracer) {
        //php_printf("(c++)Tracer created (with cpp tracer): %p\n", cpp_tracer);
    }

    Tracer::~Tracer() {
        //php_printf("(c++)Tracer destroyed\n");
    }

    void Tracer::DoSomething() {
        //php_printf("(c++)Tracer is doing something!\n");
        auto span = cpp_tracer->StartSpan("do-something");
        span->End();
    }
    opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Tracer> Tracer::GetTracer() {
        return cpp_tracer;
    }
    opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> Tracer::StartSpan() {
        //php_printf("(c++)Tracer start span!\n");
        auto span = cpp_tracer->StartSpan("some-span");
        return span;
    }
}