#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/system/error_code.hpp>
#include <chrono>
#include <iostream>

namespace as = boost::asio;
using erroc = boost::system::error_code;

void callback(const erroc& ec)
{
  std::cout << "hello" << std::endl;
}

int main()
{
  as::io_context io;
  as::steady_timer timer(io, std::chrono::seconds(5));
  timer.async_wait(&callback);
  io.run();
  return 0;
}
