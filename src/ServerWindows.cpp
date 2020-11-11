#ifndef __linux__ 
#include "ServerWindows.h"
#include "Log.hpp"

void ServerWindows::listen() {
  while (isEnabled()) {
    log::lg << "Not implemented";
  }
};

bool ServerWindows::finish() {
  log::lg << "Not implemented";
};
#endif /* LINUX */