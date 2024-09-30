# otel-ext-sdk
prototype OpenTelemetry extension SDK using opentelemetry-cpp

# Requirements

- libprotobuf + development headers 
- libcurl + development headers
- build-essential etc

Note that currently I've just copied the most recent tag of opentelemetry-cpp into `third_party`, but eventually
it should use a pre-built `libopentelemetry`

# How it works

- PHP stubs generated as normal: see `openteleemtry_sdk.stub.php`
- C files (usually 1 per PHP class: `sdk/php/*`
- C++ classes provide a wrapper around opentelemetry-cpp functionality: `sdk/cpp/*`
- sdk_manager.c/.h provides a bunch of `extern C` functions which interface between C/C++
- custom object storage defined in `sdk/php/*.h` extends PHP structures with an opaque pointer to a C++ class
- sdk_manager handles reinterpreting casts between opaque pointers and C++ classes

# TODOs

- compile opentelemetry-cpp to libopentelemetry shared object and development headers, and implement in `config.m4` as a shared lib
  - exists in alpine packages, but I couldn't install it
- couple of memory leaks reported

# Benchmark

Using hyperfine to test startup + export)
`OTEL_TRACES_EXPORTER=otlp OTEL_EXPORTER_OTLP_ENDPOINT=http://collector:4318 hyperfine --runs 10 'php -d extension=opentelemetry_sdk tests/bench/otlp_export.php 10'`