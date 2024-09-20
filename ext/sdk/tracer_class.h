#ifndef OPENTELEMETRY_SDK_TRACER_CLASS_H
#define OPENTELEMETRY_SDK_TRACER_CLASS_H

#include "php.h"
#include "opaque_types.h"
#include "sdk_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

extern zend_class_entry *tracer_ce;

typedef struct _php_tracer_object {
    zend_object std;
    trace_sdk_Tracer *cpp_tracer;
} php_tracer_object;

#define Z_TRACER_OBJ_P(zv) ((php_tracer_object *)((char *)(Z_OBJ_P(zv)) - XtOffsetOf(php_tracer_object, std)))

void register_tracer_class();

#ifdef __cplusplus
}
#endif

#endif //OPENTELEMETRY_SDK_TRACER_CLASS_H
