--TEST--
Create a TracerProvider from factory
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProviderFactory;

$p = (new TracerProviderFactory())->create();
var_dump($p);
unset($p);
?>
--EXPECTF--
object(OpenTelemetry\SDK\Trace\TracerProvider)#%d (0) {
}
