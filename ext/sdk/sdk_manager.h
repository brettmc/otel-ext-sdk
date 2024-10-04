#ifndef OPENTELEMETRY_SDK_MANAGER_H
#define OPENTELEMETRY_SDK_MANAGER_H
#include "php.h"
#include "opaque_types.h"
#ifdef __cplusplus
extern "C" {
#endif

// BatchSpanProcessor
trace_sdk_BatchSpanProcessor *batch_span_processor_create();
void batch_span_processor_destroy(trace_sdk_BatchSpanProcessor *bsp);
bool batch_span_processor_shutdown(trace_sdk_BatchSpanProcessor *bsp);
bool batch_span_processor_force_flush(trace_sdk_BatchSpanProcessor *bsp);
void batch_span_processor_on_start(trace_sdk_BatchSpanProcessor *bsp);
void batch_span_processor_on_end(trace_sdk_BatchSpanProcessor *bsp, zval *php_span);

// Tracer
void tracer_destroy(trace_sdk_Tracer *tracer);
trace_sdk_SpanBuilder *tracer_create_span_builder(trace_sdk_Tracer *tracer, const char *span_name);

// Span
void span_destroy(trace_sdk_Span *span);
void span_end_span(trace_sdk_Span *span);
void span_update_name(trace_sdk_Span *span, char *name);
void span_set_status(trace_sdk_Span *span, char *status, char *description);
trace_sdk_Scope *span_activate(trace_sdk_Span *span);
trace_sdk_SpanContext * span_get_context(trace_sdk_Span *span);

// SpanContext
void span_context_destroy(trace_sdk_SpanContext *context);
char *span_context_get_trace_id(trace_sdk_SpanContext *context);
char *span_context_get_span_id(trace_sdk_SpanContext *context);
uint8_t span_context_get_trace_flags(trace_sdk_SpanContext *context);
bool span_context_get_is_remote(trace_sdk_SpanContext *context);
bool span_context_get_is_sampled(trace_sdk_SpanContext *context);

// Scope
int scope_detach(trace_sdk_Scope *scope);
void scope_destroy(trace_sdk_Scope *scope);

// Context
trace_sdk_Context *context_get_current();
trace_sdk_Context *context_set_value(trace_sdk_Context *context, char *key, zval *value);
zval context_get_value(trace_sdk_Context *context, char *key);
void context_destroy(trace_sdk_Context *context);

// SpanBuilder
void span_builder_destroy(trace_sdk_SpanBuilder *span_builder);
void span_builder_add_attribute(trace_sdk_SpanBuilder *span_builder, const char *key, zval *value);
void span_builder_set_span_kind(trace_sdk_SpanBuilder *span_builder, int span_kind);
void span_builder_set_start_timestamp(trace_sdk_SpanBuilder *span_builder, int timestamp);
trace_sdk_Span *span_builder_start_span(trace_sdk_SpanBuilder *builder);

// Tracer Provider
trace_sdk_TracerProvider *tracer_provider_create();
void tracer_provider_destroy(trace_sdk_TracerProvider *provider);
trace_sdk_Tracer *tracer_provider_get_tracer(trace_sdk_TracerProvider *provider);
bool tracer_provider_force_flush(trace_sdk_TracerProvider *provider);
bool tracer_provider_shutdown(trace_sdk_TracerProvider *provider);

#ifdef __cplusplus
}
#endif

#endif //OPENTELEMETRY_SDK_MANAGER_H
