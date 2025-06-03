#include <threadpool.hpp>

namespace {

bool ToRelax(const std::queue<std::future<void>> &tasks) {
  if (tasks.empty()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return true;
  }
  return false;
}

} // namespace

namespace engine {

ThreadPool::ThreadPool(size_t thread_size) : thread_size_{thread_size} {
  for (size_t i = 0; i < thread_size; ++i) {
    pool_.emplace_back(std::thread(&ThreadPool::Run, this));
  }
}

ThreadPool::~ThreadPool() {
  OnStop();

  while (pool_.size()) {
    auto &thread = pool_.back();
    if (thread.joinable()) {
      thread.join();
      pool_.pop_back();
    }
  }
}

void ThreadPool::Run() {
  while (to_work_) {
    if (ToRelax(tasks_))
      continue;

    if (!mutex_.try_lock())
      continue;

    auto task = std::move(tasks_.front());
    tasks_.pop();
    mutex_.unlock();

    task_counter_++;
    task.get();
  }
}

void ThreadPool::OnStop() { to_work_ = false; }

} // namespace engine
