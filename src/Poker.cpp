#include <iostream>
#include <string>
#include <array>
#include <future>

#include "Log.h"
#include "Config.h"
#include "PockerHand.h"
#include "ServerWindows.h"
#include "ServerLinux.h"


int main(int argc, char* argv[]) {
  try{
    std::unique_ptr<ServerProxy> server;
    std::array<std::unique_ptr<PockerHand>, Config::ThreadsCount> collection;

#ifndef __linux__ // win
    server.reset(new ServerWindows());
#else // linux
    server.reset(new ServerLinux());
#endif /* __linux__ */

    lg.print(std::string("Start server"));

    for (auto i = 0; i < Config::ThreadsCount; i++) {
      if (i == (Config::ThreadsCount - 1u)) i = 0; //restart loop

      if (collection[i]) { // allocated atleast once
        if (collection[i]->is_enabled()) { // not finished, skip
          continue;
        }
      }
      // Now, we sure that have free slot
      auto request = server->get_message(); // sleep & wait here

      collection[i].reset(new PockerHand(request)); // start go nest
    }
  }
  catch (std::string what) {
    std::cout << what << std::endl;
    lg.print(std::string("Start fail with: ") + what);
  }
  catch (...) {
    std::cout << "crash" << std::endl;
  }
}
