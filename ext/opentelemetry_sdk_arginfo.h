/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: a987a0d5a0e3e2e4c12496a5cd8cdb8b27b35d38 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_Context_ContextInterface_getCurrent, 0, 0, OpenTelemetry\\Context\\ContextInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_Context_ContextInterface_activate, 0, 0, OpenTelemetry\\Context\\ScopeInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_Context_ContextInterface_with, 0, 2, OpenTelemetry\\Context\\ContextInterface, 0)
	ZEND_ARG_OBJ_INFO(0, key, OpenTelemetry\\Context\\ContextKeyInterface, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_Context_ContextInterface_get, 0, 1, IS_MIXED, 0)
	ZEND_ARG_OBJ_INFO(0, key, OpenTelemetry\\Context\\ContextKeyInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_API_Trace_TraceStateInterface___toString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getTraceId arginfo_class_OpenTelemetry_API_Trace_TraceStateInterface___toString

#define arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getSpanId arginfo_class_OpenTelemetry_API_Trace_TraceStateInterface___toString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getTraceFlags, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getTraceState, 0, 0, OpenTelemetry\\API\\Trace\\TraceStateInterface, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Common_Attribute_AttributesInterface_has, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Common_Attribute_AttributesInterface_get, 0, 1, IS_MIXED, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Common_Attribute_AttributesInterface_getDroppedAttributesCount arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getTraceFlags

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Common_Attribute_AttributesInterface_toArray, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Common_Future_CancellationInterface_subscribe, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, callback, Closure, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Common_Future_CancellationInterface_unsubscribe, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface_getName arginfo_class_OpenTelemetry_API_Trace_TraceStateInterface___toString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface_getVersion, 0, 0, IS_STRING, 1)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface_getSchemaUrl arginfo_class_OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface_getVersion

#define arginfo_class_OpenTelemetry_SDK_Trace_StatusDataInterface_getCode arginfo_class_OpenTelemetry_API_Trace_TraceStateInterface___toString

#define arginfo_class_OpenTelemetry_SDK_Trace_StatusDataInterface_getDescription arginfo_class_OpenTelemetry_API_Trace_TraceStateInterface___toString

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getName arginfo_class_OpenTelemetry_API_Trace_TraceStateInterface___toString

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getKind arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getTraceFlags

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getContext, 0, 0, OpenTelemetry\\API\\Trace\\SpanContextInterface, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getParentContext arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getContext

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getStatus, 0, 0, OpenTelemetry\\SDK\\Trace\\StatusDataInterface, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getStartEpochNanos arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getTraceFlags

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getAttributes, 0, 0, OpenTelemetry\\SDK\\Common\\Attribute\\AttributesInterface, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getEndEpochNanos arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getTraceFlags

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getInstrumentationScope, 0, 0, OpenTelemetry\\SDK\\Common\\Instrumentation\\InstrumentationScopeInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getResource, 0, 0, IS_OBJECT, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Trace_ReadableSpanInterface_getName arginfo_class_OpenTelemetry_API_Trace_TraceStateInterface___toString

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_ReadableSpanInterface_toSpanData, 0, 0, OpenTelemetry\\SDK\\Trace\\SpanDataInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_onStart, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, span, OpenTelemetry\\SDK\\Trace\\ReadWriteSpanInterface, 0)
	ZEND_ARG_OBJ_INFO(0, parentContext, OpenTelemetry\\Context\\ContextInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_onEnd, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, span, OpenTelemetry\\SDK\\Trace\\ReadableSpanInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_forceFlush, 0, 0, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, cancellation, OpenTelemetry\\SDK\\Common\\Future\\CancellationInterface, 1, "null")
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_shutdown arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_forceFlush

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor_onStart arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_onStart

#define arginfo_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor_onEnd arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_onEnd

#define arginfo_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor_forceFlush arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_forceFlush

#define arginfo_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor_shutdown arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_forceFlush


ZEND_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, __construct);
ZEND_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, onStart);
ZEND_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, onEnd);
ZEND_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, forceFlush);
ZEND_METHOD(OpenTelemetry_SDK_Trace_BatchSpanProcessor, shutdown);


