#pragma once

#include <optional>
#include <unordered_map>

#include <creater.hpp>
#include <deadline.hpp>
#include <engine.hpp>
#include <view.hpp>

namespace {

void PrepareComponents(
    std::vector<std::unique_ptr<component::Component>> &components,
    std::vector<component::kComponentTypes> &&list) {
  components = std::move(component::CreateComponents(std::move(list)));
}

void ReadSocket(
    std::vector<std::unique_ptr<component::Component>> &components) {
  std::string buffer;
  buffer.reserve(256);
  /*
    boost::asio::async_read(socket, response, [&](const system::error_code&
    ec){});
  */
  auto request = CreateHttpRequest(std::move(buffer));
  AcceptRequest(std::move(request), components);
}

request::HttpRequest &&CreateHttpRequest(std::string &&buffer) {
  request::Url url;
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

  ResponseRequest(return_code);
}

void ResponseRequest(int response_code) {
  std::string response =
      std::format("HTTP/1.1 {} {}\r\n\r\n"
                  "<html>\r\n"
                  "<body>\r\n"
                  "<h1>Hello, World!</h1>\r\n"
                  "</body>\r\n"
                  "</html>\r\n\r\n",
                  response_code, response_code == 200 ? "OK" : "FAILURE");

  /*
    boost::asio::async_write(socket, response, [&](const system::error_code&
    ec){});
  */
}

} // namespace

namespace engine {

void RequestManager::Run() {
  PrepareComponents(components_, {component::kDeadline, component::kRequester});
  // Work with sockets (boost asio or something)

  while (true) {
    // Some message from socket
    pool_.AddJob(ReadSocket, components_);
  }
}

} // namespace engine
