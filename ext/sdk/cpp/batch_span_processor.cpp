#include "batch_span_processor.h"
extern "C" {
#include "ext/standard/basic_functions.h"
#include "ext/spl/spl_exceptions.h"
}
#include "php.h"
#include <string>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>
#include "../../php_opentelemetry_sdk.h"
#include "opentelemetry/exporters/ostream/span_exporter_factory.h"
#include "opentelemetry/exporters/otlp/otlp_grpc_exporter.h"
#include "opentelemetry/exporters/otlp/otlp_http_exporter.h"
#include "opentelemetry/sdk/instrumentationscope/instrumentation_scope.h"
#include "opentelemetry/sdk/resource/resource.h"
#include "opentelemetry/sdk/trace/exporter.h"
#include "opentelemetry/sdk/trace/processor.h"
#include "opentelemetry/sdk/trace/recordable.h"
#include "opentelemetry/sdk/trace/batch_span_processor_factory.h"
#include "opentelemetry/sdk/trace/batch_span_processor_options.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/common/attribute_value.h"
#include "opentelemetry/trace/provider.h"
#include "opentelemetry/trace/span_context.h"
#include "opentelemetry/trace/trace_flags.h"
#include "opentelemetry/trace/trace_id.h"
#include "opentelemetry/trace/span_id.h"
#include <opentelemetry/common/attribute_value.h>
#include <opentelemetry/common/timestamp.h>
#include <chrono>

namespace trace_sdk {
    std::map<std::string, opentelemetry::nostd::unique_ptr<opentelemetry::sdk::instrumentationscope::InstrumentationScope>> BatchSpanProcessor::scope_map;
    std::shared_ptr<opentelemetry::sdk::resource::Resource> BatchSpanProcessor::cpp_resource = nullptr;
    BatchSpanProcessor::BatchSpanProcessor() {
        //php_printf("(c++)BSP::construct\n");
        std::string otel_exporter = GetEnvVar("OTEL_TRACES_EXPORTER", "otlp");
        if (otel_exporter == "none") {
            return;
        }
        std::unique_ptr<opentelemetry::sdk::trace::SpanExporter> exporter;
        if (otel_exporter == "console") {
            exporter = opentelemetry::exporter::trace::OStreamSpanExporterFactory::Create();
        } else if (otel_exporter == "otlp") {
            std::string otel_protocol = GetEnvVar("OTEL_EXPORTER_OTLP_PROTOCOL", "grpc");
            if (otel_protocol == "grpc") {
                exporter = std::make_unique<opentelemetry::exporter::otlp::OtlpGrpcExporter>();
            } else if (otel_protocol == "http/protobuf") {
                exporter = std::make_unique<opentelemetry::exporter::otlp::OtlpHttpExporter>();
            } else {
                zend_throw_exception(spl_ce_InvalidArgumentException, "Invalid OTEL_EXPORTER_OTLP_PROTOCOL", 0);
                return;
            }
        } else {
            zend_throw_exception(spl_ce_InvalidArgumentException, "Invalid OTEL_TRACES_EXPORTER", 0);
            return;
        }
        int max_queue_size = std::stoi(GetEnvVar("OTEL_BSP_MAX_QUEUE_SIZE", "2048"));
        int schedule_delay = std::stoi(GetEnvVar("OTEL_BSP_SCHEDULE_DELAY", "5000")); // milliseconds
        int max_export_batch_size = std::stoi(GetEnvVar("OTEL_BSP_MAX_EXPORT_BATCH_SIZE", "512"));
        opentelemetry::sdk::trace::BatchSpanProcessorOptions bsp_options;
        bsp_options.schedule_delay_millis = std::chrono::milliseconds(schedule_delay);
        bsp_options.max_export_batch_size = max_export_batch_size;
        bsp_options.max_queue_size = max_queue_size;
        cpp_processor = opentelemetry::sdk::trace::BatchSpanProcessorFactory::Create(std::move(exporter), bsp_options);
    }

