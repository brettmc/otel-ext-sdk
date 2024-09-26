#include "sdk_manager.h"
#include "tracer.h"
#include "tracer_provider.h"
#include "span_builder.h"
#include "span_context.h"
#include "span.h"
#include "scope.h"
#include "context.h"
#include "utils.h"
#include "php.h"
#include <Zend/zend_exceptions.h>
#include <opentelemetry/common/key_value_iterable_view.h>

/**
 * This file manages the interface between PHP/C code (in .c files) and C++ classes which
 * interact with the opentelemetry-cpp SDK.
 *
 * The key to the interfacing lies in how C files use an opaque pointer to the C++ class,
 * but never use it except through this manager. The pointer is cast between opaque and
 * real via reinterpret_cast, for example trace_sdk::Tracer (C++) <--> trace_sdk_Tracer (C)
 */

extern "C" {

// Tracer
void tracer_destroy(trace_sdk_Tracer *tracer) {
    //php_printf("(tracer manager)tracer_destroy\n");
    delete reinterpret_cast<trace_sdk::Tracer*>(tracer);
}

trace_sdk_SpanBuilder* tracer_create_span_builder(trace_sdk_Tracer* tracer, const char* span_name) {
    auto t = reinterpret_cast<trace_sdk::Tracer*>(tracer);
    auto cpp_span_builder = new trace_sdk::SpanBuilder(t->GetTracer(), span_name);
    return reinterpret_cast<trace_sdk_SpanBuilder*>(cpp_span_builder);
}

void tracer_do_something(trace_sdk_Tracer *tracer) {
    //php_printf("(tracer manager)tracer_do_something\n");
    reinterpret_cast<trace_sdk::Tracer*>(tracer)->DoSomething();
}
// end Tracer

// Span
void span_destroy(trace_sdk_Span *span) {
    delete reinterpret_cast<trace_sdk::Span*>(span);
}

void span_end_span(trace_sdk_Span *span) {
    reinterpret_cast<trace_sdk::Span*>(span)->End();
}

void span_update_name(trace_sdk_Span *span, char *name) {
    reinterpret_cast<trace_sdk::Span*>(span)->UpdateName(name);
}

void span_set_status(trace_sdk_Span *span, char *status, char *description) {
    reinterpret_cast<trace_sdk::Span*>(span)->SetStatus(status, description);
}

trace_sdk_Scope *span_activate(trace_sdk_Span *span) {
    std::unique_ptr<opentelemetry::v1::trace::Scope> cpp_scope = reinterpret_cast<trace_sdk::Span*>(span)->Activate();
    auto scope = new trace_sdk::Scope(std::move(cpp_scope));
    return reinterpret_cast<trace_sdk_Scope*>(scope);
}

trace_sdk_SpanContext *span_get_context(trace_sdk_Span *span) {
    auto s = reinterpret_cast<trace_sdk::Span*>(span);
    opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::SpanContext> cpp_span_context = s->GetContext();
    auto context = new trace_sdk::SpanContext(cpp_span_context);
    return reinterpret_cast<trace_sdk_SpanContext*>(context);
}
// end Span

// SpanContext
char *span_context_get_trace_id(trace_sdk_SpanContext *context) {
    auto sc = reinterpret_cast<trace_sdk::SpanContext*>(context);
    std::string trace_id = sc->GetTraceId();

    return CreateCharPointerFromString(trace_id);
}
char *span_context_get_span_id(trace_sdk_SpanContext *context) {
    auto sc = reinterpret_cast<trace_sdk::SpanContext*>(context);
    return CreateCharPointerFromString(sc->GetSpanId());
}
uint8_t span_context_get_trace_flags(trace_sdk_SpanContext *context) {
    auto sc = reinterpret_cast<trace_sdk::SpanContext*>(context);
    return sc->GetTraceFlags();
}
bool span_context_get_is_remote(trace_sdk_SpanContext *context) {
    auto sc = reinterpret_cast<trace_sdk::SpanContext*>(context);
    return sc->IsRemote();
}
bool span_context_get_is_sampled(trace_sdk_SpanContext *context) {
    auto sc = reinterpret_cast<trace_sdk::SpanContext*>(context);
    return sc->IsSampled();
}
// SpanContext end

// Scope
void scope_destroy(trace_sdk_Scope *scope) {
    delete reinterpret_cast<trace_sdk::Scope*>(scope);
}
int scope_detach(trace_sdk_Scope *scope_ptr) {
    //delete reinterpret_cast<trace_sdk::Scope*>(scope);
    trace_sdk::Scope *scope = reinterpret_cast<trace_sdk::Scope*>(scope_ptr);
    scope->Detach();
    //scope->Test();
    return 0;
}
// end Scope

// Context
trace_sdk_Context *context_get_current() {
    trace_sdk::Context *context = trace_sdk::Context::GetCurrent();
    return reinterpret_cast<trace_sdk_Context*>(context);
}

void context_test(/*trace_sdk_Context *context_ptr*/) {
    //trace_sdk::Context *context = reinterpret_cast<trace_sdk::Context*>(context_ptr);
    trace_sdk::Context::Test();
}
trace_sdk_Context *context_set_value(trace_sdk_Context *context, char *key, zval *value){
    trace_sdk::Context *cpp_context = reinterpret_cast<trace_sdk::Context*>(context);
    trace_sdk::Context *ctx_new = cpp_context->SetValue(key, value);
    return reinterpret_cast<trace_sdk_Context*>(ctx_new);
}
zval *context_get_value(trace_sdk_Context *context, char *key) {
    trace_sdk::Context *cpp_context = reinterpret_cast<trace_sdk::Context*>(context);
    return cpp_context->GetValue(key);
//    zval *zv;
//    ZVAL_STRING(zv, "hello");
//    return zv;
}
// Context end

// SpanBuilder
void span_builder_destroy(trace_sdk_SpanBuilder *span_builder) {
    delete reinterpret_cast<trace_sdk::SpanBuilder*>(span_builder);
}

trace_sdk_Span *span_builder_start_span(trace_sdk_SpanBuilder *builder) {
    auto cpp_span = reinterpret_cast<trace_sdk::SpanBuilder*>(builder)->StartSpan();
    auto tracer = reinterpret_cast<trace_sdk::SpanBuilder*>(builder)->GetTracer();
    auto span = new trace_sdk::Span(cpp_span, tracer);
    //php_printf("new span created: %p\n", span);
    return reinterpret_cast<trace_sdk_Span*>(span);
}

void span_builder_set_span_kind(trace_sdk_SpanBuilder *span_builder, int span_kind)
{
    reinterpret_cast<trace_sdk::SpanBuilder*>(span_builder)->SetSpanKind(span_kind);
}
void span_builder_set_start_timestamp(trace_sdk_SpanBuilder *span_builder, int timestamp)
{
    reinterpret_cast<trace_sdk::SpanBuilder*>(span_builder)->SetStartTimestamp(timestamp);
}
void span_builder_add_attribute(trace_sdk_SpanBuilder *span_builder, const char *key, zval *value)
{
    // Convert zval to the appropriate C++ type
    opentelemetry::common::AttributeValue attr_value;

    if (Z_TYPE_P(value) == IS_STRING) {
        attr_value = Z_STRVAL_P(value);
    } else if (Z_TYPE_P(value) == IS_LONG) {
        attr_value = Z_LVAL_P(value);
    } else if (Z_TYPE_P(value) == IS_DOUBLE) {
        attr_value = Z_DVAL_P(value);
    } else if (Z_TYPE_P(value) == IS_TRUE) {
        attr_value = true;
    } else if (Z_TYPE_P(value) == IS_FALSE) {
        attr_value = false;
    } else {
        zend_throw_exception(NULL, "Unsupported attribute type.", 0);
        return;
    }

    // Store the key-value pair in the SpanBuilder object (C++)
    reinterpret_cast<trace_sdk::SpanBuilder*>(span_builder)->AddAttribute(key, attr_value);
}
// end SpanBuilder


// TracerProvider
trace_sdk_TracerProvider* tracer_provider_create() {
    //php_printf("(tracer provider manager)tracer_provider_create\n");
    return reinterpret_cast<trace_sdk_TracerProvider*>(new trace_sdk::TracerProvider());
}

void tracer_provider_destroy(trace_sdk_TracerProvider *provider) {
    //php_printf("(tracer provider manager)tracer_provider_destroy\n");
    delete reinterpret_cast<trace_sdk::TracerProvider*>(provider);
}

void tracer_provider_do_something(trace_sdk_TracerProvider *provider) {
    //php_printf("(tracer provider manager)tracer_provider_do_something\n");
    reinterpret_cast<trace_sdk::TracerProvider*>(provider)->DoSomething();
}

trace_sdk_Tracer *tracer_provider_get_tracer(trace_sdk_TracerProvider *provider) {
    //php_printf("(tracer provider manager)tracer_provider_get_tracer::pre\n");
    auto p = reinterpret_cast<trace_sdk::TracerProvider*>(provider);
    auto tracer = new trace_sdk::Tracer(p->GetTracer());
    //php_printf("(tracer provider manager)tracer_provider_get_tracer::post\n");
    return reinterpret_cast<trace_sdk_Tracer*>(tracer);
}
// end TracerProvider

//end extern C
}