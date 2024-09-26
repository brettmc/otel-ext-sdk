--TEST--
Context store and retrieve a Span
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=none
--FILE--
<?php
use OpenTelemetry\SDK\Trace\SpanInterface;
use OpenTelemetry\SDK\Trace\Context;
use OpenTelemetry\SDK\Trace\ContextKey;
use OpenTelemetry\SDK\Trace\TracerProvider;

$provider = new TracerProvider();
$tracer = $provider->getTracer('test');

$key = new ContextKey('my_span');
$ctx = Context::getCurrent()->with($key, $tracer->spanBuilder("parent")->startSpan());

$span = $ctx->get($key);
var_dump(get_class($span));
$span->updateName('updated');
$span->end();
?>
--EXPECT--
string(28) "OpenTelemetry\SDK\Trace\Span"