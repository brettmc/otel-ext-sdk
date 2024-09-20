--TEST--
Update a span after it is created and before it ends
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
$span = $builder->startSpan();
$span
    ->updateName('updated-name')
    ->setStatus('Ok', 'status-description');
$span->end();
?>
--EXPECTF--
{
  name          : updated-name
  trace_id      : %s
  span_id       : %s
  tracestate    :%s
  parent_span_id: 0000000000000000
  start         : %d
  duration      : %d
  description   :%s
  span kind     : Internal
  status        : Ok
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