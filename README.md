# otel-ext-sdk
Prototype OpenTelemetry extension Batch Span Processor using opentelemetry-cpp

# Why?

Implementing a minimal Batch Span Processor, which wraps the opentelemetry-cpp SDK, to compare performance with the native PHP implementation.

- asynchronous exporting of spans (eg spand will export during a PHP `sleep()` call)
- uses libprotobuf and libgrpc instead of the PHP extensions
- possibly more performant exporting than native PHP implementation

# Requirements

- libprotobuf + headers
- libgrpc + headers
- libcurl + headers
- libopentelemetry + headers (see dockerfile)
- build-essential etc

# How it works

- PHP stubs generated as normal: see `openteleemtry_sdk.stub.php`
- C files (usually 1 per PHP class) to implement classes/methods: `sdk/php/*`
- C++ classes provide a wrapper around opentelemetry-cpp functionality: `sdk/cpp/*`
- `sdk_manager.cpp` provides a bunch of `extern C` functions which interface between C and C++
- custom object storage defined in `sdk/php/*.h` extends PHP structures with an opaque pointer to a C++ class (eg otel_trace_SDK (opaque) -> otel_trace::SDK)
- sdk_manager handles reinterpreting casts between opaque pointers and C++ classes

# TODOs

- gracefully handle invalid OTEL_BSP_* env var values

# Demo

```shell
docker run --rm -it -v $(pwd)/ext/demo:/app composer:latest update
```

# Benchmark

Using hyperfine to test startup + export:
`OTEL_TRACES_EXPORTER=otlp OTEL_EXPORTER_OTLP_ENDPOINT=http://collector:4318 hyperfine --runs 10 'php -d extension=opentelemetry_sdk tests/bench/otlp_export.php 10'`