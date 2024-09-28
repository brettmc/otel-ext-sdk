--TEST--
Get SpanContext from a span
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
--FILE--
<?php
use OpenTelemetry\SDK\Trace\Context;
use OpenTelemetry\SDK\Trace\TracerProvider;

$provider = new TracerProvider();
$tracer = $provider->getTracer('test');

$span = $tracer->spanBuilder("test")->startSpan();
$span->storeInContext(Context::getCurrent());
unset($span);

//$scope = Context::storage()->scope();
//$span = Span::fromContext($scope->context());
$span = Span::fromContext(Context::getCurrent());
?>
--EXPECTF--
foo