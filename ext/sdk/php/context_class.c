#include "context_class.h"
#include "scope_class.h"
#include "../../opentelemetry_sdk_arginfo.h"
#include <Zend/zend_exceptions.h>
#include "../sdk_manager.h"
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
        context_destroy(intern->cpp_context);
        //intern->cpp_context = NULL;
    }

    zend_object_std_dtor(&intern->std);  // Standard PHP object destructor
}

// Create a new PHP Context object
zend_object *context_create_object(zend_class_entry *ce)
{
    php_context_object *intern = (php_context_object *)ecalloc(1, sizeof(php_context_object));

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
    obj->name = zend_string_copy(name);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_ContextKey, __destruct)
{
    //php_printf("ContextKey::__destruct\n");
}

PHP_METHOD(OpenTelemetry_SDK_Trace_ContextKey, name)
{
    php_context_key_object *obj = Z_CONTEXT_KEY_OBJ_P(getThis());
    RETURN_STRING(ZSTR_VAL(obj->name));
}

static void context_key_free_obj(zend_object *object) {
    //php_printf("context_key_free_obj\n");
    php_context_key_object *intern = (php_context_key_object *)((char *)object - XtOffsetOf(php_context_key_object, std));
    //php_printf("(context_key_free_obj)name refcount: %d\n", GC_REFCOUNT(intern->name));
    if (intern->name) {
        zend_string_release(intern->name);
        intern->name = NULL;
    }
    zend_object_std_dtor(&intern->std);
}

static zend_object *context_key_create_object(zend_class_entry *class_type) {
    //php_printf("context_key_create_object\n");
    php_context_key_object *intern = (php_context_key_object *)ecalloc(1, sizeof(php_context_key_object) + zend_object_properties_size(class_type) + 16);
    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &context_key_object_handlers;
    //php_printf("(context_key_create_object)refcount: %d\n", GC_REFCOUNT(&obj->std));
    return &intern->std;
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
    //php_printf("(php)Context::activate\n");
    object_init_ex(return_value, scope_ce);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Context, with)
{
    zval *zv_key;
    zval *value;
    ZEND_PARSE_PARAMETERS_START(2, 2) // Expecting exactly 2 parameters
        Z_PARAM_OBJECT_OF_CLASS(zv_key, context_key_interface_ce) // First parameter: object
        Z_PARAM_ZVAL(value) // Second parameter: mixed type
    ZEND_PARSE_PARAMETERS_END();

    php_context_key_object *context_key_obj = Z_CONTEXT_KEY_OBJ_P(zv_key);
    char *key = ZSTR_VAL(context_key_obj->name);

    //return a new context with extra value applied
    php_context_object *internal = Z_CONTEXT_OBJ_P(getThis());
    trace_sdk_Context *new_context = context_set_value(internal->cpp_context, key, value);

    object_init_ex(return_value, context_ce);
    php_context_object *context_intern = Z_CONTEXT_OBJ_P(return_value);
    context_intern->cpp_context = new_context;
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Context, get)
{
    php_context_object *internal = Z_CONTEXT_OBJ_P(getThis());
    zval *zv_key;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS(zv_key, context_key_interface_ce)
    ZEND_PARSE_PARAMETERS_END();

    php_context_key_object *context_key_obj = Z_CONTEXT_KEY_OBJ_P(zv_key);
    char *key = ZSTR_VAL(context_key_obj->name);

    zval value = context_get_value(internal->cpp_context, key);
    RETURN_ZVAL(&value, 1, 0);
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
