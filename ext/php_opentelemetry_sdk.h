/* opentelemetry_sdk extension for PHP */

#ifndef PHP_OPENTELEMETRY_SDK_H
# define PHP_OPENTELEMETRY_SDK_H

extern zend_module_entry opentelemetry_sdk_module_entry;
# define phpext_opentelemetry_sdk_ptr &opentelemetry_sdk_module_entry

# define PHP_OPENTELEMETRY_SDK_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_OPENTELEMETRY_SDK)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_OPENTELEMETRY_SDK_H */
