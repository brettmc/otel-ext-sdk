#ifdef __cplusplus
extern "C" {
#endif

#include "php.h"
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>
#include "tracer_class.h"
#include "span_builder_class.h"
#include "tracer_manager.h"
#include "../opentelemetry_sdk_arginfo.h"

static zend_object_handlers tracer_object_handlers;
zend_class_entry *tracer_ce;

zend_object* tracer_create_object(zend_class_entry *class_type)
{
    //php_printf("(php)tracer_create_object\n");
    php_tracer_object *intern = (php_tracer_object *) ecalloc(1, sizeof(php_tracer_object) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &tracer_object_handlers;

    return &intern->std;
}

// Free the C++ Tracer object when the PHP object is destroyed
void tracer_free_obj(zend_object *object)
{
    //php_printf("(php)tracer_free_obj\n");
    php_tracer_object *intern = (php_tracer_object *)((char*)(object) - XtOffsetOf(php_tracer_object, std));

    if (intern->cpp_tracer != NULL) {
        tracer_destroy(intern->cpp_tracer);
        intern->cpp_tracer = NULL;
    }

    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Tracer, __construct) {
    //php_printf("(php)Tracer::__construct\n");
    php_tracer_object *intern;
    intern = (php_tracer_object *) Z_OBJ_P(ZEND_THIS);

    intern->cpp_tracer = tracer_create();
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Tracer, spanBuilder) {
    char *span_name;
    size_t span_name_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(span_name, span_name_len)
    ZEND_PARSE_PARAMETERS_END();

    php_tracer_object *tracer_intern = Z_TRACER_OBJ_P(getThis());
    if (!tracer_intern->cpp_tracer) {
        zend_throw_exception(NULL, "Tracer is not initialized.", 0);
        RETURN_NULL();
    }

    trace_sdk_SpanBuilder *cpp_span_builder = tracer_create_span_builder(tracer_intern->cpp_tracer, span_name);

    // Create a new SpanBuilder object
    object_init_ex(return_value, span_builder_ce);

    php_span_builder_object *intern = Z_SPAN_BUILDER_OBJ_P(return_value);
    intern->cpp_span_builder = cpp_span_builder;
}

PHP_METHOD(OpenTelemetry_SDK_Trace_Tracer, doSomething) {
    //php_printf("(php)Tracer::doSomething\n");
    php_tracer_object *intern;
    intern = (php_tracer_object *) Z_OBJ_P(ZEND_THIS);
    tracer_do_something(intern->cpp_tracer);
}

void register_tracer_class() {
    tracer_ce = register_class_OpenTelemetry_SDK_Trace_Tracer();
    tracer_ce->create_object = tracer_create_object;

    memcpy(&tracer_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    tracer_object_handlers.free_obj = tracer_free_obj;
}

#ifdef __cplusplus
}
#endif