#include "span.h"
#include "php.h"
#include <opentelemetry/trace/scope.h>

namespace trace_sdk {
    Span::Span(opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Span> span) : cpp_span(span) {
        auto context = cpp_span->GetContext();

        //char tbuf[32], sbuf[16];
        //context.trace_id().ToLowerBase16(tbuf);
        //context.span_id().ToLowerBase16(sbuf);
        //std::string trace_id = std::string(tbuf, sizeof(tbuf));
        //std::string span_id = std::string(sbuf, sizeof(sbuf));
        //id = span_id;
        //php_printf("(c++)Span created (with cpp span): %s\n", span_id.c_str());
        //php_printf("Trace ID: %s\n", t);
        //php_printf("(c++)Span ID: %s\n", cpp_span->GetContext().trace_id());

        cpp_span_context = std::make_shared<opentelemetry::v1::trace::SpanContext>(context);
    }

    Span::~Span() {
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