#pragma once
#ifdef __linux__

#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <memory>

#include "ServerProxy.h"

class ServerLinux : public ServerProxy {
public:
  ServerLinux() =default;

  void listen() override;
  void finish() override {};
  std::string get_message();
  void add_message(std::string mes);
  auto queue_len();

private:
  std::queue<std::string> messages_;
  std::mutex messages_lock_;
  std::condition_variable cv_messages_;
  std::unique_ptr<std::thread> messages_threads_;
};
#endif /* LINUX */