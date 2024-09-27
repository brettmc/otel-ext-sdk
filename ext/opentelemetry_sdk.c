/* opentelemetry_sdk extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_opentelemetry_sdk.h"
#include "opentelemetry_sdk_arginfo.h"
#include "sdk/php/tracer_provider_class.h"
#include "sdk/php/tracer_class.h"
#include "sdk/php/span_class.h"
#include "sdk/php/scope_class.h"
#include "sdk/php/context_class.h"
#include "sdk/php/span_context_class.h"
#include "sdk/php/span_builder_class.h"
#include <opentelemetry/version.h>

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

PHP_INI_BEGIN()
PHP_INI_END()

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(opentelemetry_sdk)
{
#if defined(ZTS) && defined(COMPILE_DL_OPENTELEMETRY_SDK)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

PHP_MINIT_FUNCTION(opentelemetry_sdk) {
    REGISTER_INI_ENTRIES();
    register_scope_class();
    register_span_class();
    register_span_builder_class();
    register_tracer_provider_class();
    register_tracer_class();
    register_span_context_class();
    register_context_class();

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(opentelemetry_sdk) {
    UNREGISTER_INI_ENTRIES();

    return SUCCESS;
}

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(opentelemetry_sdk)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "opentelemetry_sdk support", "enabled");
    php_info_print_table_row(2, "extension version", PHP_OPENTELEMETRY_SDK_VERSION);
    php_info_print_table_row(2, "opentelemetry-cpp version", OPENTELEMETRY_VERSION);
	php_info_print_table_end();
}
/* }}} */

/* {{{ opentelemetry_sdk_module_entry */
zend_module_entry opentelemetry_sdk_module_entry = {
	STANDARD_MODULE_HEADER,
	"opentelemetry_sdk",					/* Extension name */
	NULL,					/* zend_function_entry */
	PHP_MINIT(opentelemetry_sdk),							/* PHP_MINIT - Module initialization */
	PHP_MSHUTDOWN(opentelemetry_sdk),							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(opentelemetry_sdk),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(opentelemetry_sdk),			/* PHP_MINFO - Module info */
	PHP_OPENTELEMETRY_SDK_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_OPENTELEMETRY_SDK
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(opentelemetry_sdk)
#endif
