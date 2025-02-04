--TEST--
Export a span not implementing ReadWriteSpanInterface
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
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
        $this->processor->onEnd(new \stdClass());
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
$span = $tracer
    ->spanBuilder('test-span')
    ->startSpan();
try {
    $span->end();
} catch (InvalidArgumentException $e) {
    var_dump(get_class($e));
    var_dump($e->getMessage());
}
?>
--EXPECTF--
string(24) "InvalidArgumentException"
string(47) "$span does not implement ReadWriteSpanInterface"