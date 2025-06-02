#pragma once

#include <request.hpp>

namespace component {

class Component {
public:
  virtual void PreRequest(request::HttpRequest &request) = 0;
  virtual void PostRequest(request::HttpRequest &request) = 0;
};

}; // namespace component