#include "context.h"
#include "php.h"
#include <opentelemetry/nostd/variant.h>
#include <string>
#include <iostream>

namespace trace_sdk
{
    Context::Context() {}
    Context::Context(std::shared_ptr<opentelemetry::context::Context> context) : cpp_context(context) {
        //php_printf("(c++)Context::construct\n");
        //php_printf("(c++)Context::construct (with context pointer)\n");
    }

    Context::~Context()
    {
        //php_printf("(c++)Context::destruct\n");
    }

    void Context::Test() {
        php_printf("(c++)Context::Test\n");
        //cpp_span_context = std::make_shared<opentelemetry::v1::trace::SpanContext>(context);

    }

    Context *Context::GetCurrent() {
        auto context = opentelemetry::context::RuntimeContext::GetCurrent();
        std::shared_ptr<opentelemetry::context::Context> current = std::make_shared<opentelemetry::context::Context>(context);
        //php_printf("(c++)Got current context\n");
        Context *c = new Context(current);
        return c;
    }

    Context *Context::SetValue(char *key, zval* value) {
        //auto variant = ConvertFromZval(value);
        //php_printf("(c++)setting value for: %s\n", key);
        auto new_context = opentelemetry::context::RuntimeContext::SetValue(key, static_cast<int64_t>(123), cpp_context.get());

        Context *c = new Context(std::make_shared<opentelemetry::context::Context>(new_context));
        return c;
    }

    zval Context::GetValue(char *key) {
        //php_printf("(c++)getting value for: %s\n", key);
        opentelemetry::v1::context::ContextValue v = cpp_context.get()->GetValue(key);

        return ToZval(v);
    }
    //private
    zval Context::ToZval(opentelemetry::v1::context::ContextValue value) {
        zval result;
        ZVAL_UNDEF(&result);
        if (opentelemetry::nostd::holds_alternative<int64_t>(value)) {
            int64_t int_value = opentelemetry::nostd::get<int64_t>(value);

            // Convert the int64_t to a zval
            ZVAL_LONG(&result, int_value);
        } else {
            ZVAL_NULL(&result);
            //php_printf("Value not found or wrong type.\n");
        }
        return result;
    }
} // namespace trace_sdk

//HasKey