    BatchSpanProcessor::~BatchSpanProcessor() {
        //php_printf("(c++)BatchSpanProcessor destructor\n");
        if (cpp_processor) {
            cpp_processor->Shutdown();
        }
    }

    bool BatchSpanProcessor::ForceFlush() {
        //php_printf("(c++)BatchSpanProcessor ForceFlush\n");
        cpp_processor->ForceFlush();
        return true;
    }

    bool BatchSpanProcessor::Shutdown() {
        //php_printf("(c++)BatchSpanProcessor Shutdown\n");
        cpp_processor->Shutdown();
        return true;
    }

    void BatchSpanProcessor::OnStart(zval *php_span, zval *parent_context) {
        //todo: Context vs SpanContext
        //php_printf("(c++)BatchSpanProcessor OnStart\n");
    }

    void BatchSpanProcessor::OnEnd(zval *php_span) {
        //php_printf("(c++)BatchSpanProcessor OnEnd\n");
        std::unique_ptr<opentelemetry::sdk::trace::Recordable> r = cpp_processor->MakeRecordable();
        ConvertPhpSpanToRecordable(php_span, r.get());
        cpp_processor->OnEnd(std::move(r));
    }

    std::string BatchSpanProcessor::GetEnvVar(const char* var_name, const std::string& default_value = "") {
        size_t len = strlen(var_name);
        zend_string *value = php_getenv(var_name, len);
        if (value) {
            const char* value_str = ZSTR_VAL(value);
            zend_string_release(value);
            return std::string(value_str);
        } else {
            return default_value;
        }
    }

    void BatchSpanProcessor::ConvertPhpSpanToRecordable(zval *php_span, opentelemetry::sdk::trace::Recordable *recordable) {
        zval span_data;
        zend_call_method_with_0_params(Z_OBJ_P(php_span), Z_OBJCE_P(php_span), NULL, "toSpanData", &span_data);
        assert(Z_TYPE(span_data) == IS_OBJECT);
        zend_class_entry *span_data_ce = Z_OBJCE(span_data);

        //get name
        zval name;
        zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getName", &name);
        assert(Z_TYPE(name) == IS_STRING);
        recordable->SetName(Z_STRVAL(name));
        zval_ptr_dtor(&name);

        //span kind
        zval kind;
        zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getKind", &kind);
        assert(Z_TYPE(kind) == IS_LONG);
        recordable->SetSpanKind(ConvertIntToSpanKind(Z_LVAL(kind)));
        zval_ptr_dtor(&kind);

        //span context
        zval span_context, parent_span_context, trace_id, span_id, trace_flags, parent_span_id;
        zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getContext", &span_context);
        assert(Z_TYPE(span_context) == IS_OBJECT);
        zend_class_entry *span_context_ce = Z_OBJCE(span_context);
        zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getParentContext", &parent_span_context);
        assert(Z_TYPE(parent_span_context) == IS_OBJECT);
        zend_class_entry *parent_span_context_ce = Z_OBJCE(parent_span_context);

        zend_call_method_with_0_params(Z_OBJ_P(&span_context), span_context_ce, NULL, "getTraceId", &trace_id);
        assert(Z_TYPE(trace_id) == IS_STRING);
        zend_call_method_with_0_params(Z_OBJ_P(&span_context), span_context_ce, NULL, "getSpanId", &span_id);
        assert(Z_TYPE(span_id) == IS_STRING);
        zend_call_method_with_0_params(Z_OBJ_P(&span_context), span_context_ce, NULL, "getTraceFlags", &trace_flags);
        assert(Z_TYPE(trace_flags) == IS_LONG);
        zend_call_method_with_0_params(Z_OBJ_P(&parent_span_context), parent_span_context_ce, NULL, "getSpanId", &parent_span_id);
        assert(Z_TYPE(span_id) == IS_STRING);
        zval_ptr_dtor(&span_context);
        zval_ptr_dtor(&parent_span_context);

        uint8_t trace_id_buf[16] = {0};
        uint8_t span_id_buf[8] = {0};
        uint8_t parent_span_id_buf[8] = {0};
        hexStringToBytes(std::string(Z_STRVAL(trace_id), Z_STRLEN(trace_id)), trace_id_buf, 16);
        hexStringToBytes(std::string(Z_STRVAL(span_id), Z_STRLEN(span_id)), span_id_buf, 8);
        hexStringToBytes(std::string(Z_STRVAL(parent_span_id), Z_STRLEN(parent_span_id)), parent_span_id_buf, 8);

        opentelemetry::v1::trace::TraceId cpp_trace_id(trace_id_buf);
        opentelemetry::v1::trace::SpanId cpp_span_id(span_id_buf);
        opentelemetry::v1::trace::SpanId cpp_parent_span_id(parent_span_id_buf);
        opentelemetry::v1::trace::TraceFlags cpp_trace_flags(static_cast<uint8_t>(Z_LVAL(trace_flags)));

        recordable->SetIdentity(
            opentelemetry::v1::trace::SpanContext(cpp_trace_id, cpp_span_id, cpp_trace_flags, true),
            cpp_parent_span_id
        );
        zval_ptr_dtor(&trace_id);
        zval_ptr_dtor(&span_id);
        zval_ptr_dtor(&trace_flags);
        zval_ptr_dtor(&parent_span_id);

        //start + end
        zval start_time, end_time;
        zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getStartEpochNanos", &start_time);
        assert(Z_TYPE(start_time) == IS_LONG);
        std::chrono::system_clock::time_point start_time_point = std::chrono::system_clock::time_point(std::chrono::nanoseconds(Z_LVAL(start_time)));
        recordable->SetStartTime(opentelemetry::v1::common::SystemTimestamp(start_time_point));

        zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getEndEpochNanos", &end_time);
        assert(Z_TYPE(end_time) == IS_LONG);
        std::chrono::system_clock::time_point end_time_point = std::chrono::system_clock::time_point(std::chrono::nanoseconds(Z_LVAL(end_time)));
        recordable->SetDuration(std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_point - start_time_point));
        zval_ptr_dtor(&start_time);
        zval_ptr_dtor(&end_time);

