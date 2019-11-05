#ifndef WORKSHOP_BOOST_ASIO_TCP_CLIENT_HPP
#define WORKSHOP_BOOST_ASIO_TCP_CLIENT_HPP
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "tcp_connection.hpp"

//shortens lines just write tcp instead of boost::asio::ip::tcp
using boost::asio::ip::tcp;

class client{
public:
    client(boost::asio::io_service &ioService, const std::string &dest_ip, short dest_port);
private:
    void connect(tcp::endpoint &edp);
    boost::asio::io_service &_io_service;
    void handle_connect(session *new_session, const boost::system::error_code &error);
};
#endif //WORKSHOP_BOOST_ASIO_TCP_CLIENT_HPP
