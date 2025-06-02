#include <engine.hpp>

int main(void) {
  constexpr int kThreadSize = 50;
  engine::RequestManager manager(kThreadSize);
  manager.Run();

  return 0;
}