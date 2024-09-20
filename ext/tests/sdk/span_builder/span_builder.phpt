--TEST--
Get a span builder
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$provider = new TracerProvider();
$tracer = $provider->getTracer('test');
$builder = $tracer->spanBuilder("test-span");
var_dump($builder);
$builder
    ->setSpanKind(1);
$span = $builder->startSpan();
var_dump($span);
$span->end();
?>
--EXPECTF--
object(OpenTelemetry\SDK\Trace\SpanBuilder)#%d (0) {
}
object(OpenTelemetry\SDK\Trace\Span)#%d (0) {
}
{
  name          : test-span
  trace_id      : %s
  span_id       : %s
  tracestate    :%s
  parent_span_id: 0000000000000000
  start         : %d
  duration      : %d
  description   :%s
  span kind     : Server
  status        : Unset
  attributes    :%s
  events        :%s
  links         :%s
  resources     :%s
	service.name: unknown_service
	telemetry.sdk.version: %d.%d.%d
	telemetry.sdk.name: ext-opentelemetry
	telemetry.sdk.language: php
  instr-lib     : foo
}