<?php

/**
 * @generate-class-entries
 * @undocumentable
 */

namespace OpenTelemetry\SDK\Trace;

interface ScopeInterface
{
    public function detach(): int;
}

class Scope implements ScopeInterface
{
    public function detach(): int {}
}

interface ContextKeyInterface
{
}

class ContextKey implements ContextKeyInterface
{
    public function __construct(private readonly ?string $name = null) {}
    public function __destruct() {}
    public function name(): ?string {}
}

class Context implements ContextInterface
{
    public static function getCurrent(): ContextInterface {}
    public function activate(): ScopeInterface {}
    public function with(ContextKeyInterface $key, mixed $value): ContextInterface {}
    public function get(ContextKeyInterface $key): mixed {}
}

interface ContextInterface
{
    public static function getCurrent(): ContextInterface;
    public function activate(): ScopeInterface;
    public function with(ContextKeyInterface $key, mixed $value): ContextInterface;
    public function get(ContextKeyInterface $key): mixed;
}

interface SpanContextInterface
{
    public function getTraceId(): string;
    public function getSpanId(): string;
    public function getTraceFlags(): int;
    public function isRemote(): bool;
    public function isSampled(): bool;
}

class SpanContext implements SpanContextInterface
{
    public function getTraceId(): string {}
    public function getSpanId(): string {}
    public function getTraceFlags(): int {}
    public function isRemote(): bool {}
    public function isSampled(): bool {}
}

interface SpanInterface
{
    public function activate(): ScopeInterface;
    //public function storeInContext(ContextInterface $context): ContextInterface;
    public function updateName(string $name): SpanInterface;
    public function setStatus(string $code, ?string $description = null): SpanInterface;
    public function end(?int $endTimestamp = null): void;
    //public function recordException(Throwable $exception, iterable $attributes = []): SpanInterface;
    //public function addEvent(string $name, iterable $attributes = [], ?int $timestamp = null): SpanInterface;
    //public function addLink(SpanContextInterface $context, iterable $attributes = []): SpanInterface;
    //public function setAttributes(iterable $attributes): SpanInterface;
    //public function setAttribute(string $key, bool|int|float|string|array|null $value): SpanInterface;
    //public function isRecording(): bool;
    public function getContext(): SpanContextInterface;
}

class Span implements SpanInterface
{
    public function updateName(string $name): SpanInterface {}
    public function setStatus(string $code, ?string $description = null): SpanInterface {}
    public function end(?int $endTimestamp = null): void {}
    //public function addLink(SpanContextInterface $context, iterable $attribute = []): SpanInterface
    public function activate(): ScopeInterface {}
    public function getContext(): SpanContextInterface {}
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
