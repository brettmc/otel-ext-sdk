#include "span.h"
#include "php.h"
#include <opentelemetry/trace/scope.h>

namespace trace_sdk {
    Span::Span(opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> span) : cpp_span(span) {
    }

    Span::~Span() {
        //php_printf("(c++)Span::destruct\n");
    }

    opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> Span::GetInternal() {
        return cpp_span;
    }

    void Span::UpdateName(char *name) {
        cpp_span->UpdateName(name);
    }
    void Span::SetStatus(char *status, char *description) {
        cpp_span->SetStatus(_GetStatusCode(status), description);
    }

    std::unique_ptr<opentelemetry::v1::trace::Scope> Span::Activate() {
        //php_printf("(c++)Span::Activate\n");
        std::unique_ptr<opentelemetry::v1::trace::Scope> scope = std::make_unique<opentelemetry::v1::trace::Scope>(cpp_span);
        return scope;
    }

    void Span::End() {
        cpp_span->End();
    }

    std::shared_ptr<opentelemetry::v1::trace::SpanContext> Span::GetContext() {
        if (!cpp_span_context) {
            auto context = cpp_span->GetContext();
            cpp_span_context = std::make_shared<opentelemetry::v1::trace::SpanContext>(context);
        }
        //php_printf("(c++)Span GetContext: %p\n", cpp_span);
        return cpp_span_context;
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