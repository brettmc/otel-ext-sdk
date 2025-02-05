--TEST--
Configure an invalid exporter
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=otlp
OTEL_EXPORTER_OTLP_PROTOCOL=foo-protocol
--FILE--
<?php
try {
    $processor = new \OpenTelemetry\Ext\SDK\Trace\BatchSpanProcessor();
} catch (\InvalidArgumentException $e) {
    var_dump($e->getMessage());
}
?>
--EXPECTF--
string(35) "Invalid OTEL_EXPORTER_OTLP_PROTOCOL"