#ifdef __linux__ 

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>

#include "Log.h"
#include "ServerLinux.h"
#include "Config.h"

ServerLinux::ServerLinux() {
  if (socket_fd_ = socket(AF_UNIX, SOCK_STREAM, 0) == -1) {
    lg.print("Fail create socket");
    throw std::string("Fail create socket\n");
  }

  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, Config::ServerPath , sizeof(Config::ServerPath));

  if (bind(socket_fd_, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    lg.print("Fail bind");
    throw std::string("Fail bind");
  }

  messages_threads_.reset(new std::thread(&ServerLinux::listen, this));
  messages_threads_->join();

}

ServerLinux::~ServerLinux() {
  disable();

  if (messages_threads_->joinable()) {
    messages_threads_->join();
  }
}

uint32_t ServerLinux::queue_len() {
  std::unique_lock<std::mutex> lock(messages_lock_);
  return messages_.size();
}

void ServerLinux::listen() {
  std::array<uint8_t, 100> buf;

  if (::listen(socket_fd_, 5) == -1) {
    lg.print("Fail listen");
    throw std::string("Fail listen");
  }

  while (isEnabled()) {
    int32_t cl = 0;
    std::string mes;
    if ((cl = accept(socket_fd_, NULL, NULL)) == -1) {
      lg.print("Warning attept accept was unsuccesful");
      continue;
    }
    
    uint32_t rc = 0;
    while ((rc = read(cl, buf.data(), buf.size())) > 0) {
      mes += std::string((const char*)buf.data(), buf.size());
    }

    if (rc == -1) {
      lg.print("Fail read accepted message");
      throw("Fail read accepted message");
    }
    else if (rc == 0) {
      lg.print("Info: EOF");
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

  std::string copy_mess = messages_.front();
  messages_.pop();
  return copy_mess;
}

#endif /* LINUX */
