/* opentelemetry_sdk extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_opentelemetry_sdk.h"
#include "opentelemetry_sdk_arginfo.h"
#include "sdk/tracer_provider_class.h"
#include "sdk/tracer_class.h"
#include "sdk/span_class.h"
#include "sdk/span_builder_class.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ void test1() */
PHP_FUNCTION(test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "opentelemetry_sdk");
}
/* }}} */

/* {{{ string test2( [ string $var ] ) */
PHP_FUNCTION(test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

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
    register_span_class();
    register_span_builder_class();
    register_tracer_provider_class();
    register_tracer_class();
    register_class_OpenTelemetry_SDK_Trace_SpanContextInterface();

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
