#ifdef __linux__ 

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>

#include "Log.hpp"
#include "ServerLinux.h"
#include "Config.h"

ServerLinux::ServerLinux(std::string adress) {
  if (socket(AF_UNIX, SOCK_STREAM, 0) == -1) {
    log::lg << "Fail create socket";
    throw std::string("Fail create socket\n");
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, Config::ServerPath , sizeof(Config::ServerPath));

  if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    log::lg << "Fail bind";
    throw std::string("Fail bind");
  }

  messages_threads_.reset(new std::thread(ServerLinux::listen, nullptr, 0));

}

ServerLinux::~ServerLinux() {
  disable();

  if (messages_threads_->joinable()) {
    messages_threads_->join();
  }
}

auto ServerLinux::queue_len() {
  std::unique_lock<std::mutex> lock(messages_lock_);
  return messages_.size();
}

void ServerLinux::listen() {
  std::array<uint8_t, 100> buf;

  if (listen(fd, 5) == -1) {
    log::lg << "Fail listen";
    throw std::string("Fail listen");
  }

  while (isEnabled()) {
    int32_t cl = 0;
    std::string mes;
    if ((cl = accept(fd, NULL, NULL)) == -1) {
      log::lg << "Warning attept accept was unsuccesful";
      continue;
    }

    while ((rc = read(cl, buf.data(), data.size())) > 0) {
      mes += std::string(buf.data, data.size());
      log::lg << "read " << rc << "bytes: " << buf;
    }

    if (rc == -1) {
      log::lg << "Fail read accepted message";
      throw("Fail read accepted message");
    }
    else if (rc == 0) {
      log::lg << "Info: EOF";
      add_message(mes);
      close(cl);
    }
  }
}

void ServerLinux::add_message(std::string message) {
  std::unique_lock<std::mutex> lock(messages_lock_);

  messages_.emplace(message);
  cv_messages_.notify_one();
}

std::string ServerLinux::get_message() {
  std::unique_lock<std::mutex> lock(messages_lock_);

  if (!queue_len()) cv_messages_.wait(lock);

  auto copy_mess = messages_.front();
  messages_.pop();
  return copy_mess;
}

#endif /* LINUX */
