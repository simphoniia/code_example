#pragma once

#include <memory>
#include <optional>

#include <module_interface.hpp>
#include <offer.hpp>
#include <request.hpp>
#include <types.hpp>

namespace builder {

std::optional<std::unique_ptr<modules::Module>> &&
GetItemPtr(modules::kModulesType type) {
  switch (type) {
  case modules::kModulesType::kOffer:
    return std::unique_ptr<modules::Offer>(new modules::Offer());
  case modules::kModulesType::kBuy:
    return std::nullopt;
  case modules::kModulesType::kImage:
    return std::nullopt;
  case modules::kModulesType::kPrice:
    return std::nullopt;
  case modules::kModulesType::kProfile:
    return std::nullopt;
  case modules::kModulesType::kRecommendations:
    return std::nullopt;
  case modules::kModulesType::kUser:
    return std::nullopt;
  }
}

std::vector<std::unique_ptr<modules::Module>>
GetModulesPtrs(const request::HttpRequest &request);

} // namespace builder
