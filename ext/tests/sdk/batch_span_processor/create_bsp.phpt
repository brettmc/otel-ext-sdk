--TEST--
Create a BatchSpanProcessor
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\BatchSpanProcessor;

$bsp = new BatchSpanProcessor();
var_dump($bsp);
var_dump($bsp->forceFlush());
var_dump($bsp->shutdown());
unset($bsp);
?>
--EXPECT--
object(OpenTelemetry\SDK\Trace\BatchSpanProcessor)#1 (0) {
}
bool(true)
bool(true)
