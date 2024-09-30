--TEST--
Get a span builder
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=none
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$provider = new TracerProvider();
$tracer = $provider->getTracer('test');
$spans = [];
for ($i=0; $i<10; $i++) {
  $spans[] = $tracer->spanBuilder("test-span-{$i}")->startSpan();
}
foreach ($spans as $span) {
    $span->end();
}
?>
--EXPECT--
