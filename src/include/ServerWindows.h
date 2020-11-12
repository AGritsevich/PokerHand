#ifndef __linux__ 
#include "ServerProxy.h"

class ServerWindows : public ServerProxy {
public:
  ServerWindows();
  virtual ~ServerWindows() override;
  virtual void finish() override;
  virtual void listen() override;
  virtual std::string get_message() override;
  virtual void add_message(std::string mes) override;
  virtual uint32_t queue_len() override;
};
#endif /* LINUX */