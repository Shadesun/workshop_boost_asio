#ifndef WORKSHOP_BOOST_ASIO_UDP_SERVER_HPP
#define WORKSHOP_BOOST_ASIO_UDP_SERVER_HPP
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;

class server {
public:
    server(boost::asio::io_service &io_service, short port, const std::string &ip);
    void read();
    void write();
private:
    void handle_write(const boost::system::error_code &error, size_t bytes_sent);
    void handle_read(const boost::system::error_code &error, size_t bytes_recvd);
    boost::asio::io_service& _ios;
    udp::socket _socket;
    udp::endpoint _sender_endpoint;
    boost::array<char, 1024> _data;
};

#endif //WORKSHOP_BOOST_ASIO_UDP_SERVER_HPP
