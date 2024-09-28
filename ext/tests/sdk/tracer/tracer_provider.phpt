--TEST--
Create a tracer from a provider
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$p = new TracerProvider();
var_dump($p);
unset($p);
?>
--EXPECTF--
object(OpenTelemetry\SDK\Trace\TracerProvider)#%d (0) {
}