        // status
        zval status, status_code, status_description;
        zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getStatus", &status);
        assert(Z_TYPE(status) == IS_OBJECT);
        zend_class_entry *status_ce = Z_OBJCE(status);
        zend_call_method_with_0_params(Z_OBJ_P(&status), status_ce, NULL, "getCode", &status_code);
        assert(Z_TYPE(status_code) == IS_STRING);
        zend_call_method_with_0_params(Z_OBJ_P(&status), status_ce, NULL, "getDescription", &status_description);
        assert(Z_TYPE(status_description) == IS_STRING);
        opentelemetry::v1::trace::StatusCode cpp_status;
        if (strcmp(Z_STRVAL(status_code), "Ok") == 0) {
            cpp_status = opentelemetry::v1::trace::StatusCode::kOk;
        } else if (strcmp(Z_STRVAL(status_code), "Error") == 0) {
            cpp_status = opentelemetry::v1::trace::StatusCode::kError;
        } else {
            cpp_status = opentelemetry::v1::trace::StatusCode::kUnset;
        }
        recordable->SetStatus(cpp_status, Z_STRVAL(status_description));
        zval_ptr_dtor(&status);
        zval_ptr_dtor(&status_code);
        zval_ptr_dtor(&status_description);

        //instrumentation scope
        // TODO instrumentation scope attributes
        zval scope, scope_name, scope_version, scope_schema_url;
        zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getInstrumentationScope", &scope);
        assert(Z_TYPE(scope) == IS_OBJECT);
        zend_class_entry *scope_ce = Z_OBJCE(scope);
        zend_call_method_with_0_params(Z_OBJ_P(&scope), scope_ce, NULL, "getName", &scope_name);
        assert(Z_TYPE(scope_name) == IS_STRING);
        zend_call_method_with_0_params(Z_OBJ_P(&scope), scope_ce, NULL, "getVersion", &scope_version);
        convert_to_string(&scope_version)
        assert(Z_TYPE(scope_version) == IS_STRING);
        zend_call_method_with_0_params(Z_OBJ_P(&scope), scope_ce, NULL, "getSchemaUrl", &scope_schema_url);
        convert_to_string(&scope_schema_url);
        assert(Z_TYPE(scope_schema_url) == IS_STRING);

