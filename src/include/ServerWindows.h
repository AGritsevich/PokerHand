#ifndef __linux__ 
#include <ServerProxy>

class ServerWindows : public ServerProxy {
  void listen() override;
  void finish() override;
};
#endif /* LINUX */