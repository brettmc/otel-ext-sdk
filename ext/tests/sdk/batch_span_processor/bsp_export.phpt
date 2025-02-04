--TEST--
Export a span from PHP via BatchSpanProcessor
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
--FILE--
<?php
use OpenTelemetry\SDK\Resource\ResourceInfoFactory;
use OpenTelemetry\SDK\Trace\BatchSpanProcessor;
use OpenTelemetry\SDK\Trace\TracerProvider;

use OpenTelemetry\API\Trace\SpanContext;
use OpenTelemetry\API\Trace\SpanKind;
use OpenTelemetry\API\Trace\StatusCode;

require_once dirname(__DIR__, 2) . '/vendor/autoload.php';

$processor = new BatchSpanProcessor();
$tracerProvider = TracerProvider::builder()
    ->addSpanProcessor($processor)
    ->build();

$tracer = $tracerProvider->getTracer('test', '1.0.0', 'https://my-schema', ['foo' => 'bar']);
$span = $tracer
    ->spanBuilder('test-span')
    ->setSpanKind(SpanKind::KIND_SERVER)
    ->startSpan();
$span->setAttribute('baz', 'bat');
$span->addEvent('test-event', ['event-attr' => 'event-value']);
$ctx = SpanContext::createFromRemoteParent('2e896fdf56f27218ef7aefe41a56ddb1', 'a7535e6a3bb65fa2');
$span->addLink($ctx, ['link-attr' => 'link-value']);
$span->setStatus(StatusCode::STATUS_OK, 'all is well');
$span->end();
$tracerProvider->shutdown();

?>
--EXPECTF--
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
  status        : Ok
  attributes    :%s
	baz: bat
  events        :%s
	{
	  name          : test-event
	  timestamp     : %d
	  attributes    :%s
	}
  links         :%s
	{
	  trace_id      : 2e896fdf56f27218ef7aefe41a56ddb1
	  span_id       : a7535e6a3bb65fa2
	  tracestate    :%s
	  attributes    :%s
	}
  resources     :%s
	service.version: 1.0.0+no-version-set
	telemetry.sdk.language: php
	host.arch: %s
	os.description: %s
	process.executable.path: %s
	telemetry.sdk.version: %s
	os.version: %s
	process.command: %s
	process.pid: %d
	process.owner: %s
	host.name: %s
	os.type: linux
	process.runtime.name: cli
	os.name: Linux
	process.runtime.version: %s
	service.name: __root__
	telemetry.sdk.name: opentelemetry
  instr-lib     : test-1.0.0
}
