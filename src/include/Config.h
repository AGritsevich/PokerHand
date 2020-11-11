#pragma once

#include <cstdint>

class Config {
public:
  static constexpr uint8_t ThreadsCount = 19;
  static constexpr uint8_t ServerPath[] = "./socket"; // "\0hidden";
};