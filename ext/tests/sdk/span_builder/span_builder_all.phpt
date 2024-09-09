--TEST--
Span builder with the kitchen sink
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;
$provider = new TracerProvider();
$tracer = $provider->getTracer('phpt-test');
$builder = $tracer->spanBuilder('phpt-test-span');
$builder
    ->setSpanKind(4) //consumer
    ->setStartTimestamp(999)
    ->setAttributes([
        'a_one' => 'v_one',
        'a_two' => true,
        'a_three' => false,
        'a_four' => 99,
        'a_five' => 1.234,
    ])
    ->setAttribute('foo', 'bar')
    ->setAttribute('count', 2)
    ->setAttribute('pi', 3.14159)
    ->setAttribute('bool_true', true)
    ->setAttribute('bool_false', false)
    ;
$span = $builder->startSpan();
$span->end();
?>
--EXPECTF--
{
  name          : phpt-test-span
  trace_id      : %s
  span_id       : %s
  tracestate    :%s
  parent_span_id: 0000000000000000
  start         : 999
  duration      : %d
  description   :%s
  span kind     : Consumer
  status        : Unset
  attributes    :%s
	pi: 3.14159
	foo: bar
	count: 2
	bool_true: 1
	bool_false: 0
	a_three: 0
	a_two: 1
	a_one: v_one
	a_four: 99
	a_five: 1.234
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