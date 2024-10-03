<?php

/**
 * @generate-class-entries
 * @undocumentable
 */

//TODO create an interface in core SDK
/*interface \OpenTelemetry\SDK\Resource\ResourceInfo
{

}*/

namespace OpenTelemetry\API\Trace;

interface SpanContextInterface
{
    public function getTraceId(): string;
    public function getSpanId(): string;
    public function getTraceFlags(): int;
    //public function getTraceState(): ?TraceStateInterface;
}

/*interface \OpenTelemetry\SDK\Common\Attribute\AttributesInterface extends \Traversable, \Countable
{
    public function has(string $name): bool;
    public function get(string $name);
    public function getDroppedAttributesCount(): int;
    public function toArray(): array;
}

interface \OpenTelemetry\SDK\Common\Instrumentation\InstrumentationScopeInterface
{
    public function getName(): string;

    public function getVersion(): ?string;

    public function getSchemaUrl(): ?string;

    public function getAttributes(): \OpenTelemetry\SDK\Common\Attribute\AttributesInterface;
}*/

namespace OpenTelemetry\SDK\Trace;

/*interface StatusDataInterface
{
    public static function ok(): self;
    public static function error(): self;
    public static function unset(): self;
    public function getCode(): string;
    public function getDescription(): string;
}*/

interface SpanDataInterface
{
    public function getName(): string;
    public function getKind(): int;
    public function getContext(): \OpenTelemetry\API\Trace\SpanContextInterface;
    public function getParentContext(): \OpenTelemetry\API\Trace\SpanContextInterface;
    //public function getTraceId(): string;
    //public function getSpanId(): string;
    //public function getParentSpanId(): string;
    //public function getStatus(): StatusDataInterface;
    public function getStartEpochNanos(): int;
    //public function getAttributes(): AttributesInterface;
    //public function getEvents(): array;
    //public function getLinks(): array;
    public function getEndEpochNanos(): int;
    //public function hasEnded(): bool;
    //public function getInstrumentationScope(): InstrumentationScopeInterface;
    //public function getResource(): ResourceInfo;
    //public function getTotalDroppedEvents(): int;
    //public function getTotalDroppedLinks(): int;
}

interface ReadableSpanInterface
{
    public function getName(): string;
    //public function getContext(): mixed;//: API\SpanContextInterface;
    //public function getParentContext(): mixed;//: API\SpanContextInterface;
    //public function getInstrumentationScope(): mixed;//: InstrumentationScopeInterface;
    //public function hasEnded(): bool;
    public function toSpanData(): SpanDataInterface;
    //public function getDuration(): int;
    //public function getKind(): int;
    //public function getAttribute(string $key): mixed;
}

interface SpanProcessorInterface {
    public function onStart(ReadWriteSpanInterface $span, ContextInterface $parentContext): void;
    public function onEnd(ReadableSpanInterface $span): void;
    public function forceFlush(?CancellationInterface $cancellation = null): bool;
    public function shutdown(?CancellationInterface $cancellation = null): bool;
}

class BatchSpanProcessor implements SpanProcessorInterface
{
    public function __construct() {}
    public function onStart(ReadWriteSpanInterface $span, ContextInterface $parentContext): void {}
    public function onEnd(ReadableSpanInterface $span): void {}
    public function forceFlush(?CancellationInterface $cancellation = null): bool {}
    public function shutdown(?CancellationInterface $cancellation = null): bool {}
    public function test(): void {}
}

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
    public function storeInContext(ContextInterface $context): ContextInterface;
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
    public function storeInContext(ContextInterface $context): ContextInterface;
    public static function fromContext(ContextInterface $context): SpanInterface;
    //public static function getInvalid(): SpanInterface;
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

interface TracerProviderInterface
{
    public function getTracer(string $name): Tracer;
}

class TracerProvider implements TracerProviderInterface
{
    public function __construct() {}
    public function __destruct() {}
    public function getTracer(string $name): Tracer {}
    public function forceFlush(): bool {}
    public function shutdown(): bool {}
}

class TracerProviderFactory
{
    public function create(): TracerProviderInterface;
}
