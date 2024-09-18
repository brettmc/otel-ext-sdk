#include "scope.h"
#include <php.h>

// Define the namespace as trace_sdk to match the header
namespace trace_sdk
{
    // Constructor: Activate the span
    Scope::Scope(std::unique_ptr<opentelemetry::v1::trace::Scope> _scope) : scope(std::move(_scope))
    {
        //php_printf("(c++)Scope::construct (with c++ scope)\n");
//        scope = _scope;
    }

    // Destructor: Deactivate the span
    Scope::~Scope()
    {
        //php_printf("(c++)Scope::destruct, detached=%d\n", detached);
    }

    void Scope::Test() {
        //php_printf("(c++)Scope::Test detached=%d", detached);
    }
    void Scope::Detach() {
        //php_printf("(c++)Scope::Detach\n");
        if (!detached) {
            //php_printf("(c++)detaching scope\n");
            scope.reset();
            detached = true;
        } else {
            //php_printf("(c++)Scope already detached!\n");
            //todo return false?
        }
        return;
    }

} // namespace trace_sdk
