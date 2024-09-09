#include "tracer_provider_manager.h"
#include "tracer_provider.h"
#include "php.h"

extern "C" {

// This function creates a new C++ TracerProvider object
trace_sdk_TracerProvider* tracer_provider_create() {
    //php_printf("(tracer provider manager)tracer_provider_create\n");
    return reinterpret_cast<trace_sdk_TracerProvider*>(new trace_sdk::TracerProvider());
}

// This function destroys the C++ TracerProvider object
void tracer_provider_destroy(trace_sdk_TracerProvider *provider) {
    //php_printf("(tracer provider manager)tracer_provider_destroy\n");
    delete reinterpret_cast<trace_sdk::TracerProvider*>(provider);
}

// This function calls the DoSomething method on the C++ TracerProvider object
void tracer_provider_do_something(trace_sdk_TracerProvider *provider) {
    //php_printf("(tracer provider manager)tracer_provider_do_something\n");
    reinterpret_cast<trace_sdk::TracerProvider*>(provider)->DoSomething();
}

trace_sdk_Tracer *tracer_provider_get_tracer(trace_sdk_TracerProvider *provider) {
    //php_printf("(tracer provider manager)tracer_provider_get_tracer::pre\n");
    auto p = reinterpret_cast<trace_sdk::TracerProvider*>(provider);
    auto tracer = new trace_sdk::Tracer(p->GetTracer());
    //php_printf("(tracer provider manager)tracer_provider_get_tracer::post\n");
    return reinterpret_cast<trace_sdk_Tracer*>(tracer);
}

//end extern C
}