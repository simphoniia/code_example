#pragma once

#include <request.hpp>

namespace component {

enum kComponentTypes { kDeadline, kRequester };

std::string ResovleComponentName(kComponentTypes type) {
  switch (type) {
  case kDeadline:
    return "deadline";
  case kRequester:
    return "requester";
  }
  return "";
}

class Component {
public:
  virtual void PreRequest(request::HttpRequest &request) = 0;
  virtual void PostRequest(request::HttpRequest &request) = 0;
};

}; // namespace component