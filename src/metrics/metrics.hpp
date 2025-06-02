#pragma once

#include <atomic>

namespace metrics {

enum kEventType { kSuccessRequest, kFailureRequest };

struct RequestMetrics {
  std::atomic<long long> success_requests;
  std::atomic<long long> failure_requests;
};

void IncreaseMetric(kEventType event) {
  static RequestMetrics metric;

  if (event == kSuccessRequest)
    metric.success_requests++;
  else
    metric.failure_requests++;
}

} // namespace metrics
