<?php

declare(strict_types=1);

namespace OpenTelemetry\SDK\Trace;

use OpenTelemetry\API\Behavior\LogsMessagesTrait;
use OpenTelemetry\SDK\Sdk;

final class TracerProviderFactory
{
    use LogsMessagesTrait;

    public function __construct(
        private readonly ExporterFactory $exporterFactory = new ExporterFactory(),
        private readonly SamplerFactory $samplerFactory = new SamplerFactory(),
        private readonly SpanProcessorFactory $spanProcessorFactory = new SpanProcessorFactory(),
    ) {
    }

    public function create(): TracerProviderInterface
    {
        if (Sdk::isDisabled()) {
            return new NoopTracerProvider();
        }

        try {
            $sampler = $this->samplerFactory->create();
        } catch (\Throwable $t) {
            self::logWarning('Unable to create sampler', ['exception' => $t]);
            $sampler = null;
        }

        if (extension_loaded('opentelemetry_sdk')) {
            $spanProcessor = new BatchSpanProcessor();
            return new TracerProvider($spanProcessor, $sampler);
        }

        try {
            $exporter = $this->exporterFactory->create();
        } catch (\Throwable $t) {
            self::logWarning('Unable to create exporter', ['exception' => $t]);
            $exporter = null;
        }

        try {
            $spanProcessor = $this->spanProcessorFactory->create($exporter);
        } catch (\Throwable $t) {
            self::logWarning('Unable to create span processor', ['exception' => $t]);
            $spanProcessor = null;
        }

        return new TracerProvider(
            $spanProcessor,
            $sampler,
        );
    }
}
