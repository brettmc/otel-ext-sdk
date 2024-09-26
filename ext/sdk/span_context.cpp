#include "span_context.h"
#include "php.h"

namespace trace_sdk {
    SpanContext::SpanContext(opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::SpanContext> span_context) : cpp_span_context(span_context) {
        //php_printf("(c++)SpanContext created: %p\n", cpp_span_context);
    }

    SpanContext::~SpanContext() {
        //php_printf("(c++)SpanContext destroyed\n");
    }

    opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::SpanContext> SpanContext::GetInternal() {
        return cpp_span_context;
    }

    void SpanContext::DoSomething() {
        //php_printf("(c++)SpanContext is doing something!\n");
    }
    std::string SpanContext::GetTraceId() {
        char buf[32];
        cpp_span_context->trace_id().ToLowerBase16(buf);
        std::string trace_id = std::string(buf, sizeof(buf));
        return trace_id;
    }
    std::string SpanContext::GetSpanId() {
        char buf[16];
        cpp_span_context->span_id().ToLowerBase16(buf);
        return std::string(buf, sizeof(buf));
    }
    int SpanContext::GetTraceFlags() {
        return cpp_span_context->trace_flags().flags();
    }
    bool SpanContext::IsSampled() {
        return cpp_span_context->IsSampled();
    }
    bool SpanContext::IsRemote()
    {
        return cpp_span_context->IsRemote();
    }
}