#pragma once

#include <queue>

#include <component.hpp>
#include <request.hpp>
#include <threadpool.hpp>

namespace engine {

class RequestManager {
public:
  RequestManager(size_t thread_size) : pool_(thread_size) {}
  void Run(std::vector<component::kComponentTypes> &&component_list);

private:
  std::queue<request::HttpRequest> requests_;
  ThreadPool pool_;
  std::vector<std::unique_ptr<component::Component>> components_;
};

} // namespace engine
