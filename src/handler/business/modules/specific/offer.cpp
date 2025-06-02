#include <offer.hpp>

#include <format>
#include <optional>
#include <stdexcept>

#include <module_interface.hpp>

namespace {

constexpr std::string_view kItemIdKey = "item_id";

std::optional<std::string> GetItemIdFromQuery(const std::string &query) {
  size_t offset = query.find(kItemIdKey);

  if (offset == std::string::npos)
    return std::nullopt;

  offset += kItemIdKey.size();

  std::string buffer;
  while (offset < query.size() && std::isdigit(query[offset])) {
    buffer.push_back(query[offset]);
    ++offset;
  }

  return buffer;
}

} // namespace

namespace modules {

void Offer::ProcessModule(const request::HttpRequest &request) {
  const auto &query = request.GetUrl().query;
  auto item_id = GetItemIdFromQuery(query);

  if (!item_id.has_value())
    throw std::runtime_error("No item id in url");

  try {
    stats_.item_id = std::stoll(item_id.value());
  } catch (...) {
    throw std::runtime_error(std::format(
        "Invalid item id in request. Request {}", request.GetUrl().query));
  }

  // Try extract value of item in shop
  // Like `SELECT count FROM item_count WHERE id == item_id_
  int item_count = 9999;
  stats_.available = (item_count > 0);
}

} // namespace modules
