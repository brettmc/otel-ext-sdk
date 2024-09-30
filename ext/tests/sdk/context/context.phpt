--TEST--
Context values stored in new context and not current
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\Context;
use OpenTelemetry\SDK\Trace\ContextKey;
use OpenTelemetry\SDK\Trace\ContextKeyInterface;

$key = new ContextKey('key_one');
var_dump($key->name());
$ctx_one = Context::getCurrent();

$ctx_two = $ctx_one->with($key, 12345);
var_dump($ctx_two->get($key));
var_dump($ctx_one->get($key));
?>
--EXPECT--
string(7) "key_one"
int(12345)
NULL