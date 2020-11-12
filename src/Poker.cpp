#include <iostream>
#include <string>
#include <deque>
#include <memory>
#include <thread>

#include "Log.h"
#include "PockerHand.h"
#include "ServerWindows.h"
#include "ServerLinux.h"


int main(int argc, char* argv[]) {
  try{
    std::unique_ptr<ServerProxy> server;
    PockerHand hand;
    std::deque<std::unique_ptr<std::thread>> list;

#ifndef __linux__ // win
    server.reset(new ServerWindows());
#else // linux
    server.reset(new ServerLinux());
#endif /* __linux__ */

    lg.print(std::string("Start server"));

    while (1) {
      auto request = server->get_message(); // sleep & wait here

      list.emplace_back(std::unique_ptr<std::thread>((new std::thread(&PockerHand::proceed, request, hand))));
    }
  }
  catch (std::string what) {
    std::cout << what << std::endl;
    lg.print(std::string("Start fail with: ") + what);
  }
  
}
