#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <thread>

#include "Types.h"

class PockerHand {
public:
  PockerHand() = delete;
  PockerHand(const PockerHand&) = delete;
  PockerHand(const std::string& req );
  ~PockerHand() {};

  void proceed(std::string message);
  bool isFlush(const types::Hand& one);
  bool isStraight(types::Hand& one);
  void disable();
  inline bool is_enabled() const { return enabled_; };

private:
  std::atomic<bool> enabled_;
  std::unique_ptr<std::thread> thread_;
};
