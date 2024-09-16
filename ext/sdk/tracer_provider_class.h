#ifndef OPENTELEMETRY_SDK_TRACER_PROVIDER_CLASS_H
#define OPENTELEMETRY_SDK_TRACER_PROVIDER_CLASS_H

#include "php.h"
#include "sdk_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _php_tracer_provider_object {
    zend_object std;
    trace_sdk_TracerProvider *cpp_tracer_provider;
} php_tracer_provider_object;

zend_object* tracer_provider_create_object(zend_class_entry *class_type);
void tracer_provider_free_obj(zend_object *object);

void register_tracer_provider_class();

#ifdef __cplusplus
}
#endif
#endif //OPENTELEMETRY_SDK_TRACER_PROVIDER_CLASS_H