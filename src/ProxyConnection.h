#ifndef _RNET_PROXYCONN_H_
#define _RNET_PROXYCONN_H_

#include "base.h"
#include <array>
#include <memory>
class ProxyConnection : std::enable_shared_from_this<ProxyConnection>,
                        base::noncopyable {

  public:
  ProxyConnection(IoContext& io)
      : client_socket_(io)
      , server_socket_(io)
  {
  }

  AsioSocket& ClientSocket() { return client_socket_; }
  // finish establish connnect with server and begin forward packet
  void startProxy(Endpoint target);

  private:
  void read_from_client();
  void write_to_client(size_t n);
  void read_from_server();
  void write_to_server(size_t n);
  void stop()
  {
    client_socket_.close();
    server_socket_.close();
  }

  private:
  AsioSocket client_socket_;
  AsioSocket server_socket_;
  std::array<char, 1024> data_from_client_;
  std::array<char, 1024> data_from_server;
};

#endif