        std::stringstream ss;
        ss << Z_STRVAL(scope_name) << "_" << Z_STRVAL(scope_version) << "_" << Z_STRVAL(scope_schema_url);
        std::string scope_key = ss.str();
        if (scope_map.find(scope_key) == scope_map.end()) {
            scope_map[scope_key] = opentelemetry::sdk::instrumentationscope::InstrumentationScope::Create(
                Z_STRVAL(scope_name),
                Z_STRVAL(scope_version),
                Z_STRVAL(scope_schema_url)
            );
        }
        recordable->SetInstrumentationScope(*scope_map[scope_key]);
        zval_ptr_dtor(&scope);
        zval_ptr_dtor(&scope_name);
        zval_ptr_dtor(&scope_version);
        zval_ptr_dtor(&scope_schema_url);

        // resource
        if (cpp_resource == nullptr) {
            zval resource, resource_attributes, resource_schema_url;
            zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getResource", &resource);
            assert(Z_TYPE(resource) == IS_OBJECT);
            zend_call_method_with_0_params(Z_OBJ_P(&resource), Z_OBJCE_P(&resource), NULL, "getAttributes",
                                           &resource_attributes);
            assert(Z_TYPE(resource_attributes) == IS_OBJECT);
            zend_call_method_with_0_params(Z_OBJ_P(&resource), Z_OBJCE_P(&resource), NULL, "getSchemaUrl",
                                           &resource_schema_url);
            convert_to_string(&resource_schema_url);
            assert(Z_TYPE(resource_schema_url) == IS_STRING);
            std::string rsu_str(Z_STRVAL(resource_schema_url), Z_STRLEN(resource_schema_url));

            opentelemetry::sdk::common::AttributeMap attribute_map;
            AddAttributesToMap(&resource_attributes, attribute_map);
            opentelemetry::sdk::resource::Resource custom_resource = opentelemetry::sdk::resource::Resource::Create(attribute_map, rsu_str);

            cpp_resource = std::make_shared<opentelemetry::sdk::resource::Resource>(custom_resource);
            zval_ptr_dtor(&resource);
            zval_ptr_dtor(&resource_attributes);
            zval_ptr_dtor(&resource_schema_url);
        }
        recordable->SetResource(*cpp_resource);

        // attributes
        zval attributes;
        zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getAttributes", &attributes);
        assert(zend_is_iterable(&attributes));
        zval attributes_array;
        zend_call_method_with_0_params(Z_OBJ_P(&attributes), Z_OBJCE_P(&attributes), NULL, "toArray", &attributes_array);
        assert(Z_TYPE(attributes_array) == IS_ARRAY);
        HashTable *ht = Z_ARRVAL(attributes_array);
        zend_string *key;
        zval *value;
        ZEND_HASH_FOREACH_STR_KEY_VAL(ht, key, value) {
            std::string attr_key(ZSTR_VAL(key));
            if (Z_TYPE_P(value) == IS_STRING) {
                std::string attr_value(Z_STRVAL_P(value));
                recordable->SetAttribute(attr_key, attr_value);
            } else if (Z_TYPE_P(value) == IS_LONG) {
                int64_t attr_value = Z_LVAL_P(value);
                recordable->SetAttribute(attr_key, attr_value);
            } else if (Z_TYPE_P(value) == IS_DOUBLE) {
                double attr_value = Z_DVAL_P(value);
                recordable->SetAttribute(attr_key, attr_value);
            } else if (Z_TYPE_P(value) == IS_TRUE || Z_TYPE_P(value) == IS_FALSE) {
                bool attr_value = (Z_TYPE_P(value) == IS_TRUE);
                recordable->SetAttribute(attr_key, attr_value);
            }
        } ZEND_HASH_FOREACH_END();

        zval_ptr_dtor(&attributes_array);
        zval_ptr_dtor(&attributes);

