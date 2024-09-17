<?php

/**
 * @generate-class-entries
 * @undocumentable
 */

namespace OpenTelemetry\SDK\Trace;

/*class Scope
{
    public function detach(): void {}
}*/

interface SpanContextInterface
{
    public function getTraceId(): string;
    public function getSpanId(): string;
    public function getTraceFlags(): int;
    public function isRemote(): bool;
    public function isSampled(): bool;
}

class Span
{
    public function end(): void {}
    //public function activate(): Scope {}
}

class SpanBuilder
{
    public function setAttribute(string $key, mixed $value): SpanBuilder {}
    public function setAttributes(iterable $attributes): SpanBuilder {}
    public function setSpanKind(int $spanKind): SpanBuilder {}
    public function setStartTimestamp(int $timestamp): SpanBuilder {}
    public function setParent(): SpanBuilder {}
    public function addLink(SpanContextInterface $context, iterable $attributes = []): SpanBuilder {}
    public function startSpan(): Span {}
}

class Tracer
{
    public function spanBuilder(string $spanName): SpanBuilder {}
}

class TracerProvider
{
    public function __construct() {}
    public function __destruct() {}
    public function getTracer(string $name): Tracer {}
}
