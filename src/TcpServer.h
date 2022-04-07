#ifndef _RNET_TCPSERVER_
#define _RNET_TCPSERVER_

#include "TcpConnection.h"
#include "base.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <vector>

// gieven that this head file will nerver be used by ther program
// take some abbreviation to simplify my code

class TcpServer : public base::noncopyable {
  public:
  TcpServer(IoContext& io, Endpoint ep)
      : io_(io)
      , acceptor_(io, ep)
  {
  }

  void start()
  {
    auto conn_ptr = std::make_shared<TcpConnection>(io_);
    acceptor_.async_accept(conn_ptr->Socket(), [conn_ptr, this](const ErrorCode& ec) {
      if (ec) {
        // ERROR_LOG
        // TODO
        return;
      }
      conn_ptr->handle_request();
    });
  }
  ~TcpServer();

  private:
  IoContext& io_;
  Acceptor acceptor_;
};

#endif
