--TEST--
Configure an invalid exporter
--XFAIL--
Non-numeric values for OTEL_BSP_* are not handled correctly
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_BSP_MAX_EXPORT_BATCH_SIZE=foo
--FILE--
<?php
try {
    $processor = new \OpenTelemetry\Ext\SDK\Trace\BatchSpanProcessor();
} catch (\InvalidArgumentException $e) {
    var_dump($e->getMessage());
}
?>
--EXPECTF--
string(33) "Invalid OTEL_BSP_MAX_EXPORT_BATCH_SIZE"