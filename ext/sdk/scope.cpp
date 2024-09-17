#include "scope.h"
#include <php.h>

// Define the namespace as trace_sdk to match the header
namespace trace_sdk
{
    // Constructor: Activate the span
    Scope::Scope(opentelemetry::v1::nostd::shared_ptr<opentelemetry::v1::trace::Scope> _scope)
    {
        php_printf("(c++)Scope::construct (with c++ scope)\n");
        scope = _scope;
        detached = false;
    }

    // Destructor: Deactivate the span
    Scope::~Scope()
    {
        php_printf("(c++)Scope::destruct\n");
    }

    int Scope::Detach() {
        if (detached) {
            php_printf("(c++)Scope already detached!\n");
            return 1;
        }
        php_printf("(c++)Scope::Detach\n");
        detached = true;


        return 0;
    }

} // namespace trace_sdk
