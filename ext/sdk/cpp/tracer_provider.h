#ifndef EXT_TRACER_PROVIDER_H
#define EXT_TRACER_PROVIDER_H

#include <memory> //for smart pointers
#include "tracer.h"
#include "opentelemetry/trace/provider.h"
#include "opentelemetry/sdk/trace/tracer.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"

// Full class definition of TracerProvider
namespace trace_sdk {
    class TracerProvider {
    public:
        TracerProvider();
        ~TracerProvider();
        opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Tracer> GetTracer();
        bool Shutdown();
    private:
        std::string GetEnvVar(const char*, const std::string&);
        opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::TracerProvider> noop_tracer_provider;
        std::shared_ptr<opentelemetry::sdk::trace::TracerProvider> cpp_tracer_provider;
    };
} //namespace trace_sdk

#endif // EXT_TRACER_PROVIDER_H
