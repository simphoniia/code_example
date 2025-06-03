#pragma once

#include <request.hpp>

namespace modules {

class Module {
public:
  virtual void ProcessModule(const request::HttpRequest &request) = 0;
};

} // namespace modules
