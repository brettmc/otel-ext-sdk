#include "sdk_manager.h"
#include "cpp/batch_span_processor.h"
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

// BatchSpanProcessor
trace_sdk_BatchSpanProcessor *batch_span_processor_create() {
    //php_printf("(manager) bsp_create\n");
    auto bsp = new trace_sdk::BatchSpanProcessor();
    return reinterpret_cast<trace_sdk_BatchSpanProcessor *>(bsp);
}
void batch_span_processor_destroy(trace_sdk_BatchSpanProcessor *bsp) {
    delete reinterpret_cast<trace_sdk::BatchSpanProcessor *>(bsp);
}
bool batch_span_processor_shutdown(trace_sdk_BatchSpanProcessor *bsp) {
    return reinterpret_cast<trace_sdk::BatchSpanProcessor *>(bsp)->Shutdown();
}
bool batch_span_processor_force_flush(trace_sdk_BatchSpanProcessor *bsp) {
    return reinterpret_cast<trace_sdk::BatchSpanProcessor *>(bsp)->ForceFlush();
}
void batch_span_processor_on_start(trace_sdk_BatchSpanProcessor *bsp, zval *php_span, zval *php_parent_context) {
    reinterpret_cast<trace_sdk::BatchSpanProcessor *>(bsp)->OnStart(php_span, php_parent_context);
}
void batch_span_processor_on_end(trace_sdk_BatchSpanProcessor *bsp, zval *php_span) {
    reinterpret_cast<trace_sdk::BatchSpanProcessor *>(bsp)->OnEnd(php_span);
}

//end extern C
}