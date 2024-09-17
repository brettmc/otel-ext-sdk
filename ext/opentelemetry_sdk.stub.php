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

interface SpanInterface
{
    public function updateName(string $name): SpanInterface;
    public function setStatus(string $code, ?string $description = null): SpanInterface;
    public function end(?int $endTimestamp = null): void;
    //public function recordException(Throwable $exception, iterable $attributes = []): SpanInterface;
    //public function addEvent(string $name, iterable $attributes = [], ?int $timestamp = null): SpanInterface;
    //public function addLink(SpanContextInterface $context, iterable $attributes = []): SpanInterface;
    //public function setAttributes(iterable $attributes): SpanInterface;
    //public function setAttribute(string $key, bool|int|float|string|array|null $value): SpanInterface;
    //public function isRecording(): bool;
    //public function getContext(): SpanContextInterface;
}

class Span implements SpanInterface
{
    public function updateName(string $name): SpanInterface {}
    public function setStatus(string $code, ?string $description = null): SpanInterface {}
    public function end(?int $endTimestamp = null): void {}
    //public function addLink(SpanContextInterface $context, iterable $attribute = []): SpanInterface
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
