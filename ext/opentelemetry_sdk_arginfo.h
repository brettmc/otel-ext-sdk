/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 756e136f9ac497ec52883add9a189e6f408795d6 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor_onStart, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, span, IS_OBJECT, 0)
	ZEND_ARG_TYPE_INFO(0, context, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor_onEnd, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, span, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor_forceFlush, 0, 0, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, cancellation, IS_OBJECT, 1, "null")
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor_shutdown arginfo_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor_forceFlush


ZEND_METHOD(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, __construct);
ZEND_METHOD(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, onStart);
ZEND_METHOD(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, onEnd);
ZEND_METHOD(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, forceFlush);
ZEND_METHOD(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, shutdown);


static const zend_function_entry class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor_methods[] = {
	ZEND_ME(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, __construct, arginfo_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, onStart, arginfo_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor_onStart, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, onEnd, arginfo_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor_onEnd, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, forceFlush, arginfo_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor_forceFlush, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor, shutdown, arginfo_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor_shutdown, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\Ext\\SDK\\Trace", "BatchSpanProcessor", class_OpenTelemetry_Ext_SDK_Trace_BatchSpanProcessor_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	return class_entry;
}
