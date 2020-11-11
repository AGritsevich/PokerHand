#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <fstream>
#include <ctime>
#include <chrono>

namespace log {
  class Log {
  public:
    Log()
      : enabled_(true) {
      using std::chrono::system_clock;
      system_clock::time_point today = system_clock::now();
      std::time_t tt = system_clock::to_time_t(today);
      std::string file_name = "pocker_" + ctime(&tt) + ".log";
      file_.open(file_name, std::ofstream::out | std::ofstream::app);
      safe_thread_.reset(new std::thread(&Log::proceed, this));
    }

    ~Log() {
      disable();

      if (safe_thread_->joinable()) {
        safe_thread_->join();
      }
    }
    //template<typename T>
    //friend Log& operator<<(Log& l, const T& s);
    friend Log& operator<<(Log& l, const std::string& s);

    //void enable() { enabled_. };
    void disable() { 
      enabled_ = false;
      cv_queue_.notify_all();
    };

  private:
    void add_message(const std::string& message) {
      std::unique_lock<std::mutex> lock(queue_lock_);
      queue_.emplace(message);
      cv_queue_.notify_one();
    };

    std::string get_message() {
      std::unique_lock<std::mutex> lock(queue_lock_);
      auto copy_mess = queue_.front();
      queue_.pop();
      return copy_mess;
    };

    auto queue_len() {
      std::unique_lock<std::mutex> lock(queue_lock_);
      return queue_.size();
    }

    void proceed() {
      while (enabled_) {
        std::unique_lock<std::mutex> lock(queue_lock_);
        file_ << get_message() << std::endl;

        if (!queue_len()) cv_queue_.wait(lock);
      }
    }

  private:
    std::queue<std::string> queue_;
    std::unique_ptr<std::thread> safe_thread_;
    std::atomic<bool> enabled_;
    std::mutex queue_lock_;
    std::condition_variable cv_queue_;
    std::ofstream file_;
  };

  //template<typename T>
  Log& operator<<(Log& l, const std::string& s) {
    //l.file_ << s << "\n";
    l.add_message(s);
    return l;
  }

  static constexpr log::Log lg; // TODO
} // namespace log
