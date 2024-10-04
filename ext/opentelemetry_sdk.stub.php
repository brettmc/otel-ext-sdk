<?php

/**
 * @generate-class-entries
 * @undocumentable
 */

/*interface \OpenTelemetry\SDK\Resource\ResourceInfo
{
}*/

namespace OpenTelemetry\Context;

interface ContextInterface
{
    public static function getCurrent(): ContextInterface;
    public function activate(): ScopeInterface;
    public function with(ContextKeyInterface $key, mixed $value): ContextInterface;
    public function get(ContextKeyInterface $key): mixed;
}

namespace OpenTelemetry\API\Trace;

interface TraceStateInterface
{
    //public function with(string $key, string $value): TraceStateInterface;
    //public function without(string $key): TraceStateInterface;
    //public function get(string $key): ?string;
    //public function getListMemberCount(): int;
    //public function toString(?int $limit = null): string;
    public function __toString(): string;
}

interface SpanContextInterface
{
    public function getTraceId(): string;
    public function getSpanId(): string;
    public function getTraceFlags(): int;
    public function getTraceState(): ?TraceStateInterface;
}

namespace OpenTelemetry\SDK\Common\Attribute;

interface AttributesInterface extends \Traversable, \Countable
{
    public function has(string $name): bool;
    public function get(string $name): mixed; //todo??
    public function getDroppedAttributesCount(): int;
    public function toArray(): array;
}

namespace OpenTelemetry\SDK\Common\Future;

interface CancellationInterface
{
    public function subscribe(\Closure $callback): string;
    public function unsubscribe(string $id): void;
}

namespace OpenTelemetry\SDK\Common\Instrumentation;

interface InstrumentationScopeInterface
{
    public function getName(): string;
    public function getVersion(): ?string;
    public function getSchemaUrl(): ?string;
    //public function getAttributes(): \OpenTelemetry\SDK\Common\Attribute\AttributesInterface;
}

namespace OpenTelemetry\SDK\Trace;

interface StatusDataInterface
{
    //public static function ok(): StatusDataInterface;
    //public static function error(): StatusDataInterface;
    //public static function unset(): StatusDataInterface;
    public function getCode(): string;
    public function getDescription(): string;
}

interface SpanDataInterface
{
    public function getName(): string;
    public function getKind(): int;
    public function getContext(): \OpenTelemetry\API\Trace\SpanContextInterface;
    public function getParentContext(): \OpenTelemetry\API\Trace\SpanContextInterface;
    //public function getTraceId(): string;
    //public function getSpanId(): string;
    //public function getParentSpanId(): string;
    public function getStatus(): StatusDataInterface;
    public function getStartEpochNanos(): int;
    //public function getAttributes(): AttributesInterface;
    //public function getEvents(): array;
    //public function getLinks(): array;
    public function getEndEpochNanos(): int;
    //public function hasEnded(): bool;
    public function getInstrumentationScope(): \OpenTelemetry\SDK\Common\Instrumentation\InstrumentationScopeInterface;
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

//TODO should also extend SpanInterface
interface ReadWriteSpanInterface extends ReadableSpanInterface {}

interface SpanProcessorInterface {
    public function onStart(ReadWriteSpanInterface $span, \OpenTelemetry\Context\ContextInterface $parentContext): void;
    public function onEnd(ReadableSpanInterface $span): void;
    public function forceFlush(?\OpenTelemetry\SDK\Common\Future\CancellationInterface $cancellation = null): bool;
    public function shutdown(?\OpenTelemetry\SDK\Common\Future\CancellationInterface $cancellation = null): bool;
}

class BatchSpanProcessor implements SpanProcessorInterface
{
    public function __construct() {}
    public function onStart(ReadWriteSpanInterface $span, \OpenTelemetry\Context\ContextInterface $parentContext): void {}
    public function onEnd(ReadableSpanInterface $span): void {}
    public function forceFlush(?\OpenTelemetry\SDK\Common\Future\CancellationInterface $cancellation = null): bool {}
    public function shutdown(?\OpenTelemetry\SDK\Common\Future\CancellationInterface $cancellation = null): bool {}
}
