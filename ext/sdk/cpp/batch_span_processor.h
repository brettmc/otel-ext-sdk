#ifndef EXT_BATCH_SPAN_PROCESSOR_H
#define EXT_BATCH_SPAN_PROCESSOR_H

#include <memory> //for smart pointers
#include "php.h"
#include "opentelemetry/sdk/trace/batch_span_processor.h"

namespace trace_sdk {
    class BatchSpanProcessor {
    public:
        BatchSpanProcessor();
        ~BatchSpanProcessor();
        void OnStart();
        void OnEnd(zval *php_span);
        bool ForceFlush();
        bool Shutdown();
        void Test();
    private:
        std::unique_ptr<opentelemetry::sdk::trace::SpanProcessor> cpp_processor;
        std::string GetEnvVar(const char*, const std::string&);
        void ConvertPhpSpanToRecordable(zval *, opentelemetry::sdk::trace::Recordable *);
        opentelemetry::v1::trace::SpanKind ConvertIntToSpanKind(int);
    };
} //namespace trace_sdk

#endif // EXT_BATCH_SPAN_PROCESSOR_H
