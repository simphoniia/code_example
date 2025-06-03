#pragma once

#include <atomic>

namespace metrics {

enum kEventType { kSuccessRequest, kFailureRequest };

struct RequestMetrics {
  std::atomic<long long> success_requests;
  std::atomic<long long> failure_requests;
};

class Metrics {
public:
  static void IncreaseSuccess() { metrics_.success_requests++; }
  static void IncreaseFailure() { metrics_.failure_requests++; }
  static const RequestMetrics &GetMetrics() { return metrics_; }

private:
  static RequestMetrics metrics_;
};

} // namespace metrics
