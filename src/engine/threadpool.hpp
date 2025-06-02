#pragma once

#include <atomic>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

namespace engine {

class ThreadPool {
public:
  ThreadPool(size_t thread_size);
  ~ThreadPool();

  template <typename Func, typename... Args>
  void AddJob(Func func, Args &&...args) {
    tasks_.emplace(std::async(std::launch::deferred, func, args...));
  }

private:
  bool to_work_{};
  size_t thread_size_{};
  std::queue<std::future<void>> tasks_;
  std::vector<std::thread> pool_;

  std::atomic<long long> task_counter_{};
  std::mutex mutex;

  void Run();
  void OnStop();
};

} // namespace engine