        // events
        zval events;
        zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getEvents", &events);
        assert(zend_is_iterable(&events));
        // get event name, timestamp, and attributes
        zval event_name, event_timestamp, event_attributes;
        HashTable *events_ht = Z_ARRVAL(events);
        zval *event;
        ZEND_HASH_FOREACH_VAL(events_ht, event) {
            //zval event_ce;
            zend_call_method_with_0_params(Z_OBJ_P(event), Z_OBJCE_P(event), NULL, "getName", &event_name);
            assert(Z_TYPE(event_name) == IS_STRING);
            zend_call_method_with_0_params(Z_OBJ_P(event), Z_OBJCE_P(event), NULL, "getEpochNanos", &event_timestamp);
            assert(Z_TYPE(event_timestamp) == IS_LONG);
            zend_call_method_with_0_params(Z_OBJ_P(event), Z_OBJCE_P(event), NULL, "getAttributes", &event_attributes);
            assert(Z_TYPE(event_attributes) == IS_OBJECT);
            //TODO convert attributes to opentelemetry::common::KeyValueIterable
            opentelemetry::common::SystemTimestamp event_ts(std::chrono::system_clock::time_point(std::chrono::nanoseconds(Z_LVAL(event_timestamp))));
            //recordable->AddEvent(Z_STRVAL(event_name), event_ts, event_attributes);
            recordable->AddEvent(Z_STRVAL(event_name), event_ts);
            zval_ptr_dtor(&event_name);
            zval_ptr_dtor(&event_timestamp);
            zval_ptr_dtor(&event_attributes);
        } ZEND_HASH_FOREACH_END();
        zval_ptr_dtor(&events);

        // links
        zval links;
        zend_call_method_with_0_params(Z_OBJ_P(&span_data), span_data_ce, NULL, "getLinks", &links);
        assert(zend_is_iterable(&links));
        // get span context and attributes
        zval link_span_context;//, link_attributes;
        HashTable *links_ht = Z_ARRVAL(links);
        zval *link;
        ZEND_HASH_FOREACH_VAL(links_ht, link)
        {
            zend_call_method_with_0_params(Z_OBJ_P(link), Z_OBJCE_P(link), NULL, "getSpanContext", &link_span_context);
            assert(Z_TYPE(link_span_context) == IS_OBJECT);
            //zend_call_method_with_0_params(Z_OBJ_P(link), Z_OBJCE_P(link), NULL, "getAttributes", &link_attributes);
            //assert(Z_TYPE(link_attributes) == IS_OBJECT);
            opentelemetry::v1::trace::SpanContext cpp_link_span_ctx = ConvertPhpSpanContextToSpanContext(link_span_context);
            recordable->AddLink(cpp_link_span_ctx); //), link_attributes);
            zval_ptr_dtor(&link_span_context);
        } ZEND_HASH_FOREACH_END();
        zval_ptr_dtor(&links);

