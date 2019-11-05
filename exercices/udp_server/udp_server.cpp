#include "udp_server.hpp"

server::server(boost::asio::io_service& io_service, short port, const std::string &ip): _ios(io_service), _socket(io_service, udp::endpoint(boost::asio::ip::address::from_string(ip), port))
{

}

void server::read() {

}

void server::handle_read(const boost::system::error_code &e, size_t bytes_recvd)
{

}

void server::write() {

}

void server::handle_write(const boost::system::error_code &e, size_t bytes_sent)
{

}

int main(int argc, char **argv)
{
    boost::asio::io_service ios;

    try {
        //run l'objet server ici
        ios.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}