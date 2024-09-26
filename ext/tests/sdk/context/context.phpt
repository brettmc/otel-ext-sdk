--TEST--
Get current context
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

$ctx_two = $ctx_one->with($key, 'value');
var_dump($ctx_two->get($key));
var_dump($ctx_one->get($key));
?>
--EXPECTF--
string(7) "key_one"
string(5) "value"
NULL
