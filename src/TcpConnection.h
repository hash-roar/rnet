#ifndef _RNET_TCPCONNECTION_
#define _RNET_TCPCONNECTION_

#include "base.h"
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <chrono>
#include <memory>
#include <vector>

// to manage memeory of tcp connection we have two choices.
// for that all callbacks are asynchronous we have to take on
// smart pointer as a data memeber  of TcpConnection but it
// is not exception safe for which this way is discarded.
// yet another solution is to transform pointer in every callback
// to prolong life time of TcpConnection

class TcpConnection : public base::noncopyable,
                      public std::enable_shared_from_this<TcpConnection> {
  public:
  using ConnPtr = std::shared_ptr<TcpConnection>;
  TcpConnection(IoContext& io)
      : socket_(io)
      , buffer_(kBufferInitSize, 0)
      , timer_(io)
  {
  }

  void stop();

  AsioSocket& Socket()
  {
    return socket_;
  }

  void handle_request(const ErrorCode& rc );

  private:

  void onRead();
  void onWrite();
  private:
  static const int kBufferInitSize = 1024;

  //ConnPtr self_ptr_;
  AsioSocket socket_; // avoid name conflict
  DeadLineTimer timer_;
  //std::chrono::seconds timeout_second_;
  std::vector<char> buffer_;

  bool stopped_;
};

#endif
