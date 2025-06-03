#pragma once

#include <component.hpp>

namespace component {

class Requester : public component::Component {
public:
  std::string_view kName = "requester";

  virtual void PreRequest(request::HttpRequest &request) override;
  virtual void PostRequest(request::HttpRequest &request) override {}
};

} // namespace component
