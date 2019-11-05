#include "udp_server.hpp"

server::server(boost::asio::io_service& io_service, short port, const std::string &ip)
: _ios(io_service),
_socket(io_service, udp::endpoint(boost::asio::ip::address::from_string(ip), port)), _data{0}
{
    //starts reading data
    read();
}

void server::read() {
    //reads data destined to the server
    _socket.async_receive_from(
        boost::asio::buffer(_data, 1024),
        _sender_endpoint,boost::bind(&server::handle_read,
            this, boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void server::handle_read(const boost::system::error_code &e, size_t bytes_recvd)
{
    if (!e && bytes_recvd > 0) {
        //writes back to the user
        std::cout << _data.data();
        write();
    }
    else {
        std::cerr << e.message() << std::endl;
        read();
    }
}

void server::write() {
    //writes to the _sender_endpoint
    _socket.async_send_to(
        boost::asio::buffer(_data, boost::array<char, 1024>::size()), _sender_endpoint,
        boost::bind(&server::handle_write, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void server::handle_write(const boost::system::error_code &e, size_t bytes_sent)
{
    if (!e) {
        //empties _data and starts listening again
        _data.fill(0);
        read();
    }
    else
        std::cerr << e.message() << std::endl;
}

int main(int argc, char **argv)
{
    boost::asio::io_service ios;
    short port = 4244;
    std::string ip = "127.0.0.1";

    try {
        server s(ios, port, ip);
        ios.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}