#ifndef OPENTELEMETRY_SDK_TRACER_MANAGER_H
#define OPENTELEMETRY_SDK_TRACER_MANAGER_H
#include "php.h"

#ifdef __cplusplus
extern "C" {
#endif

// Opaque type for the TracerProvider C++ object
typedef struct trace_sdk_Tracer trace_sdk_Tracer;
typedef struct trace_sdk_Span trace_sdk_Span;
typedef struct trace_sdk_SpanBuilder trace_sdk_SpanBuilder;

// Function to create a Tracer object
trace_sdk_Tracer *tracer_create();

// Function to destroy a Tracer object
void tracer_destroy(trace_sdk_Tracer *tracer);
void span_destroy(trace_sdk_Span *span);
void span_builder_destroy(trace_sdk_SpanBuilder *span_builder);

// Function to invoke DoSomething on the TracerProvider object
void tracer_do_something(trace_sdk_Tracer *tracer);
void tracer_end_span(trace_sdk_Span *span);
void span_builder_add_attribute(trace_sdk_SpanBuilder *span_builder, const char *key, zval *value);
void span_builder_set_span_kind(trace_sdk_SpanBuilder *span_builder, int span_kind);
void span_builder_set_start_timestamp(trace_sdk_SpanBuilder *span_builder, int timestamp);
trace_sdk_Span *span_builder_start_span(trace_sdk_SpanBuilder *builder);
trace_sdk_SpanBuilder *tracer_create_span_builder(trace_sdk_Tracer *tracer, const char *span_name);

#ifdef __cplusplus
}
#endif

#endif //OPENTELEMETRY_SDK_TRACER_MANAGER_H
