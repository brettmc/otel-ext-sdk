#include "scope_class.h"
#include "../opentelemetry_sdk_arginfo.h"
#include <Zend/zend_exceptions.h>
#include "sdk_manager.h"

static zend_object_handlers scope_object_handlers;
zend_class_entry *scope_interface_ce;
zend_class_entry *scope_ce;

PHP_METHOD(OpenTelemetry_SDK_Trace_Scope, detach)
{
    //todo: check for double-detach?
    php_scope_object *intern = Z_SCOPE_OBJ_P(getThis());
    int r = scope_detach(intern->cpp_scope);
    RETURN_LONG(r);
}

// Free the C++ Scope when the PHP object is destroyed
void scope_free_obj(zend_object *object)
{
    //php_printf("(php)scope_free_obj\n");
    php_scope_object *intern = (php_scope_object *)((char *)(object) - XtOffsetOf(php_scope_object, std));

    if (intern->cpp_scope) {
        scope_destroy(intern->cpp_scope);
        intern->cpp_scope = NULL;
    }

    zend_object_std_dtor(&intern->std);  // Standard PHP object destructor
}

// Create a new PHP Span object
zend_object *scope_create_object(zend_class_entry *ce)
{
    php_scope_object *intern = (php_scope_object *)ecalloc(1, sizeof(php_scope_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &scope_object_handlers;

    return &intern->std;
}

// Initialize the Scope+ScopeInterface classes
void register_scope_class()
{
    scope_interface_ce = register_class_OpenTelemetry_SDK_Trace_ScopeInterface();
    scope_ce = register_class_OpenTelemetry_SDK_Trace_Scope(scope_interface_ce);
    scope_ce->create_object = scope_create_object;

    memcpy(&scope_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    scope_object_handlers.free_obj = scope_free_obj;
}
