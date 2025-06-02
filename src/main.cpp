#include <engine.hpp>

int main(void) {
  constexpr int kThreadSize = 50;
  engine::RequestManager io(kThreadSize);
  io.Run();

  return 0;
}