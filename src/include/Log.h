#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <fstream>
#include <ctime>
#include <chrono>

class Log {
public:
  Log();
  ~Log();
  inline void print(const std::string& ll);
  void disable();

private:
  void add_message(const std::string& message);
  std::string get_message();
  auto queue_len();
  void proceed();

private:
  std::queue<std::string> queue_;
  std::unique_ptr<std::thread> safe_thread_;
  std::atomic<bool> enabled_;
  std::mutex queue_lock_;
  std::condition_variable cv_queue_;
  std::ofstream file_;
};

static Log lg;
