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
        cpp_span->UpdateName(name);
    }
    void Span::SetStatus(char *status, char *description) {
        cpp_span->SetStatus(_GetStatusCode(status), description);
    }

    opentelemetry::v1::nostd::unique_ptr<opentelemetry::v1::context::Token> Span::Activate() {
        php_printf("(c++)Span::Activate\n");
        //opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Scope> scope(new opentelemetry::v1::trace::Scope(cpp_span));
        //return scope;

        return opentelemetry::context::RuntimeContext::Attach(cpp_span->GetContext());
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