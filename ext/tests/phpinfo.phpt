--TEST--
Check phpinfo output
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
phpinfo(INFO_MODULES);
?>
--EXPECTF--
%A
opentelemetry_sdk

opentelemetry_sdk support => enabled
extension version => %d.%d.%d%S
opentelemetry-cpp version => %d.%d.%d
%A