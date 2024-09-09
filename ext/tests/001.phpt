--TEST--
Check if opentelemetry_sdk is loaded
--EXTENSIONS--
opentelemetry_sdk
--FILE--
<?php
echo 'The extension "opentelemetry_sdk" is available';
?>
--EXPECT--
The extension "opentelemetry_sdk" is available
