#ifndef OPENTELEMETRY_SDK_BATCH_SPAN_PROCESSOR_CLASS_H
#define OPENTELEMETRY_SDK_BATCH_SPAN_PROCESSOR_CLASS_H

#include "php.h"
#include "../sdk_manager.h"
#include "../opaque_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _php_batch_span_processor_object {
    zend_object std;
    trace_sdk_BatchSpanProcessor *cpp_batch_span_processor;
} php_batch_span_processor_object;

#define Z_BATCH_SPAN_PROCESSOR_OBJ_P(zv) ((php_batch_span_processor_object *)((char *)(Z_OBJ_P(zv)) - XtOffsetOf(php_batch_span_processor_object, std)))

extern zend_class_entry *readable_span_interface_ce;
extern zend_class_entry *span_data_interface_ce;
extern zend_class_entry *span_context_interface_ce;

zend_object* batch_span_processor_create_object(zend_class_entry *class_type);
void batch_span_processor_free_obj(zend_object *object);

void register_batch_span_processor_class();

#ifdef __cplusplus
}
#endif
#endif //OPENTELEMETRY_SDK_BATCH_SPAN_PROCESSOR_CLASS_H