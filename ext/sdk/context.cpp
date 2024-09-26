#include "context.h"
#include "php.h"
#include <opentelemetry/nostd/variant.h>
#include <string>
#include <zend_exceptions.h>
#include "span_class.h"
#include "span_context_class.h"
#include "span.h"
#include "span_context.h"

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
        //php_printf("(c++)Context::Test\n");
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
        auto new_context = opentelemetry::context::RuntimeContext::SetValue(key, FromZval(value), cpp_context.get());

        Context *c = new Context(std::make_shared<opentelemetry::context::Context>(new_context));
        return c;
    }

    zval Context::GetValue(char *key) {
        //php_printf("(c++)getting value for: %s\n", key);
        opentelemetry::v1::context::ContextValue v = cpp_context.get()->GetValue(key);

        return ToZval(v);
    }
    //private
    opentelemetry::v1::context::ContextValue Context::FromZval(zval *value) {
        opentelemetry::v1::context::ContextValue cpp_value;

        // Convert zval to C++ type
        switch (Z_TYPE_P(value)) {
            case IS_LONG:
                cpp_value = static_cast<int64_t>(Z_LVAL_P(value));  // Convert long to int64_t
                break;

            case IS_DOUBLE:
                cpp_value = static_cast<double>(Z_DVAL_P(value));  // Convert double
                break;

            case IS_TRUE:
            case IS_FALSE:
                cpp_value = static_cast<bool>(Z_TYPE_P(value) == IS_TRUE);  // Convert boolean
                break;
            case IS_OBJECT:
                // Check if the object is a Span
                if (instanceof_function(Z_OBJCE_P(value), span_ce)) {
                    php_span_object *span_obj = Z_SPAN_OBJ_P(value);  // Cast zval to span object
                    trace_sdk::Span *span = reinterpret_cast<trace_sdk::Span*>(span_obj->cpp_span);

                    opentelemetry::nostd::shared_ptr<opentelemetry::trace::Span> span_ptr = span->GetInternal();
                    cpp_value = span_ptr;
                }
                // Check if the object is a SpanContext
                else if (instanceof_function(Z_OBJCE_P(value), span_context_ce)) {
                    php_span_context_object *span_context_obj = Z_SPAN_CONTEXT_OBJ_P(value);  // Cast zval to span context object
                    trace_sdk::SpanContext *spanContext = reinterpret_cast<trace_sdk::SpanContext*>(span_context_obj->cpp_span_context);

                    opentelemetry::nostd::shared_ptr<opentelemetry::trace::SpanContext> span_context_ptr = spanContext->GetInternal();
                    cpp_value = span_context_ptr;
                } else {
                    // Unsupported object type
                    zend_throw_exception(zend_ce_exception, "Unsupported object type", 0);
                    return opentelemetry::nostd::monostate();  // Return default value
                }
                break;
            default:
                zend_throw_exception(zend_ce_exception, "Unsupported Context value type", 0);
                cpp_value = opentelemetry::nostd::monostate();  // Use monostate to represent an unsupported type
                break;
        }

        return cpp_value;
    }
    zval Context::ToZval(opentelemetry::v1::context::ContextValue value) {
        zval result;
        ZVAL_UNDEF(&result);
        if (opentelemetry::nostd::holds_alternative<int64_t>(value)) {
            ZVAL_LONG(&result, opentelemetry::nostd::get<int64_t>(value));
        } else if (opentelemetry::nostd::holds_alternative<double>(value)) {
            ZVAL_DOUBLE(&result, opentelemetry::nostd::get<double>(value));
        } else if (opentelemetry::nostd::holds_alternative<bool>(value)) {
            ZVAL_BOOL(&result, opentelemetry::nostd::get<bool>(value));
        } else if (opentelemetry::nostd::holds_alternative<opentelemetry::nostd::shared_ptr<opentelemetry::trace::Span>>(value)) {
            // Convert Span to zval (PHP object)
            object_init_ex(&result, span_ce);  // Initialize a new Span object
            auto span = new trace_sdk::Span(opentelemetry::nostd::get<opentelemetry::nostd::shared_ptr<opentelemetry::trace::Span>>(value));
            php_span_object *span_intern = Z_SPAN_OBJ_P(&result);
            span_intern->cpp_span = reinterpret_cast<trace_sdk_Span*>(span);
        } else if (opentelemetry::nostd::holds_alternative<opentelemetry::nostd::shared_ptr<opentelemetry::trace::SpanContext>>(value)) {
            // Convert SpanContext to zval (PHP object)
            object_init_ex(&result, span_context_ce);  // Initialize a new SpanContext object
            auto spanContext = new trace_sdk::SpanContext(opentelemetry::nostd::get<opentelemetry::nostd::shared_ptr<opentelemetry::trace::SpanContext>>(value));
            php_span_context_object *span_context_intern = Z_SPAN_CONTEXT_OBJ_P(&result);
            span_context_intern->cpp_span_context = reinterpret_cast<trace_sdk_SpanContext*>(spanContext);
        } else {
            ZVAL_NULL(&result);  // If type is not supported, return NULL
        }
        return result;
    }
} // namespace trace_sdk

//HasKey