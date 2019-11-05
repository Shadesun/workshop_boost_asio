#ifndef WORKSHOP_BOOST_ASIO_TCP_CONNECTION_HPP
#define WORKSHOP_BOOST_ASIO_TCP_CONNECTION_HPP
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/asio/streambuf.hpp>

//shortens lines just write tcp instead of boost::asio::ip::tcp
using boost::asio::ip::tcp;

class session {
public:
    explicit session(boost::asio::io_service &io_service);
    void start();
    tcp::socket &getSocket();
private:
    void read_inupt();
    void write();
    void read();
    void handle_read_input(const boost::system::error_code &error, size_t bytes_transferred);
    void handle_write(const boost::system::error_code &error);
    void handle_read(const boost::system::error_code &error, size_t bytes_transferred);
    tcp::socket _socket;
    boost::array<char, 1024> _data;
    boost::asio::streambuf _input_buffer;
    boost::asio::posix::stream_descriptor _in;
};

#endif //WORKSHOP_BOOST_ASIO_TCP_CONNECTION_HPP
