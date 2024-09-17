--TEST--
Update a span after it is created and before it ends
--EXTENSIONS--
opentelemetry_sdk
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
	telemetry.sdk.version: 1.16.1
	telemetry.sdk.language: php
	service.version: 0.0.1
	telemetry.sdk.name: opentelemetry
	service.instance.id: instance-1
	service.namespace: foo
	service.name: my-service
  instr-lib     : foo
}