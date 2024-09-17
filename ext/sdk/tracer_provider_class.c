#include "php.h"
#include <Zend/zend_exceptions.h>
#include "tracer_class.h"
#include "tracer_provider_class.h"
#include "../opentelemetry_sdk_arginfo.h"

static zend_object_handlers tracer_provider_object_handlers;

zend_object* tracer_provider_create_object(zend_class_entry *class_type)
{
    //php_printf("(php)tracer_provider_create_object\n");
    php_tracer_provider_object *intern = (php_tracer_provider_object *) ecalloc(1, sizeof(php_tracer_provider_object) + zend_object_properties_size(class_type));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &tracer_provider_object_handlers;

    return &intern->std;
}

// Free the C++ TracerProvider object when the PHP object is destroyed
void tracer_provider_free_obj(zend_object *object)
{
    //php_printf("(php)tracer_provider_free_obj\n");
    php_tracer_provider_object *intern = (php_tracer_provider_object *)((char*)(object) - XtOffsetOf(php_tracer_provider_object, std));

    if (intern->cpp_tracer_provider != NULL) {
        tracer_provider_destroy(intern->cpp_tracer_provider);
        intern->cpp_tracer_provider = NULL;
    }

    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_TracerProvider, __construct) {
    //php_printf("(php)TracerProvider::construct\n");
    php_tracer_provider_object *intern;
    intern = (php_tracer_provider_object *) Z_OBJ_P(ZEND_THIS);

    intern->cpp_tracer_provider = tracer_provider_create();
}

PHP_METHOD(OpenTelemetry_SDK_Trace_TracerProvider, __destruct) {
    //php_printf("(php)TracerProvider::destruct\n");
    php_tracer_provider_object *intern;
    intern = (php_tracer_provider_object *) Z_OBJ_P(ZEND_THIS);

    if (intern->cpp_tracer_provider != NULL) {
        tracer_provider_destroy(intern->cpp_tracer_provider);
        intern->cpp_tracer_provider = NULL;
    } else {
        zend_throw_exception(NULL, "TracerProvider is not initialized.", 0);
    }
}
PHP_METHOD(OpenTelemetry_SDK_Trace_TracerProvider, getTracer) {
    //php_printf("(php)TracerProvider::getTracer\n");

    char *name;
    size_t name_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(name, name_len)
    ZEND_PARSE_PARAMETERS_END();

    php_tracer_provider_object *intern;
    intern = (php_tracer_provider_object *) Z_OBJ_P(ZEND_THIS);
    trace_sdk_Tracer *cpp_tracer = tracer_provider_get_tracer(intern->cpp_tracer_provider);
    //php_printf("(php)got a c++ tracer\n");
    object_init_ex(return_value, tracer_ce);
    php_tracer_object *tracer_intern = (php_tracer_object *) Z_OBJ_P(return_value);
    tracer_intern->cpp_tracer = cpp_tracer;
}

void register_tracer_provider_class() {
    zend_class_entry *ce;
    ce = register_class_OpenTelemetry_SDK_Trace_TracerProvider();
    ce->create_object = tracer_provider_create_object;

    memcpy(&tracer_provider_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    tracer_provider_object_handlers.free_obj = tracer_provider_free_obj;
}
