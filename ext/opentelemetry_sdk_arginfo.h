/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: d30fe392bdf1ea3cbb3177989df600ab5d4a9ea7 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_ScopeInterface_detach, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Trace_Scope_detach arginfo_class_OpenTelemetry_SDK_Trace_ScopeInterface_detach

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_getTraceId, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_getSpanId arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_getTraceId

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_getTraceFlags arginfo_class_OpenTelemetry_SDK_Trace_ScopeInterface_detach

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_isRemote, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_isSampled arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_isRemote

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanContext_getTraceId arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_getTraceId

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanContext_getSpanId arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_getTraceId

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanContext_getTraceFlags arginfo_class_OpenTelemetry_SDK_Trace_ScopeInterface_detach

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanContext_isRemote arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_isRemote

#define arginfo_class_OpenTelemetry_SDK_Trace_SpanContext_isSampled arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_isRemote

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_activate, 0, 0, OpenTelemetry\\SDK\\Trace\\ScopeInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_updateName, 0, 1, OpenTelemetry\\SDK\\Trace\\SpanInterface, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_setStatus, 0, 1, OpenTelemetry\\SDK\\Trace\\SpanInterface, 0)
	ZEND_ARG_TYPE_INFO(0, code, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, description, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_end, 0, 0, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, endTimestamp, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_getContext, 0, 0, OpenTelemetry\\SDK\\Trace\\SpanContextInterface, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Trace_Span_updateName arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_updateName

#define arginfo_class_OpenTelemetry_SDK_Trace_Span_setStatus arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_setStatus

#define arginfo_class_OpenTelemetry_SDK_Trace_Span_end arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_end

#define arginfo_class_OpenTelemetry_SDK_Trace_Span_activate arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_activate

#define arginfo_class_OpenTelemetry_SDK_Trace_Span_getContext arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_getContext

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_setAttribute, 0, 2, OpenTelemetry\\SDK\\Trace\\SpanBuilder, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_setAttributes, 0, 1, OpenTelemetry\\SDK\\Trace\\SpanBuilder, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, attributes, Traversable, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_setSpanKind, 0, 1, OpenTelemetry\\SDK\\Trace\\SpanBuilder, 0)
	ZEND_ARG_TYPE_INFO(0, spanKind, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_setStartTimestamp, 0, 1, OpenTelemetry\\SDK\\Trace\\SpanBuilder, 0)
	ZEND_ARG_TYPE_INFO(0, timestamp, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_setParent, 0, 0, OpenTelemetry\\SDK\\Trace\\SpanBuilder, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_addLink, 0, 1, OpenTelemetry\\SDK\\Trace\\SpanBuilder, 0)
	ZEND_ARG_OBJ_INFO(0, context, OpenTelemetry\\SDK\\Trace\\SpanContextInterface, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, attributes, Traversable, MAY_BE_ARRAY, "[]")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_startSpan, 0, 0, OpenTelemetry\\SDK\\Trace\\Span, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_Tracer_spanBuilder, 0, 1, OpenTelemetry\\SDK\\Trace\\SpanBuilder, 0)
	ZEND_ARG_TYPE_INFO(0, spanName, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_TracerProvider___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OpenTelemetry_SDK_Trace_TracerProvider___destruct arginfo_class_OpenTelemetry_SDK_Trace_TracerProvider___construct

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_OpenTelemetry_SDK_Trace_TracerProvider_getTracer, 0, 1, OpenTelemetry\\SDK\\Trace\\Tracer, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()


ZEND_METHOD(OpenTelemetry_SDK_Trace_Scope, detach);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanContext, getTraceId);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanContext, getSpanId);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanContext, getTraceFlags);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanContext, isRemote);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanContext, isSampled);
ZEND_METHOD(OpenTelemetry_SDK_Trace_Span, updateName);
ZEND_METHOD(OpenTelemetry_SDK_Trace_Span, setStatus);
ZEND_METHOD(OpenTelemetry_SDK_Trace_Span, end);
ZEND_METHOD(OpenTelemetry_SDK_Trace_Span, activate);
ZEND_METHOD(OpenTelemetry_SDK_Trace_Span, getContext);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, setAttribute);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, setAttributes);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, setSpanKind);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, setStartTimestamp);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, setParent);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, addLink);
ZEND_METHOD(OpenTelemetry_SDK_Trace_SpanBuilder, startSpan);
ZEND_METHOD(OpenTelemetry_SDK_Trace_Tracer, spanBuilder);
ZEND_METHOD(OpenTelemetry_SDK_Trace_TracerProvider, __construct);
ZEND_METHOD(OpenTelemetry_SDK_Trace_TracerProvider, __destruct);
ZEND_METHOD(OpenTelemetry_SDK_Trace_TracerProvider, getTracer);


