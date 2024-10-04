--TEST--
Span::storeInContext
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
--FILE--
<?php
use OpenTelemetry\Context\Context;
use OpenTelemetry\Context\ContextKey;
use OpenTelemetry\SDK\Trace\TracerProvider;
use OpenTelemetry\SDK\Trace\Span;

$provider = new TracerProvider();
$tracer = $provider->getTracer('test');

$span = $tracer->spanBuilder("test")->startSpan();
$ctx = $span->storeInContext(Context::getCurrent());
unset($span);
//var_dump($ctx->get(new ContextKey('_span')));

$span = Span::fromContext($ctx);
$span->updateName('updated');
$span->end();

//$scope = Context::storage()->scope();
//$span = Span::fromContext($scope->context());
//$span = Span::fromContext(Context::getCurrent());
?>
--EXPECTF--
{
  name          : updated
  trace_id      : %s
  span_id       : %s
%A
}