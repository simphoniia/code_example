#pragma once

#include <random>

namespace utils {
class Randomizer {
public:
  Randomizer() {
    std::random_device device;
    random_generator_.seed(device());
  }

  int GetRandom(int max) {
    std::uniform_int_distribution<int> range(0, max);
    return range(random_generator_);
  }

private:
  std::mt19937 random_generator_;
};
} // namespace utils