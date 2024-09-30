#ifndef OTEL_EXT_SDK_SPAN_BUILDER_CLASS_H
#define OTEL_EXT_SDK_SPAN_BUILDER_CLASS_H

#include "php.h"
#include "../opaque_types.h"

typedef struct _php_span_builder_object {
    zend_object std;
    trace_sdk_SpanBuilder *cpp_span_builder;
} php_span_builder_object;

#define Z_SPAN_BUILDER_OBJ_P(zv) ((php_span_builder_object *)((char *)(Z_OBJ_P(zv)) - XtOffsetOf(php_span_builder_object, std)))

extern zend_class_entry *span_builder_ce;

void register_span_builder_class();

#endif //OTEL_EXT_SDK_SPAN_BUILDER_CLASS_H
