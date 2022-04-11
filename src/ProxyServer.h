#ifndef _RNET_PROXYSERVER_H_
#define _RNET_PROXYSERVER_H_

#include "base.h"
#include <algorithm>
#include <boost/asio/ip/tcp.hpp>

// brefore establish proxyserver ,a endpoint shoud be resolved first

class ProxyServer : public base::noncopyable {
  public:
  ProxyServer(IoContext& io, Endpoint listen, Endpoint target)
      : io_(io)
      , listen_endpoint_(std::move(listen))
      , target_endpoient_(std::move(target))
      , acceptor_{io, {boost::asio::ip::tcp::v4(),7999}}
  //, socket_(io)
  {
  }

  void start();
  void setReuseAddress(bool on = true)
  {
    if (on) {
    }
  }

  private:
  IoContext& io_;
  Acceptor acceptor_;
  // AsioSocket socket_;
  Endpoint listen_endpoint_;
  Endpoint target_endpoient_;
};

#include "ProxyServer.h"
#endif
