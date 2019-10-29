#ifndef WORKSHOP_BOOST_ASIO_TCP_CONNECTION_HPP
#define WORKSHOP_BOOST_ASIO_TCP_CONNECTION_HPP
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

class session {
public:
    explicit session(boost::asio::io_service &io_service);
    void start();
    void write(boost::array<char, 1024> data);
    void read();
    tcp::socket &getSocket();
private:
    void handle_write(const boost::system::error_code &error);
    void handle_read(const boost::system::error_code &error, size_t bytes_transferred);
    tcp::socket _socket;
    boost::array<char, 1024> _data;
};

#endif //WORKSHOP_BOOST_ASIO_TCP_CONNECTION_HPP
