#include "ProxyConnection.h"
#include "base.h"
#include <boost/asio/buffer.hpp>
#include <cstddef>
#include <system_error>

void ProxyConnection::startProxy(Endpoint target)
{
  auto self_ptr = shared_from_this();
  server_socket_.async_connect(target, [self_ptr](std::error_code error) {
    if (error) {
      // TODO DEBUG
    }
    self_ptr->read_from_client();
    self_ptr->read_from_server();
  });
}

void ProxyConnection::read_from_client()
{
  auto self_ptr = shared_from_this();
  client_socket_.async_read_some(boost::asio::buffer(data_from_client_),
      [self_ptr](std::error_code error, std::size_t n) {
        if (!error) {
          self_ptr->write_to_server(n);
        } else {
          self_ptr->stop();
        }
      });
}

void ProxyConnection::write_to_server(std::size_t n)
{
  auto self_ptr = shared_from_this();
  server_socket_.async_write_some(boost::asio::buffer(data_from_client_, n),
      [self_ptr](std::error_code error, std::size_t n) {
        if (!error) {
          self_ptr->read_from_client();
        } else {
          self_ptr->stop();
        }
      });
}

void ProxyConnection::read_from_server()
{
  auto self_ptr = shared_from_this();
  client_socket_.async_read_some(boost::asio::buffer(data_from_server),
      [self_ptr](std::error_code error, std::size_t n) {
        if (!error) {
          self_ptr->write_to_client(n);
        } else {
          self_ptr->stop();
        }
      });
}
void ProxyConnection::write_to_client(std::size_t n)
{
  auto self_ptr = shared_from_this();
  server_socket_.async_write_some(boost::asio::buffer(data_from_client_, n),
      [self_ptr](std::error_code error, std::size_t n) {
        if (!error) {
          self_ptr->read_from_server();
        } else {
          self_ptr->stop();
        }
      });
}
