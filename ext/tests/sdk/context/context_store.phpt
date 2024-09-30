--TEST--
Context stores supported types
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\Context;
use OpenTelemetry\SDK\Trace\ContextKey;
use OpenTelemetry\SDK\Trace\ContextKeyInterface;

$key = new ContextKey('key_one');
var_dump(Context::getCurrent()->with($key, 99)->get($key));
var_dump(Context::getCurrent()->with($key, 3.14159)->get($key));
var_dump(Context::getCurrent()->with($key, true)->get($key));
var_dump(Context::getCurrent()->with($key, false)->get($key));
//TODO also should handle Span, SpanContext, Baggage
try {
    var_dump(Context::getCurrent()->with($key, NULL)->get($key));
} catch (\Exception $e) {
    var_dump($e->getMessage());
}
?>
--EXPECT--
int(99)
float(3.14159)
bool(true)
bool(false)
string(30) "Unsupported Context value type"