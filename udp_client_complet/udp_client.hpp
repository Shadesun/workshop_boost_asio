#ifndef WORKSHOP_BOOST_ASIO_UDP_CLIENT_HPP
#define WORKSHOP_BOOST_ASIO_UDP_CLIENT_HPP
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/asio/streambuf.hpp>

using boost::asio::ip::udp;

class client{
public:
    client(boost::asio::io_service &io_service, const std::string &ip, short port, const std::string &dest_ip, short dest_port);
private:
    void write();
    void read_inupt();
    void read();
    void handle_read(const boost::system::error_code &error, size_t got);
    void handle_write(const boost::system::error_code &error, __attribute__((unused))size_t got);
    void handle_read_input(const boost::system::error_code &error, size_t bytes_transferred);
    boost::asio::io_service& _ios;
    udp::socket _socket;
    boost::array<char, 1024> _data;
    udp::endpoint _sender_endpoint;
    udp::endpoint _server_endpoint;
    boost::asio::streambuf _input_buffer;
    boost::asio::posix::stream_descriptor _in;
};
#endif //WORKSHOP_BOOST_ASIO_UDP_CLIENT_HPP
