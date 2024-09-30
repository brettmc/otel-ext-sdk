--TEST--
Configure batch span processor
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
OTEL_PHP_TRACES_PROCESSOR=batch
OTEL_BSP_MAX_QUEUE_SIZE=20
OTEL_BSP_SCHEDULE_DELAY=500
OTEL_BSP_MAX_EXPORT_BATCH_SIZE=10
--FILE--
<?php
use OpenTelemetry\SDK\Trace\TracerProvider;

$p = new TracerProvider();
$t = $p->getTracer('test');
$s = $t->spanBuilder('test')->startSpan()->end();
/**
 * note that the console output is printed in the middle of the 600ms var_dump,
 * which is the first thing to happen after 500ms delay has passed.
 */
var_dump('going to sleep');
foreach (range(1, 7, 1) as $i) {
  var_dump("usleep {$i}00ms");
  usleep(100000); //100ms
}
?>
--EXPECTF--
string(14) "going to sleep"
string(12) "usleep 100ms"
string(12) "usleep 200ms"
string(12) "usleep 300ms"
string(12) "usleep 400ms"
string(12) "usleep 500ms"
string(12) "{
  name          : test
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
	telemetry.sdk.version: 0.1.0
	telemetry.sdk.name: ext-opentelemetry
	telemetry.sdk.language: php
  instr-lib     : foo
}
usleep 600ms"
string(12) "usleep 700ms"