--TEST--
Call BatchSpanProcessor::onEnd with a ReadableSpanInterface
--EXTENSIONS--
opentelemetry_sdk
--ENV--
OTEL_TRACES_EXPORTER=console
--FILE--
<?php
use OpenTelemetry\API\Trace\SpanContextInterface;
use OpenTelemetry\API\Trace\TraceStateInterface;
use OpenTelemetry\SDK\Common\Attribute\AttributesInterface;
use OpenTelemetry\SDK\Common\Instrumentation\InstrumentationScopeInterface;
use OpenTelemetry\SDK\Resource\ResourceInfo;
use OpenTelemetry\SDK\Trace\StatusDataInterface;
use OpenTelemetry\SDK\Trace\BatchSpanProcessor;
use OpenTelemetry\SDK\Trace\ReadableSpanInterface;
use OpenTelemetry\SDK\Trace\SpanDataInterface;

$span = new class implements ReadableSpanInterface {
    public function getName(): string {
      return 'foobarbaz';
    }
    public function toSpanData(): SpanDataInterface {
        return new class implements SpanDataInterface {
            public function getName(): string { return 'span-name'; }
            public function getKind(): int { return 1; }
            public function getTraceId(): string { return 'e4a8d4e0d75c0702200af2882cb16c6b'; }
            public function getSpanId(): string { return '46701247e52c2d1b'; }
            public function getParentSpanId(): string { return '5da31fe1c9339c1269966cefd0cbad1a'; }
            public function getStartEpochNanos(): int { return 12345; }
            public function getEndEpochNanos(): int { return 12347; }
            public function getContext(): SpanContextInterface {
                return new class implements SpanContextInterface {
                    public function getTraceId(): string { return 'e4a8d4e0d75c0702200af2882cb16c6b'; }
                    public function getSpanId(): string { return '46701247e52c2d1b'; }
                    public function getTraceFlags(): int { return 0; }
                    public function getTraceState(): ?TraceStateInterface { return null; }
                };
            }
            public function getParentContext(): SpanContextInterface  {
                 return new class implements SpanContextInterface {
                     public function getTraceId(): string { return 'e4a8d4e0d75c0702200af2882cb16c6b'; }
                     public function getSpanId(): string { return '5da31fe1c9339c1269966cefd0cbad1a'; }
                     public function getTraceFlags(): int { return 0; }
                     public function getTraceState(): ?TraceStateInterface { return null; }
                 };
             }
             public function getStatus(): StatusDataInterface {
                return new class implements StatusDataInterface {
                    public function getCode(): string { return 'Ok'; }
                    public function getDescription(): string { return 'ok-description'; }
                };
             }
             public function getInstrumentationScope(): InstrumentationScopeInterface {
                return new class implements InstrumentationScopeInterface {
                    public function getName(): string { return 'instrumentation_scope_name'; }
                    public function getVersion(): ?string { return '0.0.1'; }
                    public function getSchemaUrl(): ?string { return 'http://example.com/schema/'; }
                };
             }
             public function getAttributes(): AttributesInterface {
                return new class implements AttributesInterface, \Traversable {
                    public function has(string $name): bool { return true; }
                    public function get(string $name): mixed { return null; }
                    public function getDroppedAttributesCount(): int { return 0; }
                    public function toArray(): array {
                        return [
                            'foo' => 'foo',
                            'bar' => 'bar',
                            'pi' => 3.14159,
                            'ok' => true,
                        ];
                    }
                };
             }
             public function getResource(): ResourceInfo {
                return new class implements ResourceInfo {
                    public function getSchemaUrl(): ?string { return 'https://example.com/resource/schema'; }
                    public function getAttributes(): AttributesInterface {
                        return new class implements AttributesInterface, \Traversable {

                        };
                    }
                };
             }
        };
    }
};
$bsp = new BatchSpanProcessor();
$bsp->onEnd($span);
$bsp->shutdown();
?>
--EXPECTF--
{
  name          : span-name
  trace_id      : 65346138643465306437356330373032
  span_id       : 3436373031323437
  tracestate    :%s
  parent_span_id: 3564613331666531
  start         : 12345000000000
  duration      : 2000000000
  description   : ok-description
  span kind     : Server
  status        : Ok
  attributes    :%s
  events        :%s
  links         :%s
  resources     :%s
  instr-lib     : instrumentation_scope_name-0.0.1
}
