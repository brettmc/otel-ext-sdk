--TEST--
Get a span builder
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$provider = new TracerProvider();
$tracer = $provider->getTracer('test');
$builder = $tracer->spanBuilder("test-span");
var_dump($builder);
$builder
    ->setSpanKind(1);
$builder->test();
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
	telemetry.sdk.version: 1.16.1
	telemetry.sdk.language: php
	service.version: 0.0.1
	telemetry.sdk.name: opentelemetry
	service.instance.id: instance-1
	service.namespace: foo
	service.name: my-service
  instr-lib     : foo
}