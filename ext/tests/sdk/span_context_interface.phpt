--TEST--
Create a class implementing SpanContextInterface
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\SpanContextInterface;

$c = new class implements SpanContextInterface
{
    public function getTraceId(): string { return '0000001';}
    public function getSpanId(): string { return '0000002';}
    public function getTraceFlags(): int { return 0;}
    public function isRemote(): bool { return false; }
    public function isSampled(): bool { return false; }
};

var_dump($c);
var_dump($c instanceof SpanContextInterface);
?>
--EXPECTF--
object(OpenTelemetry\SDK\Trace\SpanContextInterface@anonymous)#1 (0) {
}
bool(true)