<?php
require __DIR__ . '/vendor/autoload.php';

putenv('OTEL_EXPORTER_OTLP_ENDPOINT=http://collector:4318');
putenv('OTEL_EXPORTER_OTLP_PROTOCOL=http/protobuf');
putenv('OTEL_EXPORTER_OTLP_TIMEOUT=1500'); //1.5s
$factory = new \OpenTelemetry\SDK\Trace\TracerProviderFactory();
$tracerProvider = $factory->create();

$tracer = $tracerProvider->getTracer('io.opentelemetry.contrib.php');

$rootSpan = $tracer->spanBuilder('root')->startSpan();
$scope = $rootSpan->activate();

//because the root span is active, each of the following spans will be parented to the root span
try {
    $spans = [];
    for ($i = 1; $i <= 4; $i++) {
        $spans[] = $tracer->spanBuilder('http-' . $i)
            //@see https://github.com/open-telemetry/opentelemetry-collector/blob/main/model/semconv/v1.6.1/trace.go#L834
            ->setAttribute('http.method', 'GET')
            ->setAttribute('http.url', 'example.com/' . $i)
            ->setAttribute('http.status_code', 200)
            ->setAttribute('http.response_content_length', 1024)
            ->startSpan();
    }
    /** @psalm-suppress ArgumentTypeCoercion */
    foreach ($spans as $span) {
        usleep((int) (0.3 * 1e6));
        $span->end();
    }
} finally {
    $scope->detach();
    $rootSpan->end();
}

$tracerProvider->shutdown();