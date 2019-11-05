#include "tcp_connection.hpp"

session::session(boost::asio::io_service& io_service) : _socket(io_service),
_in(io_service, ::dup(STDIN_FILENO)), _input_buffer(1024), _data{0}
{}

tcp::socket &session::getSocket()
{
    return _socket;
}

void session::start()
{
    read();
    read_inupt();
}

void session::read_inupt()
{
    //reads from cin since std::cin is thread-unsafe
    boost::asio::async_read_until(_in, _input_buffer, '\n', boost::bind(&session::handle_read_input, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void session::handle_read_input(const boost::system::error_code &error, size_t bytes_transferred)
{
    //calls our write function
    if (!error) {
        write();
    }
    else {
        std::cerr << error.message();
        delete this;
    }
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
        std::cout << "server said : " << _data.data();
        //use the data here
        read();
    }
    else
        delete this;
}

void session::write()
{
    //writes then calls the handle
    boost::asio::async_write(_socket, _input_buffer,boost::bind(&session::handle_write,this, boost::asio::placeholders::error));
}

void session::handle_write(const boost::system::error_code& error)
{
    //calling read again to keep the server alive
    if (!error) {
        read_inupt();
    }
    else
        delete this;
}