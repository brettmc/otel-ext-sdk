--TEST--
Create a tracer from a provider
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=otlp
OTEL_EXPORTER_OTLP_ENDPOINT=http://collector:4318
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$p = new TracerProvider();
$t = $p->getTracer('test');
$t->spanBuilder('foo')->startSpan()->end();
?>
--XFAIL--
Does not work if collector unavailable
--EXPECTF--

