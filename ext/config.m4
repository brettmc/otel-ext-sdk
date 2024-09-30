dnl config.m4 for extension opentelemetry_sdk

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([opentelemetry_sdk],
dnl   [for opentelemetry_sdk support],
dnl   [AS_HELP_STRING([--with-opentelemetry_sdk],
dnl     [Include opentelemetry_sdk support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([opentelemetry_sdk],
  [whether to enable opentelemetry_sdk support],
  [AS_HELP_STRING([--enable-opentelemetry_sdk],
    [Enable opentelemetry_sdk support])],
  [no])

if test "$PHP_OPENTELEMETRY_SDK" != "no"; then
  dnl Write more examples of tests here...

    dnl libopentelemetry
    PKG_CHECK_MODULES([OPENTELEMETRY], [opentelemetry_api opentelemetry_trace opentelemetry_common opentelemetry_resources opentelemetry_version opentelemetry_exporter_otlp_http opentelemetry_exporter_ostream >= 1.16])
    LDFLAGS="$LDFLAGS $OPENTELEMETRY_LIBS"

    dnl libprotobuf
    PKG_CHECK_MODULES([PROTOBUF], [protobuf >= 3.21])
    LDFLAGS="$LDFLAGS $PROTOBUF_LIBS"

    dnl libcurl
    PKG_CHECK_MODULES([CURL], [libcurl])
    LDFLAGS="$LDFLAGS $CURL_LIBS"

    CXXFLAGS="-std=c++17 -g"
    PHP_REQUIRE_CXX()
    dnl PHP_CXX_COMPILE_STDCXX(11, mandatory, OPENTELEMETRY_SDK_STDCXX)

  AC_DEFINE(HAVE_OPENTELEMETRY_SDK, 1, [ Have opentelemetry_sdk support ])

  OTEL_SDK_SOURCES=`find $srcdir/sdk -name '*.c*' | sed "s|^$srcdir/||"`

  PHP_NEW_EXTENSION(opentelemetry_sdk, $OTEL_SDK_SOURCES opentelemetry_sdk.c, $ext_shared,, "-g -O0 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-function")
fi
