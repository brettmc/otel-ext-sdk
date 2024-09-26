#ifndef OTEL_EXT_SDK_CONTEXT_CLASS_H
#define OTEL_EXT_SDK_CONTEXT_CLASS_H

#include <php.h>
#include "opaque_types.h"

extern zend_class_entry *context_ce;
extern zend_class_entry *context_key_ce;

// Define the PHP internal object structure for Context
typedef struct _php_context_object {
    zend_object std;
    trace_sdk_Context *cpp_context;  // Pointer to C++ Context
} php_context_object;

typedef struct {
    zend_object std;
    zend_string *name;
} php_context_key_object;

#define Z_CONTEXT_OBJ_P(zv) ((php_context_object *)((char *)(Z_OBJ_P(zv)) - XtOffsetOf(php_context_object, std)))
#define Z_CONTEXT_KEY_OBJ_P(zv) ((php_context_key_object *)((char *)(Z_OBJ_P(zv)) - XtOffsetOf(php_context_key_object, std)))

void register_context_class();

#endif //OTEL_EXT_SDK_CONTEXT_CLASS_H
