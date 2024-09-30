#include "span_context_class.h"
#include "../../opentelemetry_sdk_arginfo.h"
#include <Zend/zend_exceptions.h>
#include "../sdk_manager.h"

static zend_object_handlers span_context_object_handlers;
zend_class_entry *span_context_ce;

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanContext, getTraceId)
{
    php_span_context_object *intern = Z_SPAN_CONTEXT_OBJ_P(getThis());
    if (!intern->cpp_span_context) {
        zend_throw_exception(NULL,"SpanContext is not initialized.", 0);
        return;
    }

    const char *trace_id = span_context_get_trace_id(intern->cpp_span_context);

    RETURN_STRING(trace_id);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanContext, getSpanId)
{
    php_span_context_object *intern = Z_SPAN_CONTEXT_OBJ_P(getThis());

    if (!intern->cpp_span_context) {
        zend_throw_exception(NULL,"SpanContext is not initialized.", 0);
        return;
    }

    RETURN_STRING(span_context_get_span_id(intern->cpp_span_context));
}

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanContext, getTraceFlags)
{
    php_span_context_object *intern = Z_SPAN_CONTEXT_OBJ_P(getThis());

    if (!intern->cpp_span_context) {
        zend_throw_exception(NULL,"SpanContext is not initialized.", 0);
        return;
    }

    RETURN_LONG(span_context_get_trace_flags(intern->cpp_span_context));
}

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanContext, isRemote)
{
    php_span_context_object *intern = Z_SPAN_CONTEXT_OBJ_P(getThis());

    if (!intern->cpp_span_context) {
        zend_throw_exception(NULL,"SpanContext is not initialized.", 0);
        return;
    }
    RETURN_BOOL(span_context_get_is_remote(intern->cpp_span_context));
}

PHP_METHOD(OpenTelemetry_SDK_Trace_SpanContext, isSampled)
{
    php_span_context_object *intern = Z_SPAN_CONTEXT_OBJ_P(getThis());

    if (!intern->cpp_span_context) {
        zend_throw_exception(NULL,"SpanContext is not initialized.", 0);
        return;
    }
    RETURN_BOOL(span_context_get_is_sampled(intern->cpp_span_context));
}

// Free the C++ Span when the PHP object is destroyed
void span_context_free_obj(zend_object *object)
{
    php_span_context_object *intern = (php_span_context_object *)((char *)(object) - XtOffsetOf(php_span_context_object, std));

    if (intern->cpp_span_context) {
        span_context_destroy(intern->cpp_span_context);  // Destroy the C++ Span object
        intern->cpp_span_context = NULL;
    }

    zend_object_std_dtor(&intern->std);  // Standard PHP object destructor
}

// Create a new PHP Span object
zend_object *span_context_create_object(zend_class_entry *ce)
{
    php_span_context_object *intern = (php_span_context_object *)ecalloc(1, sizeof(php_span_context_object));

    zend_object_std_init(&intern->std, ce);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &span_context_object_handlers;

    return &intern->std;
}

// Initialize the SpanContext+SpanContextInterface classes
void register_span_context_class()
{
    zend_class_entry *span_context_interface_ce = register_class_OpenTelemetry_SDK_Trace_SpanContextInterface();
    span_context_ce = register_class_OpenTelemetry_SDK_Trace_SpanContext(span_context_interface_ce);
    span_context_ce->create_object = span_context_create_object;

    memcpy(&span_context_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    span_context_object_handlers.free_obj = span_context_free_obj;
}
