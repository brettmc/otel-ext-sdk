--TEST--
Context store and retrieve a Span
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

$key = new ContextKey('my_span');
$ctx = Context::getCurrent()->with($key, $tracer->spanBuilder("parent")->startSpan());

$span = $ctx->get($key);
var_dump($span);
$span->updateName('updated');
$span->end();
?>
--EXPECTF--
string(28) "OpenTelemetry\SDK\Trace\Span"
{
  name          : updated
  trace_id      : %s
  span_id       : %s
  tracestate    :%s
  parent_span_id: 0000000000000000
  start         : %d
  duration      : %d
%A
}