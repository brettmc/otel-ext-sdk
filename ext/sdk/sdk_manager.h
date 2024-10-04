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
void batch_span_processor_on_start(trace_sdk_BatchSpanProcessor *bsp, zval *php_span, zval *php_parent_context);
void batch_span_processor_on_end(trace_sdk_BatchSpanProcessor *bsp, zval *php_span);

#ifdef __cplusplus
}
#endif

#endif //OPENTELEMETRY_SDK_MANAGER_H
