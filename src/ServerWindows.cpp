#ifndef __linux__ 
#include "ServerWindows.h"
#include "Log.h"

ServerWindows::ServerWindows() {
  lg.print("ServerWindows::ServerWindows: Not implemented");
}

ServerWindows::~ServerWindows() {
  lg.print("ServerWindows::~ServerWindows: Not implemented");
}

std::string ServerWindows::get_message() {
  lg.print("ServerWindows::get_message: Not implemented");
  return "Not implemented";
}


void ServerWindows::add_message(std::string mes) {
  lg.print("ServerWindows::add_message: Not implemented");
}

uint32_t ServerWindows::queue_len() {
  lg.print("ServerWindows::queue_len: Not implemented");
  return 0;
}

void ServerWindows::listen() {
  while (isEnabled()) {
    lg.print("ServerWindows::listen: Not implemented");
  }
}

void ServerWindows::finish() {
  lg.print("ServerWindows::finish: Not implemented");
}
#endif /* WINDOWS */