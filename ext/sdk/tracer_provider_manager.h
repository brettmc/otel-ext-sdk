#ifndef OPENTELEMETRY_SDK_TRACER_PROVIDER_MANAGER_H
#define OPENTELEMETRY_SDK_TRACER_PROVIDER_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tracer_manager.h"

// Opaque type for the TracerProvider C++ object
typedef struct trace_sdk_TracerProvider trace_sdk_TracerProvider;

trace_sdk_TracerProvider *tracer_provider_create();
void tracer_provider_destroy(trace_sdk_TracerProvider *provider);
void tracer_provider_do_something(trace_sdk_TracerProvider *provider);
trace_sdk_Tracer *tracer_provider_get_tracer(trace_sdk_TracerProvider *provider);

#ifdef __cplusplus
}
#endif

#endif //OPENTELEMETRY_SDK_TRACER_PROVIDER_MANAGER_H
