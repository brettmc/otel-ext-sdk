--TEST--
Context store and retrieve a SpanContext
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
--FILE--
<?php
use OpenTelemetry\SDK\Trace\SpanInterface;
use OpenTelemetry\SDK\Trace\Context;
use OpenTelemetry\SDK\Trace\ContextKey;
use OpenTelemetry\SDK\Trace\TracerProvider;

$provider = new TracerProvider();
$tracer = $provider->getTracer('test');

$key = new ContextKey('my_span_context');
$span = $tracer->spanBuilder("span")->startSpan();
$spanId = $span->getContext()->getSpanId();
$ctx = Context::getCurrent()->with($key, $span->getContext());
$spanContext = $ctx->get($key);
var_dump(get_class($spanContext));
assert($spanId === $spanContext->getSpanId());
?>
--EXPECTF--
string(35) "OpenTelemetry\SDK\Trace\SpanContext"
{
  name          : span
  trace_id      : %s
  span_id       : %s
  tracestate    :%s
  parent_span_id: %d
  start         : %d
  duration      : %d
%A
}