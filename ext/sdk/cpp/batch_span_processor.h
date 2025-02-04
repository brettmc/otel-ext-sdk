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
        void OnStart(zval *php_span, zval *parent_context);
        void OnEnd(zval *php_span);
        bool ForceFlush();
        bool Shutdown();
    private:
        std::unique_ptr<opentelemetry::sdk::trace::SpanProcessor> cpp_processor;
        std::string GetEnvVar(const char*, const std::string&);
        void ConvertPhpSpanToRecordable(zval *, opentelemetry::sdk::trace::Recordable *);
        opentelemetry::v1::trace::SpanKind ConvertIntToSpanKind(int);
        static std::map<std::string, opentelemetry::v1::nostd::unique_ptr<opentelemetry::sdk::instrumentationscope::InstrumentationScope>> scope_map;
        static std::shared_ptr<opentelemetry::sdk::resource::Resource> cpp_resource;
        void hexStringToBytes(const std::string &hex_string, uint8_t *out_buffer, size_t buffer_size);
        void AddAttributesToMap(zval *php_resource, opentelemetry::sdk::common::AttributeMap &attribute_map);
        opentelemetry::v1::trace::SpanContext ConvertPhpSpanContextToSpanContext(zval &span_context);
    };
} //namespace trace_sdk

#endif // EXT_BATCH_SPAN_PROCESSOR_H
