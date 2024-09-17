#ifndef OPENTELEMETRY_SDK_MANAGER_H
#define OPENTELEMETRY_SDK_MANAGER_H
#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

// Opaque types for C++ objects
typedef struct trace_sdk_TracerProvider trace_sdk_TracerProvider;
typedef struct trace_sdk_Tracer trace_sdk_Tracer;
typedef struct trace_sdk_Span trace_sdk_Span;
typedef struct trace_sdk_SpanBuilder trace_sdk_SpanBuilder;

// Tracer
void tracer_destroy(trace_sdk_Tracer *tracer);
void tracer_do_something(trace_sdk_Tracer *tracer);
trace_sdk_SpanBuilder *tracer_create_span_builder(trace_sdk_Tracer *tracer, const char *span_name);

// Span
void span_destroy(trace_sdk_Span *span);
void span_end_span(trace_sdk_Span *span);
void span_update_name(trace_sdk_Span *span, char *name);
void span_set_status(trace_sdk_Span *span, char *status, char *description);

// SpanBuilder
void span_builder_destroy(trace_sdk_SpanBuilder *span_builder);
void span_builder_add_attribute(trace_sdk_SpanBuilder *span_builder, const char *key, zval *value);
void span_builder_set_span_kind(trace_sdk_SpanBuilder *span_builder, int span_kind);
void span_builder_set_start_timestamp(trace_sdk_SpanBuilder *span_builder, int timestamp);
trace_sdk_Span *span_builder_start_span(trace_sdk_SpanBuilder *builder);

// Tracer Provider
trace_sdk_TracerProvider *tracer_provider_create();
void tracer_provider_destroy(trace_sdk_TracerProvider *provider);
void tracer_provider_do_something(trace_sdk_TracerProvider *provider);
trace_sdk_Tracer *tracer_provider_get_tracer(trace_sdk_TracerProvider *provider);

#ifdef __cplusplus
}
#endif

#endif //OPENTELEMETRY_SDK_MANAGER_H
