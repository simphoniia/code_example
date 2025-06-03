#include <requester.hpp>

#include <stdexcept>
#include <unordered_set>

namespace {
const std::string kRequesterName = "kRequesterId";

bool AllowRequest(const request::HttpRequest &request) {
  static const std::unordered_set<std::string> allowed_users{
      "User1", "SomeService", "ServiceABC"};

  auto item = request.GetHeaders().find(kRequesterName);

  if (item == request.GetHeaders().end())
    return false;

  return allowed_users.count(item->second);
}

} // namespace

namespace component {

void Requester::PreRequest(request::HttpRequest &request) {
  if (request.GetUrl().path == "/ping")
    return;

  if (AllowRequest(request))
    return;

  throw std::runtime_error("Unknown request user");
}

} // namespace component
