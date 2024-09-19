--TEST--
Add resource attributes from env
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_SPAN_EXPORTER=console
OTEL_RESOURCE_ATTRIBUTES=attr_one=foo,attr_two=99
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$p = new TracerProvider();
$t = $p->getTracer('test');
$t->spanBuilder('foo')->startSpan()->end();
?>
--EXPECTF--
{
  name          : foo
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
	attr_one: foo
	attr_two: 99
	telemetry.sdk.version: %d.%d.%d
	telemetry.sdk.name: ext-opentelemetry
	telemetry.sdk.language: php
  instr-lib     : foo
}
