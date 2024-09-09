#ifndef OTEL_EXT_SDK_SPAN_BUILDER_H
#define OTEL_EXT_SDK_SPAN_BUILDER_H

#include <opentelemetry/trace/span.h>
#include <memory>
#include <string>

// C++ class for SpanBuilder
namespace trace_sdk {
    class SpanBuilder {
    public:
        SpanBuilder(opentelemetry::v1::nostd::shared_ptr <opentelemetry::v1::trace::Tracer> tracer, const std::string &span_name);
        opentelemetry::v1::nostd::shared_ptr <opentelemetry::trace::Span> StartSpan();
        void SetSpanKind(int kind);
        void AddAttribute(const std::string &key, const opentelemetry::common::AttributeValue &value);
        void SetStartTimestamp(int timestamp);

    private:
        opentelemetry::v1::nostd::shared_ptr <opentelemetry::trace::Tracer> cpp_tracer;
        std::string span_name;
        opentelemetry::trace::SpanKind span_kind = opentelemetry::trace::SpanKind::kInternal;
        bool has_start_time = false;
        opentelemetry::common::SystemTimestamp start_time;
        std::map<std::string, opentelemetry::common::AttributeValue> attributes;
    };
}

#endif //OTEL_EXT_SDK_SPAN_BUILDER_H
