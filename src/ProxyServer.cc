#include "ProxyServer.h"
#include "ProxyConnection.h"
#include "base.h"
#include <memory>
#include <system_error>

void ProxyServer::start()
{
  auto conn_ptr = std::make_shared<ProxyConnection>(io_);
  acceptor_.async_accept(conn_ptr->ClientSocket(), [=](std::error_code error) {
      if (error) {
        //TODO Debug
      }
      conn_ptr->startProxy(target_endpoient_);
      start();
  });
}
