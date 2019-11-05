#include "tcp_client.hpp"

client::client(boost::asio::io_service &io_service, const std::string &dest_ip, short dest_port) : _io_service(io_service)
{
    tcp::endpoint edp(boost::asio::ip::address::from_string(dest_ip), dest_port);

    connect(edp);
}

void client::handle_connect(session* new_session, const boost::system::error_code& error)
{
    if (!error) {
        new_session->start();
    }
    else
        std::cerr << error.message();
}

void client::connect(tcp::endpoint &edp) {

    auto *new_session = new session(_io_service);
    tcp::socket &socket = new_session->getSocket();

    socket.async_connect(edp, boost::bind(&client::handle_connect, this, new_session, boost::asio::placeholders::error));
}

int main(int argc, char **argv)
{
    std::string dest_ip = "127.0.0.1";
    short dest_port = 4242;
    boost::asio::io_service ios;

    try {
        client cli(ios, dest_ip, dest_port);
        ios.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}