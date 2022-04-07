#include <assert.h>
#include "TcpConnection.h"

using namespace boost::asio;

void TcpConnection::handle_request(const ErrorCode &rc)
{
  auto conn_ptr = shared_from_this();
  assert(conn_ptr.use_count()==1);


}

void TcpConnection::stop()
{

}
