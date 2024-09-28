--TEST--
Get a tracer from a provider
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$p = new TracerProvider();
$tracer = $p->getTracer('test');
var_dump($tracer);
unset($tracer);
unset($p);
?>
--EXPECTF--
object(OpenTelemetry\SDK\Trace\Tracer)#%d (0) {
}
