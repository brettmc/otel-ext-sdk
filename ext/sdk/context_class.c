#include "context_class.h"
#include "scope_class.h"
#include "../opentelemetry_sdk_arginfo.h"
#include <Zend/zend_exceptions.h>
#include "sdk_manager.h"
#include "zend_types.h"

static zend_object_handlers context_object_handlers;
static zend_object_handlers context_key_object_handlers;
zend_class_entry *context_interface_ce;
zend_class_entry *context_ce;
zend_class_entry *context_key_interface_ce;
zend_class_entry *context_key_ce;

// Free the C++ Context when the PHP object is destroyed
void context_free_obj(zend_object *object)
{
    php_context_object *intern = (php_context_object *)((char *)(object) - XtOffsetOf(php_context_object, std));

    if (intern->cpp_context) {
        intern->cpp_context = NULL;
    }

    zend_object_std_dtor(&intern->std);  // Standard PHP object destructor
}

// Create a new PHP Context object
zend_object *context_create_object(zend_class_entry *ce)
{
    php_context_object *intern = (php_context_object *)ecalloc(1, sizeof(php_context_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &context_object_handlers;

    return &intern->std;
}

PHP_METHOD(OpenTelemetry_SDK_Trace_ContextKey, __construct)
{
    //php_printf("ContextKey::__construct\n");
    php_context_key_object *obj = Z_CONTEXT_KEY_OBJ_P(getThis());
    //php_printf("(ContextKey::__construct)refcount: %d\n", GC_REFCOUNT(&obj->std));
    zend_string *name;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &name) == FAILURE) {
        return;
    }
    obj->name = name;
}

PHP_METHOD(OpenTelemetry_SDK_Trace_ContextKey, __destruct)
{
    php_printf("ContextKey::__destruct\n");
}

PHP_METHOD(OpenTelemetry_SDK_Trace_ContextKey, name)
{
    php_context_key_object *obj = Z_CONTEXT_KEY_OBJ_P(getThis());
    //php_printf("refcount: %d\n", GC_REFCOUNT(&obj->std));
    RETURN_STRING(ZSTR_VAL(obj->name));
}

static void context_key_free_obj(zend_object *object) {
    //php_printf("context_key_free_obj\n");
    php_context_key_object *intern = (php_context_key_object *)((char *)object - XtOffsetOf(php_context_key_object, std));
    zend_string_release(intern->name);
    intern->name = NULL;
    zend_object_std_dtor(&intern->std);
    //efree(intern);
}

static zend_object *context_key_create_object(zend_class_entry *class_type) {
    //php_printf("context_key_create_object\n");
    php_context_key_object *obj = (php_context_key_object *)ecalloc(1, sizeof(php_context_key_object) + zend_object_properties_size(class_type));
    zend_object_std_init(&obj->std, class_type);
    object_properties_init(&obj->std, class_type);
    obj->std.handlers = &context_key_object_handlers;
    //php_printf("(context_key_create_object)refcount: %d\n", GC_REFCOUNT(&obj->std));
    return &obj->std;
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Context, getCurrent)
{
    trace_sdk_Context *cpp_context = context_get_current();
    object_init_ex(return_value, context_ce);
    php_context_object *context_intern = Z_CONTEXT_OBJ_P(return_value);
    context_intern->cpp_context = cpp_context;
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Context, activate)
{
    php_printf("(php)Context::activate\n");
    object_init_ex(return_value, scope_ce);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Context, with)
{
    zval *key;
    zval *value;
    ZEND_PARSE_PARAMETERS_START(2, 2) // Expecting exactly 2 parameters
        Z_PARAM_OBJECT_OF_CLASS(key, context_key_interface_ce) // First parameter: object
        Z_PARAM_ZVAL(value) // Second parameter: mixed type
    ZEND_PARSE_PARAMETERS_END();

    zval retval; // Variable to hold the return value
    zval method_name;
    ZVAL_STRING(&method_name, "name");
    char *key_str;

    // Call the method
    if (call_user_function(EG(function_table), key, &method_name, &retval, 0, NULL) == SUCCESS) {
        key_str = ZSTR_VAL(Z_STR(retval));
    } else {
        php_printf("Failed to call method 'name'.\n");
    }

    //php_printf("The object is an instance of class: %s\n", ZSTR_VAL(ce->name));
    //return a new context with extra value applied
    php_context_object *internal = Z_CONTEXT_OBJ_P(getThis());
    trace_sdk_Context *new_context = context_set_value(internal->cpp_context, key_str, value);

    object_init_ex(return_value, context_ce);
    php_context_object *context_intern = Z_CONTEXT_OBJ_P(return_value);
    context_intern->cpp_context = new_context;
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Context, get)
{
    php_context_object *internal = Z_CONTEXT_OBJ_P(getThis());
    zval *key;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS(key, context_key_interface_ce)
    ZEND_PARSE_PARAMETERS_END();

    char *key_str;
    zval retval; // Variable to hold the return value
    zval method_name;
    ZVAL_STRING(&method_name, "name");

    // Call the method
    if (call_user_function(EG(function_table), key, &method_name, &retval, 0, NULL) == SUCCESS) {
        key_str = ZSTR_VAL(Z_STR(retval));
    } else {
        php_printf("Failed to call method 'name'.\n");
    }
    zval *item = context_get_value(internal->cpp_context, key_str);
    RETURN_ZVAL(item, 0, 0);
}

// Initialize the classes
void register_context_class()
{
    //context key
    context_key_interface_ce = register_class_OpenTelemetry_SDK_Trace_ContextKeyInterface();
    context_key_ce = register_class_OpenTelemetry_SDK_Trace_ContextKey(context_key_interface_ce);
    context_key_ce->create_object = context_key_create_object;
    memcpy(&context_key_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    context_key_object_handlers.free_obj = context_key_free_obj;

    //context
    context_interface_ce = register_class_OpenTelemetry_SDK_Trace_ContextInterface();
    context_ce = register_class_OpenTelemetry_SDK_Trace_Context(context_interface_ce);
    context_ce->create_object = context_create_object;
    memcpy(&context_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    context_object_handlers.free_obj = context_free_obj;
}
