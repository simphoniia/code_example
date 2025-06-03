#pragma once

#include <memory>

#include <deadline.hpp>
#include <requester.hpp>

namespace {
std::unique_ptr<component::Component>
GetComponentByType(component::kComponentTypes type) {
  switch (type) {
  case component::kDeadline:
    return std::unique_ptr<component::Deadline>(new component::Deadline());
  case component::kRequester:
    return std::unique_ptr<component::Requester>(new component::Requester());
  }
}
} // namespace

namespace component {
std::vector<std::unique_ptr<component::Component>>
CreateComponents(std::vector<kComponentTypes> types) {
  std::vector<std::unique_ptr<component::Component>> components;

  for (kComponentTypes type : types) {
    components.emplace_back(std::move(GetComponentByType(type)));
  }

  return components;
}
} // namespace component