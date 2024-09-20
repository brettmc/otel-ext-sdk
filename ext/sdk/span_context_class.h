#ifndef OTEL_EXT_SDK_SPAN_CONTEXT_CLASS_H
#define OTEL_EXT_SDK_SPAN_CONTEXT_CLASS_H

#include <php.h>
#include "opaque_types.h"

// Define the PHP internal object structure for Span
typedef struct _php_span_context_object {
    zend_object std;
    trace_sdk_SpanContext *cpp_span_context;  // Pointer to C++ SpanContext
} php_span_context_object;

#define Z_SPAN_CONTEXT_OBJ_P(zv) ((php_span_context_object *)((char *)(Z_OBJ_P(zv)) - XtOffsetOf(php_span_context_object, std)))

extern zend_class_entry *span_context_ce;

void register_span_context_class();

#endif //OTEL_EXT_SDK_SPAN_CONTEXT_CLASS_H
