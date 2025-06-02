#include <format>
#include <iostream>

#include <builder.hpp>
#include <http_codes.hpp>
#include <metrics.hpp>
#include <request.hpp>
#include <view.hpp>

int views::HandleRequest(const request::HttpRequest &request) {
  try {
    auto modules = std::move(builder::GetModules(request));

    for (const auto &module : modules) {
      module->ProcessModule(request);
    }

  } catch (std::exception &ex) {
    std::cerr << std::format(
        "While processing something went wrong {}, returning 500", ex.what());
    metrics::IncreaseMetric(metrics::kEventType::kFailureRequest);
    return http::kInternalServerError;
  }

  metrics::IncreaseMetric(metrics::kEventType::kSuccessRequest);
  return http::kOk;
}
