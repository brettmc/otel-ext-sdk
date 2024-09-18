--TEST--
Activate a span
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$provider = new TracerProvider();
$tracer = $provider->getTracer('test');

$parent = $tracer->spanBuilder("parent")->startSpan();
$scope = $parent->activate();

$child = $tracer->spanBuilder('child')->startSpan();
//todo assert child's parent
$child->end();

$parent->end();
$scope->detach();
$tracer->spanBuilder("another-root")->startSpan()->end();
?>
--EXPECTF--
{
  name          : child
  trace_id      : %s
  span_id       : %s
  tracestate    :%s
  parent_span_id: %s
  start         : %d
  duration      : %d
  description   :%s
  span kind     : Internal
  status        : Unset
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
{
  name          : parent
  trace_id      : %s
  span_id       : %s
  tracestate    :%s
  parent_span_id: 0000000000000000
  start         : %d
  duration      : %d
  description   :%s
  span kind     : Internal
  status        : Unset
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
{
  name          : another-root
  trace_id      : %s
  span_id       : %s
  tracestate    :%s
  parent_span_id: 0000000000000000
  start         : %d
  duration      : %d
  description   :%s
  span kind     : Internal
  status        : Unset
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