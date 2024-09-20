#include "php.h"
#include "span_builder.h"
#include <opentelemetry/trace/tracer.h>
#include <opentelemetry/trace/span_metadata.h>
#include <opentelemetry/common/key_value_iterable_view.h>
#include <iostream>

namespace trace_sdk {
    // Constructor: Initializes the SpanBuilder with a tracer and span name
    SpanBuilder::SpanBuilder(opentelemetry::v1::nostd::shared_ptr <opentelemetry::v1::trace::Tracer> tracer, const std::string &span_name)
            : cpp_tracer(tracer), span_name(span_name) {}

    opentelemetry::v1::nostd::shared_ptr<opentelemetry::trace::Span> SpanBuilder::StartSpan() {
        opentelemetry::trace::StartSpanOptions options;
        options.kind = span_kind;
        if (has_start_time) {
            options.start_system_time = start_time;
        }
        auto span = cpp_tracer->StartSpan(span_name, attributes, {}, options);  // Start and return the OpenTelemetry C++ Span
        //php_printf("(c++) SpanBuilder started span: %p\n", span);
        return span;
    }

    void SpanBuilder::AddAttribute(const std::string &key, const opentelemetry::common::AttributeValue &value) {
        attributes[key] = value;
    }

    void SpanBuilder::SetStartTimestamp(int timestamp) {
        std::chrono::nanoseconds start_time_ns{timestamp};
        start_time = opentelemetry::common::SystemTimestamp(std::chrono::system_clock::time_point(start_time_ns));
        has_start_time = true;
    }

    opentelemetry::v1::nostd::shared_ptr <opentelemetry::trace::Tracer> SpanBuilder::GetTracer() {
        return cpp_tracer;
    }

    void SpanBuilder::SetSpanKind(int kind)
    {
        switch (kind)
        {
            case 1:
                span_kind = opentelemetry::trace::SpanKind::kServer;
                break;
            case 2:
                span_kind = opentelemetry::trace::SpanKind::kClient;
                break;
            case 3:
                span_kind = opentelemetry::trace::SpanKind::kProducer;
                break;
            case 4:
                span_kind = opentelemetry::trace::SpanKind::kConsumer;
                break;
            default:
                span_kind = opentelemetry::trace::SpanKind::kInternal;  // Default if invalid
        }
    }
}