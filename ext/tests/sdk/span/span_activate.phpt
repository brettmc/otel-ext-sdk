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
	service.name: unknown_service
	telemetry.sdk.version: %d.%d.%d
	telemetry.sdk.name: ext-opentelemetry
	telemetry.sdk.language: php
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
	service.name: unknown_service
	telemetry.sdk.version: %d.%d.%d
	telemetry.sdk.name: ext-opentelemetry
	telemetry.sdk.language: php
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
	service.name: unknown_service
	telemetry.sdk.version: %d.%d.%d
	telemetry.sdk.name: ext-opentelemetry
	telemetry.sdk.language: php
  instr-lib     : foo
}