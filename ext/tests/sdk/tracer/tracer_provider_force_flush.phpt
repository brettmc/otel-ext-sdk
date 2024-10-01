--TEST--
TracerProvider forceFlush/Shutdown
--EXTENSIONS--
opentelemetry_sdk
--INI--

--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProviderFactory;

$p = (new TracerProviderFactory())->create();
var_dump($p->forceFlush());
var_dump($p->shutdown());
?>
--EXPECT--
bool(true)
bool(true)