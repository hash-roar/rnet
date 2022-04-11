#include <algorithm>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "ProxyServer.h"
#include "base.h"

using namespace boost::asio::ip;
using namespace boost::asio;

int main()
{
  io_context io_context;
  Endpoint listen(tcp::v4(), 7999);
  Endpoint target(ip::address::from_string("127.0.0.1"), 8000);
  ProxyServer server(io_context, std::move(listen), std::move(target));

  server.start();
  io_context.run();
}
