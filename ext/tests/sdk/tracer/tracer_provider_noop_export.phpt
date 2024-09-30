--TEST--
Use no-op exporter
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=none
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$p = new TracerProvider();
$t = $p->getTracer('test');
$t->spanBuilder('foo')->startSpan()->end();
?>
--EXPECTF--
