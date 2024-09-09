#include "tracer_provider.h"
#include "php.h"
#include <Zend/zend_exceptions.h>

#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
//#include "opentelemetry/exporters/otlp/otlp_http_exporter.h"
//#include "opentelemetry/exporters/otlp/otlp_http_exporter_factory.h"
//#include "opentelemetry/exporters/otlp/otlp_http_exporter_options.h"
#include "opentelemetry/sdk/resource/resource.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/batch_span_processor_factory.h"
#include "opentelemetry/sdk/trace/batch_span_processor_options.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/provider.h"

namespace trace_sdk {
    TracerProvider::TracerProvider() {
        //TODO use global (effectively singleton)
        //php_printf("(c++)TracerProvider construct\n");
        opentelemetry::sdk::resource::ResourceAttributes attributes = {
                {"service.name", "my-service"},
                {"service.namespace", "foo"},
                {"service.instance.id", "instance-1"},
                {"service.version", "0.0.1"},
                {"telemetry.sdk.language", "php"}
        };

        auto resource = opentelemetry::sdk::resource::Resource::Create(attributes);
        auto exporter  = opentelemetry::exporter::trace::OStreamSpanExporterFactory::Create();
        auto processor = opentelemetry::sdk::trace::SimpleSpanProcessorFactory::Create(std::move(exporter));
        opentelemetry::sdk::trace::BatchSpanProcessorOptions bsp_options;
        //bsp_options.schedule_delay_millis = 1000;
        //auto processor = opentelemetry::sdk::trace::BatchSpanProcessorFactory::Create(std::move(exporter), bsp_options);
        std::shared_ptr<opentelemetry::v1::sdk::trace::TracerProvider> tracer_provider = opentelemetry::sdk::trace::TracerProviderFactory::Create(std::move(processor), resource);
        cpp_tracer_provider = tracer_provider;
    }

    TracerProvider::~TracerProvider() {
        // Destructor logic
        //php_printf("(c++)TracerProvider destructor\n");
        cpp_tracer_provider->Shutdown();
        // No need to manually delete cpp_tracer_provider.
        // std::shared_ptr will automatically handle the cleanup.
    }

    opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Tracer> TracerProvider::GetTracer() {
        //php_printf("(c++)Getting a Tracer from TracerProvider...\n");
        //return std::make_shared<Tracer>();
        return cpp_tracer_provider->GetTracer("foo");
    }

    void TracerProvider::DoSomething() {
        if (!cpp_tracer_provider) {
            zend_throw_exception(NULL, "TracerProvider is not initialized", 0);
            //todo throw?
        }
        //php_printf("(c++)Doing something with the TracerProvider...\n");
        auto tracer = cpp_tracer_provider->GetTracer("example");
        auto span = tracer->StartSpan("hello-from-php-cpp");
        span->End();
    }
}
