--TEST--
Create a tracer from a provider
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
OTEL_PHP_TRACES_PROCESSOR=batch
OTEL_BSP_MAX_QUEUE_SIZE=20
OTEL_BSP_SCHEDULE_DELAY=3000
OTEL_BSP_MAX_EXPORT_BATCH_SIZE=10
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$p = new TracerProvider();
var_dump($p);
?>
--EXPECTF--
object(OpenTelemetry\SDK\Trace\TracerProvider)#%d (0) {
}