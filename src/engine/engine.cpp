#pragma once

#include <optional>
#include <unordered_map>

#include <deadline.hpp>
#include <engine.hpp>
#include <view.hpp>

namespace {

std::optional<std::unique_ptr<component::Component>>
CreateComponentByName(std::string name) {
  if (name == "deadline")
    return std::unique_ptr<component::Deadline>();
  // else if (anothers...)
  else
    return std::nullopt;
}

void PrepareComponents(
    std::vector<std::unique_ptr<component::Component>> &components,
    std::vector<std::string> list) {
  for (auto &to_create : list) {
    auto created_component = CreateComponentByName(to_create);
    if (created_component.has_value())
      components.push_back(created_component.value());
  }
}

void ReadSocket(
    std::vector<std::unique_ptr<component::Component>> &components) {
  std::string buffer; // = ReadSocket(...);
  auto request = CreateHttpRequest(std::move(buffer));
  AcceptRequest(std::move(request), components);
}

request::HttpRequest &&CreateHttpRequest(std::string &&buffer) {
  request::Url url;
  url.host = "localhost";
  url.path = "/some/handler/in/my/service";
  url.query = "?blocks=a,b,c?something=else?";
  request::HttpRequest request(request::kRequestType::kGet, std::move(url), {},
                               "request-body");
  return request;
}

void AcceptRequest(
    request::HttpRequest &&request,
    std::vector<std::unique_ptr<component::Component>> &components) {
  for (const auto &component : components) {
    component->PreRequest(request);
  }

  int return_code = views::HandleRequest(request);

  for (const auto &component : components) {
    component->PostRequest(request);
  }

  // answer to client with return_code and some body
}

} // namespace

namespace engine {

void RequestManager::Run() {
  PrepareComponents(components_, {"deadline"});
  // Work with sockets (boost asio or something)
  while (true) {
    // Some message from socket
    pool_.AddJob(ReadSocket, components_);
  }
}

} // namespace engine
