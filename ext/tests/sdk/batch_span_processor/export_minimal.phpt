--TEST--
Export a span from PHP via BatchSpanProcessor
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
OTEL_PHP_DETECTORS=sdk
--FILE--
<?php
use OpenTelemetry\SDK\Resource\ResourceInfoFactory;
use OpenTelemetry\Ext\SDK\Trace\BatchSpanProcessor;
use OpenTelemetry\SDK\Trace\TracerProvider;
use OpenTelemetry\SDK\Trace\SpanProcessorInterface;
use OpenTelemetry\SDK\Trace\ReadableSpanInterface;
use OpenTelemetry\SDK\Common\Future\CancellationInterface;
use OpenTelemetry\SDK\Trace\ReadWriteSpanInterface;
use OpenTelemetry\Context\ContextInterface;

use OpenTelemetry\API\Trace\SpanContext;
use OpenTelemetry\API\Trace\SpanKind;
use OpenTelemetry\API\Trace\StatusCode;

require_once dirname(__DIR__, 2) . '/vendor/autoload.php';

$processor = new BatchSpanProcessor();
$wrapper = new class($processor) implements SpanProcessorInterface {
    public function __construct(private readonly BatchSpanProcessor $processor){}
    public function onStart(ReadWriteSpanInterface $span, ContextInterface $parentContext): void {
        $this->processor->onStart($span, $parentContext);
    }
    public function onEnd(ReadableSpanInterface $span): void {
        $this->processor->onEnd($span);
    }
    public function shutdown(?CancellationInterface $cancellation = null): bool {
        return $this->processor->shutdown($cancellation);
    }
    public function forceFlush(?CancellationInterface $cancellation = null): bool {
        return $this->processor->forceFlush($cancellation);
    }
};
$tracerProvider = TracerProvider::builder()
    ->addSpanProcessor($wrapper)
    ->build();

$tracer = $tracerProvider->getTracer('test');
$tracer->spanBuilder('test-span')->startSpan()->end();
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
  span kind     : Internal
  status        : Unset
  attributes    :%s
  events        :%s
  links         :%s
  resources     :%s
	service.name: unknown_service
	telemetry.sdk.version: %s
	telemetry.sdk.language: php
	telemetry.sdk.name: opentelemetry
  instr-lib     : test
}
