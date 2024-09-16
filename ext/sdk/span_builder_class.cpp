#ifdef __cplusplus
extern "C" {
#endif

#include "php.h"
#include <Zend/zend_exceptions.h>
#include "span_class.h"
#include "sdk_manager.h"
#include "span_builder_class.h"
#include "../opentelemetry_sdk_arginfo.h"

zend_class_entry *span_builder_ce;
zend_object_handlers span_builder_object_handlers;

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, setSpanKind)
{
    zend_long span_kind;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(span_kind)
    ZEND_PARSE_PARAMETERS_END();

    php_span_builder_object *intern = Z_SPAN_BUILDER_OBJ_P(ZEND_THIS);

    span_builder_set_span_kind(intern->cpp_span_builder, span_kind);

    RETURN_ZVAL(getThis(), 1, 0);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, setAttribute)
{
    php_span_builder_object *intern = Z_SPAN_BUILDER_OBJ_P(getThis());
    if (!intern->cpp_span_builder) {
        zend_throw_exception(NULL, "SpanBuilder is not initialized.", 0);
        return;
    }
    char *key;
    size_t key_len;
    zval *value;

    // Parse the parameters passed from PHP
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(key, key_len)
        Z_PARAM_ZVAL(value)
    ZEND_PARSE_PARAMETERS_END();

    span_builder_add_attribute(intern->cpp_span_builder, key, value);

    // Return the current object (self)
    RETURN_ZVAL(getThis(), 1, 0);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, setParent)
{
    php_printf("todo: implement setParent\n");
    RETURN_ZVAL(getThis(), 1, 0);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, addLink)
{
    php_printf("todo: implement addLink\n");
    RETURN_ZVAL(getThis(), 1, 0);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, setStartTimestamp)
{
    php_span_builder_object *intern = Z_SPAN_BUILDER_OBJ_P(getThis());

    zend_long timestamp;

    // Parse the timestamp parameter (expecting an integer)
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &timestamp) == FAILURE) {
        RETURN_NULL();
    }

    // Ensure the timestamp is valid (positive)
    if (timestamp <= 0) {
        zend_throw_exception(NULL, "Invalid timestamp. Must be a positive integer.", 0);
        RETURN_NULL();
    }

    // Set the start timestamp in the C++ SpanBuilder
    span_builder_set_start_timestamp(intern->cpp_span_builder, timestamp);

    RETURN_ZVAL(getThis(), 1, 0);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, setAttributes)
{
    php_span_builder_object *intern = Z_SPAN_BUILDER_OBJ_P(getThis());

    zval *attributes;

    // Parse the attributes parameter, expecting an iterable (array or traversable)
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &attributes) == FAILURE) {
        //todo throw?
        RETURN_NULL();
    }

    zend_string *key;
    zval *value;

    ZEND_HASH_FOREACH_STR_KEY_VAL(Z_ARRVAL_P(attributes), key, value) {
        if (key) {
            const char *attr_key = ZSTR_VAL(key);
            //todo drop non-simple types here?
            span_builder_add_attribute(intern->cpp_span_builder, attr_key, value);
        }
    } ZEND_HASH_FOREACH_END();

    RETURN_ZVAL(getThis(), 1, 0);  // Return $this for method chaining
}


PHP_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, startSpan)
{
    //php_printf("SpanBuilder::startSpan\n");
    php_span_builder_object *intern = Z_SPAN_BUILDER_OBJ_P(getThis());

    if (!intern->cpp_span_builder) {
        zend_throw_exception(NULL, "SpanBuilder is not initialized.", 0);
        RETURN_NULL();
    }

    // Start the span (C++ span)
    trace_sdk_Span *cpp_span = span_builder_start_span(intern->cpp_span_builder);

    if (!cpp_span) {
        zend_throw_exception(NULL, "Failed to start span.", 0);
        RETURN_NULL();
    }

    // Create a new PHP Span object
    object_init_ex(return_value, span_ce);

    // Get the internal PHP Span object
    php_span_object *span_intern = Z_SPAN_OBJ_P(return_value);

    // Store the C++ Span in the PHP Span object
    span_intern->cpp_span = cpp_span;
}

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, test)
{
    php_span_builder_object *intern = Z_SPAN_BUILDER_OBJ_P(getThis());
    //php_printf("SpanBuilder::test (%s) (%d)\n", intern->span_name, intern->span_kind);
}

// Object handlers for SpanBuilder
void span_builder_free_obj(zend_object *object)
{
    php_span_builder_object *intern = (php_span_builder_object *)((char *)(object) - XtOffsetOf(php_span_builder_object, std));

    if (intern->cpp_span_builder) {
        span_builder_destroy(intern->cpp_span_builder);
        intern->cpp_span_builder = NULL;
    }

    zend_object_std_dtor(&intern->std);
}

zend_object *span_builder_create_object(zend_class_entry *ce)
{
    php_span_builder_object *intern = (php_span_builder_object *)ecalloc(1, sizeof(php_span_builder_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &std_object_handlers;

    return &intern->std;
}

void register_span_builder_class() {
    span_builder_ce = register_class_OpenTelemetry_SDK_Trace_SpanBuilder();
    span_builder_ce->create_object = span_builder_create_object;

    // Copy standard object handlers, and replace the free handler with our custom free function
    memcpy(&span_builder_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    span_builder_object_handlers.offset = XtOffsetOf(php_span_builder_object, std);
    span_builder_object_handlers.free_obj = span_builder_free_obj;
}

#ifdef __cplusplus
}
#endif