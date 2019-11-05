#include "tcp_connection.hpp"

session::session(boost::asio::io_service &io_service) : _socket(io_service)
{}

tcp::socket &session::getSocket()
{
    return _socket;
}

void session::start()
{
    read();
}
void session::read()
{
    //reads then call the handle
    boost::asio::async_read(_socket, boost::asio::buffer(_data),boost::asio::transfer_at_least(1), boost::bind(&session::handle_read,this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void session::handle_read(const boost::system::error_code &error, size_t bytes_transferred)
{
    //writes the data back to the client
    if (!error) {
        std::cout << _data.data();
        write(_data);
    }
    else
        delete this;
}

void session::write(boost::array<char, 1024> data)
{
    //writes then calls the handle
    boost::asio::async_write(_socket, boost::asio::buffer(data),boost::bind(&session::handle_write,this, boost::asio::placeholders::error));
    //cleaning the buffer
    _data.fill(0);
}

void session::handle_write(const boost::system::error_code& error)
{
    //calling read again to keep the server alive
    if (!error)
        read();
    else
        delete this;
}