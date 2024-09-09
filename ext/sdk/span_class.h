#ifndef OTEL_EXT_SDK_SPAN_CLASS_H
#define OTEL_EXT_SDK_SPAN_CLASS_H

#include <php.h>

// Forward declaration of the C++ Span
typedef struct trace_sdk_Span trace_sdk_Span;

// Define the PHP internal object structure for Span
typedef struct _php_span_object {
    zend_object std;
    trace_sdk_Span *cpp_span;  // Pointer to C++ Span
} php_span_object;

#define Z_SPAN_OBJ_P(zv) ((php_span_object *)((char *)(Z_OBJ_P(zv)) - XtOffsetOf(php_span_object, std)))

extern zend_class_entry *span_ce;

void register_span_class();

#endif //OTEL_EXT_SDK_SPAN_CLASS_H
