#include "Log.h"

#include <ctime>
#include <chrono>

Log lg;

Log::Log()
  : enabled_(true) {
  using std::chrono::system_clock;
  system_clock::time_point today = system_clock::now();
  std::time_t tt = system_clock::to_time_t(today);
  std::string file_name = "pocker_" + *ctime(&tt); // TODO ctime to ctime_s
  file_name += ".log";
  file_.open(file_name, std::ofstream::out | std::ofstream::app);
  //safe_thread_.reset(new std::thread(&Log::proceed, this));
  //safe_thread_->join();
}

Log::~Log() {
  disable();

  if (safe_thread_->joinable()) {
    safe_thread_->join();
  }
}

void Log::print(const std::string& ll) {
  add_message(ll);
}

void Log::disable() {
  enabled_ = false;
  cv_queue_.notify_all();
};

void Log::add_message(const std::string& message) {
  std::unique_lock<std::mutex> lock(queue_lock_);
  queue_.emplace(message);
  cv_queue_.notify_one();
};

std::string Log::get_message() {
  std::unique_lock<std::mutex> lock(queue_lock_);
  std::string copy_mess = queue_.front();
  queue_.pop();
  return copy_mess;
};

auto Log::queue_len() {
  std::unique_lock<std::mutex> lock(queue_lock_);
  return queue_.size();
}

void Log::proceed() {
  while (enabled_) {
    std::unique_lock<std::mutex> lock(queue_lock_);
    file_ << get_message() << std::endl;

    if (!queue_len()) cv_queue_.wait(lock);
  }
}
