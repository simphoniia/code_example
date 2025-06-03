#pragma once

#include <string>
#include <unordered_map>

namespace request {

enum kRequestType { kGet, kPost, kPatch, kDelete };

struct Url {
  std::string host;
  std::string path;
  std::string query;
};

class HttpRequest {
  using HeaderMap = std::unordered_map<std::string, std::string>;

public:
  HttpRequest(kRequestType type, Url &&url, HeaderMap &&headers,
              std::string &&body) {
    url_ = std::move(url);
    headers_ = std::move(headers);
    body_ = std::move(body);
  }

  inline const Url &GetUrl() const { return url_; }
  inline const HeaderMap &GetHeaders() const { return headers_; }
  inline const std::string &GetBody() const { return body_; }

  void AddHeader(std::string key, std::string value) {
    headers_.insert({key, value});
  }

private:
  kRequestType type_{};
  HeaderMap headers_;
  std::string body_;
  Url url_;
};

} // namespace request