        zval_ptr_dtor(&span_data);
    }

    opentelemetry::v1::trace::SpanKind BatchSpanProcessor::ConvertIntToSpanKind(int kind) {
        switch (kind)
        {
            case 0:
                return opentelemetry::v1::trace::SpanKind::kInternal;
            case 1:
                return opentelemetry::v1::trace::SpanKind::kClient;
            case 2:
                return opentelemetry::v1::trace::SpanKind::kServer;
            case 3:
                return opentelemetry::v1::trace::SpanKind::kProducer;
            case 4:
                return opentelemetry::v1::trace::SpanKind::kConsumer;
            default:
                return opentelemetry::v1::trace::SpanKind::kInternal;  // Default to internal if unknown
        }
    }

    void BatchSpanProcessor::hexStringToBytes(const std::string &hex_string, uint8_t *out_buffer, size_t buffer_size) {
        size_t len = hex_string.length();
        for (size_t i = 0; i < buffer_size && i * 2 < len; ++i) {
            std::string byte_string = hex_string.substr(i * 2, 2);
            out_buffer[i] = static_cast<uint8_t>(strtol(byte_string.c_str(), nullptr, 16));
        }
    }

    opentelemetry::v1::trace::SpanContext BatchSpanProcessor::ConvertPhpSpanContextToSpanContext(zval &span_context) {
        zval trace_id, span_id, trace_flags, is_remote;
        zend_class_entry *span_context_ce = Z_OBJCE(span_context);

        zend_call_method_with_0_params(Z_OBJ_P(&span_context), span_context_ce, NULL, "getTraceId", &trace_id);
        assert(Z_TYPE(trace_id) == IS_STRING);
        zend_call_method_with_0_params(Z_OBJ_P(&span_context), span_context_ce, NULL, "getSpanId", &span_id);
        assert(Z_TYPE(span_id) == IS_STRING);
        zend_call_method_with_0_params(Z_OBJ_P(&span_context), span_context_ce, NULL, "getTraceFlags", &trace_flags);
        assert(Z_TYPE(trace_flags) == IS_LONG);
        zend_call_method_with_0_params(Z_OBJ_P(&span_context), span_context_ce, NULL, "isRemote", &is_remote);
        assert(Z_TYPE(is_remote) == IS_TRUE || Z_TYPE(is_remote) == IS_FALSE);

        uint8_t trace_id_buf[16] = {0};
        uint8_t span_id_buf[8] = {0};
        hexStringToBytes(std::string(Z_STRVAL(trace_id), Z_STRLEN(trace_id)), trace_id_buf, 16);
        hexStringToBytes(std::string(Z_STRVAL(span_id), Z_STRLEN(span_id)), span_id_buf, 8);

        opentelemetry::v1::trace::TraceId cpp_trace_id(trace_id_buf);
        opentelemetry::v1::trace::SpanId cpp_span_id(span_id_buf);
        opentelemetry::v1::trace::TraceFlags cpp_trace_flags(static_cast<uint8_t>(Z_LVAL(trace_flags)));

        zval_ptr_dtor(&trace_id);
        zval_ptr_dtor(&span_id);
        zval_ptr_dtor(&trace_flags);
        zval_ptr_dtor(&is_remote);

        return opentelemetry::v1::trace::SpanContext(
            cpp_trace_id,
            cpp_span_id,
            cpp_trace_flags,
            (Z_TYPE(is_remote) == IS_TRUE)
        );
    }

    void BatchSpanProcessor::AddAttributesToMap(zval *php_resource, opentelemetry::sdk::common::AttributeMap &attribute_map) {
        zval array;
        zend_call_method_with_0_params(Z_OBJ_P(php_resource), Z_OBJCE_P(php_resource), NULL, "toArray", &array);

        if (Z_TYPE(array) == IS_ARRAY) {
            // Iterate over the array
            HashTable *ht = Z_ARRVAL(array);
            zval *entry;
            zend_string *key;

            ZEND_HASH_FOREACH_STR_KEY_VAL(ht, key, entry)
            {
                if (key) {
                    std::string cpp_key(ZSTR_VAL(key));

                    // Handle different value types
                    switch (Z_TYPE_P(entry)) {
                        case IS_STRING:
                            attribute_map.SetAttribute(cpp_key,
                                                       opentelemetry::common::AttributeValue(Z_STRVAL_P(entry)));
                            break;
                        case IS_LONG:
                            attribute_map.SetAttribute(cpp_key, opentelemetry::common::AttributeValue(
                                    static_cast<int64_t>(Z_LVAL_P(entry))));
                            break;
                        case IS_DOUBLE:
                            attribute_map.SetAttribute(cpp_key, opentelemetry::common::AttributeValue(Z_DVAL_P(entry)));
                            break;
                        case IS_TRUE:
                        case IS_FALSE:
                            attribute_map.SetAttribute(cpp_key, opentelemetry::common::AttributeValue(
                                    Z_TYPE_P(entry) == IS_TRUE));
                            break;
                        default:
                            // Handle other types (arrays, objects, etc.) if needed
                            break;
                    }
                }
            }
            ZEND_HASH_FOREACH_END();

            // Clean up the array zval
            zval_ptr_dtor(&array);
        }
    }
}
