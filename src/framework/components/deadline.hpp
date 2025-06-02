#pragma once

#include <component.hpp>

namespace component {

class Deadline : public component::Component {
public:
  virtual void PreRequest(request::HttpRequest &request) override;
  virtual void PostRequest(request::HttpRequest &request) override {}
};

} // namespace component
