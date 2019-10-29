#ifndef WORKSHOP_BOOST_ASIO_TCP_SERVER_HPP
#define WORKSHOP_BOOST_ASIO_TCP_SERVER_HPP
#include "tcp_connection.hpp"

class server {
public:
    server(boost::asio::io_service& io_service, short port, const std::string &address);
    void accept();
private:
    void handle_accept(session *new_session, const boost::system::error_code &error);
    boost::asio::io_service& _io_service;
    tcp::acceptor _acceptor;
};
#endif //WORKSHOP_BOOST_ASIO_TCP_SERVER_HPP
