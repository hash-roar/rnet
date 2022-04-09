#ifndef _RNET_PROXYSERVER_H_
#define _RNET_PROXYSERVER_H_

#include "base.h"
#include <algorithm>

// brefore establish proxyserver ,a endpoint shoud be resolved first

class ProxyServer : public base::noncopyable {
  public:
  ProxyServer(IoContext& io, Endpoint listen, Endpoint target)
      : io_(io)
      , listen_endpoint_(std::move(listen))
      , target_endpoient_(std::move(target))
      , acceptor_(io, listen_endpoint_)
  //, socket_(io)
  {
  }

  void start();

  private:
  IoContext& io_;
  Acceptor acceptor_;
  // AsioSocket socket_;
  Endpoint listen_endpoint_;
  Endpoint target_endpoient_;
};

#endif
