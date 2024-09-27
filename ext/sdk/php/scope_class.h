#ifndef OTEL_EXT_SDK_SCOPE_CLASS_H
#define OTEL_EXT_SDK_SCOPE_CLASS_H

#include <php.h>
#include "../opaque_types.h"

extern zend_class_entry *scope_ce;

// Define the PHP internal object structure for Scope
typedef struct _php_scope_object {
    zend_object std;
    trace_sdk_Scope *cpp_scope;  // Pointer to C++ Scope
} php_scope_object;

#define Z_SCOPE_OBJ_P(zv) ((php_scope_object *)((char *)(Z_OBJ_P(zv)) - XtOffsetOf(php_scope_object, std)))

void register_scope_class();

#endif //OTEL_EXT_SDK_SCOPE_CLASS_H
