#include "span_class.h"
#include "scope_class.h"
#include "span_context_class.h"
#include "../opentelemetry_sdk_arginfo.h"
#include <Zend/zend_exceptions.h>
#include "sdk_manager.h"

static zend_object_handlers span_object_handlers;
zend_class_entry *span_ce;

PHP_METHOD(OpenTelemetry_SDK_Trace_Span, end)
{
    //todo end timestamp
    php_span_object *intern = Z_SPAN_OBJ_P(getThis());

    if (!intern->cpp_span) {
        zend_throw_exception(NULL,"Span is not initialized.", 0);
        return;
    }

    span_end_span(intern->cpp_span);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Span, updateName)
{
    php_span_object *intern = Z_SPAN_OBJ_P(getThis());


    // Variables to hold the parameters
    zend_string *name;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(name)
    ZEND_PARSE_PARAMETERS_END();

    span_update_name(intern->cpp_span, ZSTR_VAL(name));

    RETURN_ZVAL(getThis(), 1, 0);
}


PHP_METHOD(OpenTelemetry_SDK_Trace_Span, setStatus)
{
    php_span_object *intern = Z_SPAN_OBJ_P(getThis());

    // Variables to hold the parameters
    zend_string *status_code;
    zend_string *description = NULL;

    // Parse the parameters: status_code (required) and description (optional, nullable)
    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_STR(status_code)               // The status code string (required)
        Z_PARAM_OPTIONAL
        Z_PARAM_STR_OR_NULL(description)       // The optional description string (nullable)
    ZEND_PARSE_PARAMETERS_END();

    if (description) {
        span_set_status(intern->cpp_span, ZSTR_VAL(status_code), ZSTR_VAL(description));
    } else {
        span_set_status(intern->cpp_span, ZSTR_VAL(status_code), NULL);
    }

    RETURN_ZVAL(getThis(), 1, 0);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Span, activate) {
    php_span_object *span_intern = Z_SPAN_OBJ_P(getThis());
    if (!span_intern->cpp_span) {
        zend_throw_exception(NULL, "Span is not initialized.", 0);
        RETURN_NULL();
    }
    trace_sdk_Scope *cpp_scope = span_activate(span_intern->cpp_span);
    object_init_ex(return_value, scope_ce);
    php_scope_object *intern = Z_SCOPE_OBJ_P(return_value);
    intern->cpp_scope = cpp_scope;
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Span, getContext) {
    //php_printf("Span::getContext\n");
    php_span_object *span_intern = Z_SPAN_OBJ_P(getThis());
    if (!span_intern->cpp_span) {
        zend_throw_exception(NULL, "Span is not initialized.", 0);
        RETURN_NULL();
    }
    trace_sdk_SpanContext *cpp_span_context = span_get_context(span_intern->cpp_span);
    //php_printf("Span::getContext(end)\n");

    object_init_ex(return_value, span_context_ce);
    php_span_context_object *span_context_intern = Z_SPAN_CONTEXT_OBJ_P(return_value);
    span_context_intern->cpp_span_context = cpp_span_context;
}

// Free the C++ Span when the PHP object is destroyed
void span_free_obj(zend_object *object)
{
//    php_printf("span_free_obj\n");
    php_span_object *intern = (php_span_object *)((char *)(object) - XtOffsetOf(php_span_object, std));

    if (intern->cpp_span) {
        span_destroy(intern->cpp_span);  // Destroy the C++ Span object
        intern->cpp_span = NULL;
    }

    zend_object_std_dtor(&intern->std);  // Standard PHP object destructor
}

// Create a new PHP Span object
zend_object *span_create_object(zend_class_entry *ce)
{
    php_span_object *intern = (php_span_object *)ecalloc(1, sizeof(php_span_object) + zend_object_properties_size(ce) - 20);

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &span_object_handlers;

    return &intern->std;
}

// Initialize the Span+SpanInterface classes
void register_span_class()
{
    zend_class_entry *span_interface_ce = register_class_OpenTelemetry_SDK_Trace_SpanInterface();
    span_ce = register_class_OpenTelemetry_SDK_Trace_Span(span_interface_ce);
    span_ce->create_object = span_create_object;

    memcpy(&span_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    span_object_handlers.free_obj = span_free_obj;
}
