<?php

/**
 * @generate-class-entries
 * @undocumentable
 */
namespace OpenTelemetry\Ext\SDK\Trace;

class BatchSpanProcessor
{
    public function __construct() {}
    public function onStart(object $span, object $context): void {}
    public function onEnd(object $span): void {}
    public function forceFlush(?object $cancellation = null): bool {}
    public function shutdown(?object $cancellation = null): bool {}
}
