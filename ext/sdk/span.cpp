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

    void Span::UpdateName(char *name) {
        //virtual void UpdateName(nostd::string_view name)
        cpp_span->UpdateName(name);
    }
    void Span::SetStatus(char *status, char *description) {
        cpp_span->SetStatus(_GetStatusCode(status), description);
        //virtual void SetStatus(StatusCode code, nostd::string_view description = "")
    }

    void Span::End() {
        //php_printf("(c++)Span is ending!\n");
        cpp_span->End();
    }

    //private
    opentelemetry::trace::StatusCode Span::_GetStatusCode(char *status) {
        if (strcmp(status, "Ok") == 0) {
            return opentelemetry::trace::StatusCode::kOk;
        } else if (strcmp(status, "Error") == 0) {
            return opentelemetry::trace::StatusCode::kError;
        } else {
            return opentelemetry::trace::StatusCode::kUnset;
        }
    }
}