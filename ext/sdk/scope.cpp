#include "scope.h"
#include <php.h>

// Define the namespace as trace_sdk to match the header
namespace trace_sdk
{
    // Constructor: Activate the span
    Scope::Scope(opentelemetry::v1::nostd::unique_ptr<opentelemetry::v1::context::Token> token) : token(std::move(token))
    {
        php_printf("(c++)Scope::construct (with c++ token)\n");
    }

    // Destructor: Deactivate the span
    Scope::~Scope()
    {
        php_printf("(c++)Scope::destruct\n");
        if (!detached) {
            php_printf("(c++)Scope::destroyed, detaching the Token\n");
            Detach();
        }
    }

    bool Scope::Detach() {
        if (detached) {
            php_printf("(c++)Scope already detached!\n");
            return false;
        }
        php_printf("(c++)Scope::Detach\n");
        bool result = opentelemetry::context::RuntimeContext::Detach(*token);
        detached = true;
        return result;
    }

} // namespace trace_sdk
