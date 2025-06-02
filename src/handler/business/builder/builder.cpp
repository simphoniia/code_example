#include <builder.hpp>

#include <format>
#include <stdexcept>

namespace builder {

namespace {

constexpr std::string_view kModuleKey = "modules";

std::optional<modules::kModulesType> ResolveFromString(const std::string &str) {
  std::unordered_map<std::string, modules::kModulesType> module_lists{
      {"offer", modules::kModulesType::kOffer},
      {"buy", modules::kModulesType::kBuy},
      {"image", modules::kModulesType::kImage},
      {"price", modules::kModulesType::kPrice},
      {"profile", modules::kModulesType::kProfile},
      {"recomm", modules::kModulesType::kRecommendations},
      {"user", modules::kModulesType::kUser},
  };

  auto item = module_lists.find(str);

  if (item == module_lists.end())
    return std::nullopt;

  return item->second;
}

std::string GetType(const std::string &str, size_t offset) {
  std::string buffer;
  while (offset < str.size() && std::isalpha(str[offset])) {
    buffer.push_back(str[offset]);
    ++offset;
  }
  return buffer;
}

} // namespace

std::vector<std::unique_ptr<modules::Module>>
GetModulesPtrs(const request::HttpRequest &request) {
  // modules in url `some=val?modules=a,b,c?some=val`

  const std::string &query = request.GetUrl().query;
  size_t offset = query.find(kModuleKey);

  if (offset == std::string::npos)
    return {};

  offset += kModuleKey.size();

  std::vector<std::unique_ptr<modules::Module>> modules;
  while (offset < query.size()) {
    if (offset == '?')
      break;

    std::string value = std::move(GetType(query, offset));
    offset += value.size();

    auto module_type = ResolveFromString(value);
    if (!module_type.has_value())
      throw std::runtime_error(std::format(
          "Unknown format in request = {}, current_value = {}", query, value));

    modules.emplace_back(std::move(GetItemPtr(module_type.value())));
  }
}

} // namespace builder
