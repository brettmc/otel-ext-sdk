#include "php.h"
#include <Zend/zend_exceptions.h>
#include "ext/spl/spl_exceptions.h"
#include <Zend/zend_interfaces.h>
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

PHP_METHOD(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, __construct) {
    //php_printf("(php)BatchSpanProcessor::construct\n");
    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);

    intern->cpp_batch_span_processor = batch_span_processor_create();
}

PHP_METHOD(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, __destruct) {
    //php_printf("(php)TracerProvider::destruct\n");
    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);

    if (intern->cpp_batch_span_processor != NULL) {
        batch_span_processor_destroy(intern->cpp_batch_span_processor);
        intern->cpp_batch_span_processor = NULL;
    } else {
        zend_throw_exception(NULL, "BatchSpanProcessor is not initialized.", 0);
    }
}

PHP_METHOD(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, onStart) {
    //OnStart is a no-op in the C++ implementation, and also accepts an incorrect argument (SpanContext instead of Context)
    /*zval *span, *context;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        //Z_PARAM_OBJECT_OF_CLASS(span, readable_span_interface_ce)
        Z_PARAM_OBJECT(span)
        Z_PARAM_OBJECT(context)
    ZEND_PARSE_PARAMETERS_END();

    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);
    batch_span_processor_on_start(intern->cpp_batch_span_processor, span, context);*/
}

PHP_METHOD(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, onEnd) {
    zval *span;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT(span)
    ZEND_PARSE_PARAMETERS_END();

    //type-check $span implements ReadWriteSpanInterface
    const char *interface_name = "OpenTelemetry\\SDK\\Trace\\ReadWriteSpanInterface";
    zend_string *interface_str = zend_string_init(interface_name, strlen(interface_name), 0);
    zend_class_entry *interface_ce = zend_lookup_class(interface_str);
    zend_string_release(interface_str);

    if (!interface_ce) {
        //SDK not installed?
        zend_throw_exception(spl_ce_RuntimeException, "Interface not found", 0);
        return;
        //php_error_docref(NULL, E_WARNING, "Interface '%s' not found", interface_name);
    }

    // Use instanceof_function to check if the object implements the interface.
    if (!instanceof_function(Z_OBJCE_P(span), interface_ce)) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "$span does not implement ReadWriteSpanInterface", 0);
        return;
        //php_error_docref(NULL, E_WARNING, "Span does not implement Interface: '%s'", interface_name);
    }

    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);
    batch_span_processor_on_end(intern->cpp_batch_span_processor, span);
    //zval_ptr_dtor(span);
}

PHP_METHOD(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, shutdown) {
    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);
    RETURN_BOOL(batch_span_processor_shutdown(intern->cpp_batch_span_processor));
}

PHP_METHOD(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, forceFlush) {
    php_batch_span_processor_object *intern = Z_BATCH_SPAN_PROCESSOR_OBJ_P(ZEND_THIS);
    RETURN_BOOL(batch_span_processor_force_flush(intern->cpp_batch_span_processor));
}

void register_batch_span_processor_class() {
    batch_span_processor_ce = register_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor();

    memcpy(&batch_span_processor_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    batch_span_processor_object_handlers.free_obj = batch_span_processor_free_obj;
}
