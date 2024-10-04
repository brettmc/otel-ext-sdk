--TEST--
Call BatchSpanProcessor::onStart
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
--FILE--
<?php
namespace OpenTelemetry\SDK\Trace;

use OpenTelemetry\Context\ContextInterface;
use OpenTelemetry\SDK\Trace\BatchSpanProcessor;
use OpenTelemetry\SDK\Trace\ReadableSpanInterface;
use OpenTelemetry\SDK\Trace\ReadWriteSpanInterface;

$span = new class implements ReadableSpanInterface, ReadWriteSpanInterface {
    public function getName(): string {
      return 'foobarbaz';
    }
    public function toSpanData(): SpanDataInterface {
    }
};
$context = new class implements ContextInterface {};
$bsp = new BatchSpanProcessor();
$bsp->onStart($span, $context);
$bsp->onEnd($span);
$bsp->shutdown();
?>
--EXPECTF--

