#include "tracer_manager.h"
#include "tracer.h"
#include "span_builder.h"
#include "span.h"
#include "php.h"
#include <Zend/zend_exceptions.h>
#include <opentelemetry/common/key_value_iterable_view.h>

extern "C" {

// This function destroys the C++ TracerProvider object
void tracer_destroy(trace_sdk_Tracer *tracer) {
    //php_printf("(tracer manager)tracer_destroy\n");
    delete reinterpret_cast<trace_sdk::Tracer*>(tracer);
}

void span_destroy(trace_sdk_Span *span) {
    delete reinterpret_cast<trace_sdk::Span*>(span);
}

void span_builder_destroy(trace_sdk_SpanBuilder *span_builder) {
    delete reinterpret_cast<trace_sdk::SpanBuilder*>(span_builder);
}

trace_sdk_SpanBuilder* tracer_create_span_builder(trace_sdk_Tracer* tracer, const char* span_name) {
    auto t = reinterpret_cast<trace_sdk::Tracer*>(tracer);
    auto cpp_span_builder = new trace_sdk::SpanBuilder(t->GetTracer(), span_name);
    return reinterpret_cast<trace_sdk_SpanBuilder*>(cpp_span_builder);
}

// This function calls the DoSomething method on the C++ Tracer object
void tracer_do_something(trace_sdk_Tracer *tracer) {
    //php_printf("(tracer manager)tracer_do_something\n");
    reinterpret_cast<trace_sdk::Tracer*>(tracer)->DoSomething();
}

trace_sdk_Span *span_builder_start_span(trace_sdk_SpanBuilder *builder) {
    auto cpp_span = reinterpret_cast<trace_sdk::SpanBuilder*>(builder)->StartSpan();
    auto span_wrapper = new trace_sdk::Span(cpp_span);
    return reinterpret_cast<trace_sdk_Span*>(span_wrapper);
}

void tracer_end_span(trace_sdk_Span *span) {
    reinterpret_cast<trace_sdk::Span*>(span)->End();
}

void span_builder_set_span_kind(trace_sdk_SpanBuilder *span_builder, int span_kind)
{
    reinterpret_cast<trace_sdk::SpanBuilder*>(span_builder)->SetSpanKind(span_kind);
}
void span_builder_set_start_timestamp(trace_sdk_SpanBuilder *span_builder, int timestamp)
{
    reinterpret_cast<trace_sdk::SpanBuilder*>(span_builder)->SetStartTimestamp(timestamp);
}
void span_builder_add_attribute(trace_sdk_SpanBuilder *span_builder, const char *key, zval *value)
{
    // Convert zval to the appropriate C++ type
    opentelemetry::common::AttributeValue attr_value;

    if (Z_TYPE_P(value) == IS_STRING) {
        attr_value = Z_STRVAL_P(value);
    } else if (Z_TYPE_P(value) == IS_LONG) {
        attr_value = Z_LVAL_P(value);
    } else if (Z_TYPE_P(value) == IS_DOUBLE) {
        attr_value = Z_DVAL_P(value);
    } else if (Z_TYPE_P(value) == IS_TRUE) {
        attr_value = true;
    } else if (Z_TYPE_P(value) == IS_FALSE) {
        attr_value = false;
    } else {
        zend_throw_exception(NULL, "Unsupported attribute type.", 0);
        return;
    }

    // Store the key-value pair in the SpanBuilder object (C++)
    reinterpret_cast<trace_sdk::SpanBuilder*>(span_builder)->AddAttribute(key, attr_value);
}

//end extern C
}