--TEST--
Create a ContextKey
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
use OpenTelemetry\SDK\Trace\ContextKey;
use OpenTelemetry\SDK\Trace\ContextKeyInterface;

$one = new ContextKey('key_one');
$two = new ContextKey('key_two');
var_dump($one instanceof ContextKeyInterface);
var_dump($one->name());
var_dump($two->name());
unset($one);
unset($two);
?>
--EXPECTF--
bool(true)
string(7) "key_one"
string(7) "key_two"
