#include "span.h"
#include "php.h"

namespace trace_sdk {
    Span::Span(opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> span) : cpp_span(span) {
        //php_printf("(c++)Span created (with cpp span): %p\n", cpp_span);
    }

    Span::~Span() {
        //php_printf("(c++)Span destroyed\n");
    }

    void Span::DoSomething() {
        //php_printf("(c++)Span is doing something!\n");
    }

    void Span::End() {
        //php_printf("(c++)Span is ending!\n");
        cpp_span->End();
    }
}