#ifndef OTEL_EXT_SDK_SPAN_BUILDER_CLASS_H
#define OTEL_EXT_SDK_SPAN_BUILDER_CLASS_H

#include "php.h"

// Forward declaration of the C++ SpanBuilder and Span
typedef struct trace_sdk_SpanBuilder trace_sdk_SpanBuilder;
typedef struct trace_sdk_Span trace_sdk_Span;
typedef struct trace_sdk_Tracer trace_sdk_Tracer;

typedef struct _php_span_builder_object {
    zend_object std;
    trace_sdk_SpanBuilder *cpp_span_builder;
} php_span_builder_object;

#define Z_SPAN_BUILDER_OBJ_P(zv) ((php_span_builder_object *)((char *)(Z_OBJ_P(zv)) - XtOffsetOf(php_span_builder_object, std)))

extern zend_class_entry *span_builder_ce;

void register_span_builder_class();

#endif //OTEL_EXT_SDK_SPAN_BUILDER_CLASS_H
