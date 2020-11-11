#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <thread>
#include "Log.hpp"
#include "PockerHand.h"
#include "ServerWindows.h"
#include "ServerLinux.h"


int main(int argc, char* argv[]) {
  try{
    std::unique_ptr<ServerProxy> server;
    PockerHand hand;

#ifndef __linux__ // win
    server.reset(new ServerWindows());
#else // linux
    server.reset(new ServerLinux());
#endif /* __linux__ */

    log::lg << "Start server";

    std::list<std:unique_ptr> list;

    while (1) {
      auto request = server->get_message(); // sleep & wait here

      list.emplace_back(std::unique_ptr<std::thread>(PockerHand::proceed, request, hand));
    }
  }
  catch (std::string what) {
    std::cout << what << std::endl;
  }
  
}
