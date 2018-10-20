#pragma once

#include "global_defs.h"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/ssl/stream.hpp>

namespace nibaserver {

class server_session : public std::enable_shared_from_this<server_session>
{
public:
    server_session(boost::asio::io_context& ioc,
        boost::asio::ip::tcp::socket&& socket,
        boost::asio::ssl::context& ctx);
    ~server_session() = default;
    void go();
private:
    // error_code is required
    void ping_timer(boost::system::error_code ec);

    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::socket socket_;
    boost::beast::websocket::stream<boost::asio::ssl::stream<boost::asio::ip::tcp::socket&>> ws_;
    boost::asio::steady_timer timer_;

    char ping_state_ = 0;
};

}