static const zend_function_entry class_OpenTelemetry_SDK_Trace_ScopeInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_ScopeInterface, detach, arginfo_class_OpenTelemetry_SDK_Trace_ScopeInterface_detach, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_Scope_methods[] = {
	ZEND_ME(OpenTelemetry_SDK_Trace_Scope, detach, arginfo_class_OpenTelemetry_SDK_Trace_Scope_detach, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_SpanContextInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanContextInterface, getTraceId, arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_getTraceId, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanContextInterface, getSpanId, arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_getSpanId, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanContextInterface, getTraceFlags, arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_getTraceFlags, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanContextInterface, isRemote, arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_isRemote, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanContextInterface, isSampled, arginfo_class_OpenTelemetry_SDK_Trace_SpanContextInterface_isSampled, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_SpanContext_methods[] = {
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanContext, getTraceId, arginfo_class_OpenTelemetry_SDK_Trace_SpanContext_getTraceId, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanContext, getSpanId, arginfo_class_OpenTelemetry_SDK_Trace_SpanContext_getSpanId, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanContext, getTraceFlags, arginfo_class_OpenTelemetry_SDK_Trace_SpanContext_getTraceFlags, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanContext, isRemote, arginfo_class_OpenTelemetry_SDK_Trace_SpanContext_isRemote, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanContext, isSampled, arginfo_class_OpenTelemetry_SDK_Trace_SpanContext_isSampled, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_SpanInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanInterface, activate, arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_activate, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanInterface, updateName, arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_updateName, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanInterface, setStatus, arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_setStatus, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanInterface, end, arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_end, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(OpenTelemetry_SDK_Trace_SpanInterface, getContext, arginfo_class_OpenTelemetry_SDK_Trace_SpanInterface_getContext, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_Span_methods[] = {
	ZEND_ME(OpenTelemetry_SDK_Trace_Span, updateName, arginfo_class_OpenTelemetry_SDK_Trace_Span_updateName, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_Span, setStatus, arginfo_class_OpenTelemetry_SDK_Trace_Span_setStatus, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_Span, end, arginfo_class_OpenTelemetry_SDK_Trace_Span_end, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_Span, activate, arginfo_class_OpenTelemetry_SDK_Trace_Span_activate, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_Span, getContext, arginfo_class_OpenTelemetry_SDK_Trace_Span_getContext, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_SpanBuilder_methods[] = {
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanBuilder, setAttribute, arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_setAttribute, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanBuilder, setAttributes, arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_setAttributes, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanBuilder, setSpanKind, arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_setSpanKind, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanBuilder, setStartTimestamp, arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_setStartTimestamp, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanBuilder, setParent, arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_setParent, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanBuilder, addLink, arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_addLink, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_SpanBuilder, startSpan, arginfo_class_OpenTelemetry_SDK_Trace_SpanBuilder_startSpan, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_Tracer_methods[] = {
	ZEND_ME(OpenTelemetry_SDK_Trace_Tracer, spanBuilder, arginfo_class_OpenTelemetry_SDK_Trace_Tracer_spanBuilder, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_OpenTelemetry_SDK_Trace_TracerProvider_methods[] = {
	ZEND_ME(OpenTelemetry_SDK_Trace_TracerProvider, __construct, arginfo_class_OpenTelemetry_SDK_Trace_TracerProvider___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_TracerProvider, __destruct, arginfo_class_OpenTelemetry_SDK_Trace_TracerProvider___destruct, ZEND_ACC_PUBLIC)
	ZEND_ME(OpenTelemetry_SDK_Trace_TracerProvider, getTracer, arginfo_class_OpenTelemetry_SDK_Trace_TracerProvider_getTracer, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_ScopeInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "ScopeInterface", class_OpenTelemetry_SDK_Trace_ScopeInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_Scope(zend_class_entry *class_entry_OpenTelemetry_SDK_Trace_ScopeInterface)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "Scope", class_OpenTelemetry_SDK_Trace_Scope_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	zend_class_implements(class_entry, 1, class_entry_OpenTelemetry_SDK_Trace_ScopeInterface);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_SpanContextInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "SpanContextInterface", class_OpenTelemetry_SDK_Trace_SpanContextInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_SpanContext(zend_class_entry *class_entry_OpenTelemetry_SDK_Trace_SpanContextInterface)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "SpanContext", class_OpenTelemetry_SDK_Trace_SpanContext_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	zend_class_implements(class_entry, 1, class_entry_OpenTelemetry_SDK_Trace_SpanContextInterface);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_SpanInterface(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "SpanInterface", class_OpenTelemetry_SDK_Trace_SpanInterface_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_Span(zend_class_entry *class_entry_OpenTelemetry_SDK_Trace_SpanInterface)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "Span", class_OpenTelemetry_SDK_Trace_Span_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	zend_class_implements(class_entry, 1, class_entry_OpenTelemetry_SDK_Trace_SpanInterface);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_SpanBuilder(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "SpanBuilder", class_OpenTelemetry_SDK_Trace_SpanBuilder_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_Tracer(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "Tracer", class_OpenTelemetry_SDK_Trace_Tracer_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	return class_entry;
}

static zend_class_entry *register_class_OpenTelemetry_SDK_Trace_TracerProvider(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "OpenTelemetry\\SDK\\Trace", "TracerProvider", class_OpenTelemetry_SDK_Trace_TracerProvider_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	return class_entry;
}
