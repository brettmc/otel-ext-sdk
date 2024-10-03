#include "php.h"
#include <Zend/zend_exceptions.h>
#include "batch_span_processor_class.h"
#include "../../opentelemetry_sdk_arginfo.h"

static zend_object_handlers batch_span_processor_object_handlers;
zend_class_entry *batch_span_processor_ce;
zend_class_entry *readable_span_interface_ce;
zend_class_entry *span_data_interface_ce;
zend_class_entry *span_context_interface_ce;

zend_object* batch_span_processor_create_object(zend_class_entry *class_type)
{
    //php_printf("(php)batch_span_processor_create_object\n");
    php_batch_span_processor_object *intern = (php_batch_span_processor_object *) ecalloc(1, sizeof(php_batch_span_processor_object));

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &batch_span_processor_object_handlers;

    return &intern->std;
}

// Free the C++ object when the PHP object is destroyed
void batch_span_processor_free_obj(zend_object *object)
{
    //php_printf("(php)batch_span_processor_free_obj\n");
    php_batch_span_processor_object *intern = (php_batch_span_processor_object *)((char*)(object) - XtOffsetOf(php_batch_span_processor_object, std));

    if (intern->cpp_batch_span_processor != NULL) {
        batch_span_processor_destroy(intern->cpp_batch_span_processor);
        intern->cpp_batch_span_processor = NULL;
    }

    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, __construct) {
    //php_printf("(php)BatchSpanProcessor::construct\n");
    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);

    intern->cpp_batch_span_processor = batch_span_processor_create();
}

PHP_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, __destruct) {
    //php_printf("(php)TracerProvider::destruct\n");
    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);

    if (intern->cpp_batch_span_processor != NULL) {
        batch_span_processor_destroy(intern->cpp_batch_span_processor);
        intern->cpp_batch_span_processor = NULL;
    } else {
        zend_throw_exception(NULL, "BatchSpanProcessor is not initialized.", 0);
    }
}

PHP_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, onStart) {
    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);
    batch_span_processor_on_start(intern->cpp_batch_span_processor);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, onEnd) {
    zval *span;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS(span, readable_span_interface_ce)
    ZEND_PARSE_PARAMETERS_END();
    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);

    batch_span_processor_on_end(intern->cpp_batch_span_processor, span);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, test) {
    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);
    batch_span_processor_test(intern->cpp_batch_span_processor);
}

PHP_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, shutdown) {
    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);
    RETURN_BOOL(batch_span_processor_shutdown(intern->cpp_batch_span_processor));
}

PHP_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, forceFlush) {
    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);
    RETURN_BOOL(batch_span_processor_force_flush(intern->cpp_batch_span_processor));
}

void register_batch_span_processor_class() {
    readable_span_interface_ce = register_class_OpenTelemetry_SDK_Trace_ReadableSpanInterface();
    span_data_interface_ce = register_class_OpenTelemetry_SDK_Trace_SpanDataInterface();
    span_context_interface_ce = register_class_OpenTelemetry_API_Trace_SpanContextInterface();

    zend_class_entry *span_processor_interface_ce = register_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface();
    batch_span_processor_ce = register_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor(span_processor_interface_ce);

    memcpy(&batch_span_processor_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    batch_span_processor_object_handlers.free_obj = batch_span_processor_free_obj;
}
