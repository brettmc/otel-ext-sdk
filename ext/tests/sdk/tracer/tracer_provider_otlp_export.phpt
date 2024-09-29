--TEST--
otlp/http export
--EXTENSIONS--
opentelemetry_sdk
--SKIPIF--
<?php if (true) die("Skipped: otlp/http export requires an endpoint."); ?>
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

