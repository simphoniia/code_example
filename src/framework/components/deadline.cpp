#include <deadline.hpp>

#include <unordered_map>

namespace {
const std::unordered_map<std::string, std::string> kDefaultHeadersValue{
    {"kDefaultDeadlineKey", "200"},
    {"kAnotherKey", "500"},
    {"kMaxServices", "3"}};

void FillEmptyKeys(request::HttpRequest &request) {
  for (const auto &header : kDefaultHeadersValue) {
    if (request.GetHeaders().count(header.first) == 0) {
      request.AddHeader(header.first, header.second);
    }
  }
}
} // namespace

namespace component {

void Deadline::PreRequest(request::HttpRequest &request) {
  if (request.GetUrl().path == "/ping")
    return;

  FillEmptyKeys(request);
}

} // namespace component