static const zend_function_entry class_OpenTelemetry_Context_ContextInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_Context_ContextInterface, getCurrent, arginfo_class_OpenTelemetry_Context_ContextInterface_getCurrent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_Context_ContextInterface, activate, arginfo_class_OpenTelemetry_Context_ContextInterface_activate, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_Context_ContextInterface, with, arginfo_class_OpenTelemetry_Context_ContextInterface_with, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_Context_ContextInterface, get, arginfo_class_OpenTelemetry_Context_ContextInterface_get, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_API_Trace_TraceStateInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_API_Trace_TraceStateInterface, __toString, arginfo_class_OpenTelemetry_API_Trace_TraceStateInterface___toString, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_API_Trace_SpanContextInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_API_Trace_SpanContextInterface, getTraceId, arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getTraceId, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_API_Trace_SpanContextInterface, getSpanId, arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getSpanId, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_API_Trace_SpanContextInterface, getTraceFlags, arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getTraceFlags, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_API_Trace_SpanContextInterface, getTraceState, arginfo_class_OpenTelemetry_API_Trace_SpanContextInterface_getTraceState, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Common_Attribute_AttributesInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Common_Attribute_AttributesInterface, has, arginfo_class_OpenTelemetry_SDK_Common_Attribute_AttributesInterface_has, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Common_Attribute_AttributesInterface, get, arginfo_class_OpenTelemetry_SDK_Common_Attribute_AttributesInterface_get, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Common_Attribute_AttributesInterface, getDroppedAttributesCount, arginfo_class_OpenTelemetry_SDK_Common_Attribute_AttributesInterface_getDroppedAttributesCount, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Common_Attribute_AttributesInterface, toArray, arginfo_class_OpenTelemetry_SDK_Common_Attribute_AttributesInterface_toArray, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Common_Future_CancellationInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Common_Future_CancellationInterface, subscribe, arginfo_class_OpenTelemetry_SDK_Common_Future_CancellationInterface_subscribe, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Common_Future_CancellationInterface, unsubscribe, arginfo_class_OpenTelemetry_SDK_Common_Future_CancellationInterface_unsubscribe, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface, getName, arginfo_class_OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface_getName, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface, getVersion, arginfo_class_OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface_getVersion, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface, getSchemaUrl, arginfo_class_OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface_getSchemaUrl, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_StatusDataInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_StatusDataInterface, getCode, arginfo_class_OpenTelemetry_SDK_Trace_StatusDataInterface_getCode, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_StatusDataInterface, getDescription, arginfo_class_OpenTelemetry_SDK_Trace_StatusDataInterface_getDescription, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_SpanDataInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanDataInterface, getName, arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getName, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanDataInterface, getKind, arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getKind, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanDataInterface, getContext, arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getContext, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanDataInterface, getParentContext, arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getParentContext, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanDataInterface, getStatus, arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getStatus, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanDataInterface, getStartEpochNanos, arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getStartEpochNanos, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanDataInterface, getAttributes, arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getAttributes, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanDataInterface, getEndEpochNanos, arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getEndEpochNanos, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanDataInterface, getInstrumentationScope, arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getInstrumentationScope, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanDataInterface, getResource, arginfo_class_OpenTelemetry_SDK_Trace_SpanDataInterface_getResource, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_ReadableSpanInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_ReadableSpanInterface, getName, arginfo_class_OpenTelemetry_SDK_Trace_ReadableSpanInterface_getName, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_ReadableSpanInterface, toSpanData, arginfo_class_OpenTelemetry_SDK_Trace_ReadableSpanInterface_toSpanData, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_ReadWriteSpanInterface_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanProcessorInterface, onStart, arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_onStart, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanProcessorInterface, onEnd, arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_onEnd, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanProcessorInterface, forceFlush, arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_forceFlush, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanProcessorInterface, shutdown, arginfo_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_shutdown, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_BatchSpanProcessor_methods[] = {
	ZEND_ME(OpenTelemetry_SDK_Trace_BatchSpanProcessor, __construct, arginfo_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_BatchSpanProcessor, onStart, arginfo_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor_onStart, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_BatchSpanProcessor, onEnd, arginfo_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor_onEnd, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_BatchSpanProcessor, forceFlush, arginfo_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor_forceFlush, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_BatchSpanProcessor, shutdown, arginfo_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor_shutdown, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_OpenTelemetry_Context_ContextInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\Context", "ContextInterface", class_OpenTelemetry_Context_ContextInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_API_Trace_TraceStateInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\API\\Trace", "TraceStateInterface", class_OpenTelemetry_API_Trace_TraceStateInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_API_Trace_SpanContextInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\API\\Trace", "SpanContextInterface", class_OpenTelemetry_API_Trace_SpanContextInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Common_Attribute_AttributesInterface(zend_class_entry *class_entry_Traversable, zend_class_entry *class_entry_Countable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Common\\Attribute", "AttributesInterface", class_OpenTelemetry_SDK_Common_Attribute_AttributesInterface_methods);
	class_entry = zend_register_internal_interface(&ce);
	zend_class_implements(class_entry, 2, class_entry_Traversable, class_entry_Countable);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Common_Future_CancellationInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Common\\Future", "CancellationInterface", class_OpenTelemetry_SDK_Common_Future_CancellationInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Common\\Instrumentation", "InstrumentationScopeInterface", class_OpenTelemetry_SDK_Common_Instrumentation_InstrumentationScopeInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_StatusDataInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "StatusDataInterface", class_OpenTelemetry_SDK_Trace_StatusDataInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_SpanDataInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "SpanDataInterface", class_OpenTelemetry_SDK_Trace_SpanDataInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_ReadableSpanInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "ReadableSpanInterface", class_OpenTelemetry_SDK_Trace_ReadableSpanInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_ReadWriteSpanInterface(zend_class_entry *class_entry_OpenTelemetry_SDK_Trace_ReadableSpanInterface)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "ReadWriteSpanInterface", class_OpenTelemetry_SDK_Trace_ReadWriteSpanInterface_methods);
	class_entry = zend_register_internal_interface(&ce);
	zend_class_implements(class_entry, 1, class_entry_OpenTelemetry_SDK_Trace_ReadableSpanInterface);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_SpanProcessorInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "SpanProcessorInterface", class_OpenTelemetry_SDK_Trace_SpanProcessorInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_BatchSpanProcessor(zend_class_entry *class_entry_OpenTelemetry_SDK_Trace_SpanProcessorInterface)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "BatchSpanProcessor", class_OpenTelemetry_SDK_Trace_BatchSpanProcessor_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	zend_class_implements(class_entry, 1, class_entry_OpenTelemetry_SDK_Trace_SpanProcessorInterface);

	return class_entry;
}
