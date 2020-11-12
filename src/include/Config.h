#pragma once

#include <cstdint>

class Config {
public:
  static constexpr uint8_t ThreadsCount = 19;
  static constexpr const char* ServerPath = "./socket"; // "\0hidden";
};