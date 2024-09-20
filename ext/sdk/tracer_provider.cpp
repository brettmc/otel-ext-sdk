#include "tracer_provider.h"
#include "php.h"
#include <Zend/zend_exceptions.h>
#include "../php_opentelemetry_sdk.h"
#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter.h"
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
        if (noop_tracer_provider == nullptr) {
            noop_tracer_provider = opentelemetry::trace::Provider::GetTracerProvider();
            //noop_tracer_provider = std::make_shared<opentelemetry::v1::trace::TracerProvider>(p);
        }
        std::string otel_exporter = GetEnvVar("OTEL_TRACES_EXPORTER", "otlp");
        if (otel_exporter == "none") {
            return;
        }
        std::unique_ptr<opentelemetry::sdk::trace::SpanExporter> exporter;
        if (otel_exporter == "otlp") {
            exporter = std::make_unique<opentelemetry::exporter::otlp::OtlpHttpExporter>();
        } else {
            exporter = opentelemetry::exporter::trace::OStreamSpanExporterFactory::Create();
        }


        //TODO use global (effectively singleton)
        //php_printf("(c++)TracerProvider construct\n");
        opentelemetry::sdk::resource::ResourceAttributes attributes = {
                {"telemetry.sdk.language", "php"},
                {"telemetry.sdk.name", "ext-opentelemetry"},
                {"telemetry.sdk.version", PHP_OPENTELEMETRY_SDK_VERSION}
        };

        auto resource = opentelemetry::sdk::resource::Resource::Create(attributes);
        //auto exporter  = opentelemetry::exporter::trace::OStreamSpanExporterFactory::Create();
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
        if (cpp_tracer_provider) {
            cpp_tracer_provider->Shutdown();
        }
        // No need to manually delete cpp_tracer_provider.
        // std::shared_ptr will automatically handle the cleanup.
    }

    opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Tracer> TracerProvider::GetTracer() {
        //php_printf("(c++)Getting a Tracer from TracerProvider...\n");
        //return std::make_shared<Tracer>();
        if (cpp_tracer_provider) {
            return cpp_tracer_provider->GetTracer("foo");
        } else {
            return noop_tracer_provider->GetTracer("foo");
        }
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

    std::string TracerProvider::GetEnvVar(const char* var_name, const std::string& default_value = "") {
        const char* value = std::getenv(var_name); // Get the environment variable
        if (value != nullptr) {
                return std::string(value); // Return the value if it exists
            }
        return default_value; // Return the default value if not set
    }

}
