--TEST--
Get SpanContext from a span
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$provider = new TracerProvider();
$tracer = $provider->getTracer('test');

$span = $tracer->spanBuilder("test")->startSpan();
$context = $span->getContext();
var_dump($context->getTraceId());
var_dump($context->getSpanId());
var_dump($context->getTraceFlags());
var_dump($context->isRemote());
var_dump($context->isSampled());
$span->end();
?>
--EXPECTF--
string(32) "%s"
string(16) "%s"
int(1)
bool(false)
bool(true)
%A