--TEST--
Configure an invalid exporter
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=foo_exporter
--FILE--
<?php
try {
    $processor = new \OpenTelemetry\Ext\SDK\Trace\BatchSpanProcessor();
} catch (\InvalidArgumentException $e) {
    var_dump($e->getMessage());
}
?>
--EXPECTF--
string(28) "Invalid OTEL_TRACES_EXPORTER"