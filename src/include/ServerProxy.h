#pragma once

#include <atomic>

class ServerProxy {
public:
  ServerProxy() : enabled_(true) {};
  virtual ~ServerProxy() {};
  virtual void finish() =0;
  virtual void listen() =0;
  virtual std::string get_message() =0;
  virtual void add_message(std::string mes) =0;
  virtual uint32_t queue_len() =0;
  void disable() { enabled_ = false; }
  bool isEnabled() { return enabled_; }

private:
  ServerProxy(const ServerProxy& obj) {};

  std::atomic<bool> enabled_;
};