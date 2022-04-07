#ifndef _RNET_BASE_H_
#define _RNET_BASE_H_

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/system_context.hpp>
#include <boost/system/error_code.hpp>

// gieven that this head file will nerver be used by ther program
// take some abbreviation to simplify my code
using AsioSocket = boost::asio::ip::tcp::socket;
using Endpoint = boost::asio::ip::tcp::endpoint;
using DeadLineTimer = boost::asio::deadline_timer;
using IoContext = boost::asio::io_context;
using ErrorCode = boost::system::error_code;
using Acceptor = boost::asio::ip::tcp::acceptor;
namespace base {

class noncopyable {
  public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable) = delete;

  protected:
  noncopyable() = default;
  ~noncopyable() = default;
};
}

#endif
