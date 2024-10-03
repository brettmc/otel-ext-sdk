--TEST--
Create a BatchSpanProcessor
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
--FILE--
<?php
use OpenTelemetry\SDK\Trace\BatchSpanProcessor;

$bsp = new BatchSpanProcessor();
$bsp->test();
?>
--EXPECT--
object(OpenTelemetry\SDK\Trace\BatchSpanProcessor)#1 (0) {
}
bool(true)
bool(true)
