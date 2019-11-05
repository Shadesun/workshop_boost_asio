#include "tcp_server.hpp"

//server constructor
server::server(boost::asio::io_service &io_service, short port, const std::string &address) : _io_service(io_service), _acceptor(io_service, tcp::endpoint(boost::asio::ip::address::from_string(address), port))
{
}

void server::accept()
{

}

void server::handle_accept(session* new_session, const boost::system::error_code& error)
{

}

//netcat 127.0.0.1 4242
//compile with gcc » g++ *.cpp -L /usr/include/boost -lboost_system -lboost_thread -lpthread
int main(int argc, char** argv) {

    boost::asio::io_service ios;

    try {
        //run l'objet server ici
        ios.run();
    }
    catch (std::exception &e) {
        std::cerr << "error: " << e.what() << std::endl;
    }
    return 0;
}