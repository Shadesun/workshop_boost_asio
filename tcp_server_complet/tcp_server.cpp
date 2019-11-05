#include "tcp_server.hpp"

//server constructor
server::server(boost::asio::io_service &io_service, short port, const std::string &address) : _io_service(io_service), _acceptor(io_service, tcp::endpoint(boost::asio::ip::address::from_string(address), port))
{
    accept();
}

//accepts new connections to the server
void server::accept()
{
    //create a new connection object
    auto *new_session = new session(_io_service);
    //waits until someone connects to the server
    _acceptor.async_accept(new_session->getSocket(), boost::bind(&server::handle_accept, this, new_session, boost::asio::placeholders::error));
}

void server::handle_accept(session* new_session, const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "New client connected\n";
        //create a new session object
        new_session->start();
        new_session = new session(_io_service);
        //accepting new connections
        accept();
    }
    else
        delete new_session;
}

//netcat 127.0.0.1 4242
//compile with gcc » g++ *.cpp -L /usr/include/boost -lboost_system -lboost_thread -lpthread
int main(int argc, char** argv) {
    short port = 4242;
    std::string address = "127.0.0.1";
    //creating io service needed for boost::asio
    boost::asio::io_service ios;

    try {
        //running the server
        server serv(ios, port, address);
        //keeps the io_service alive
        ios.run();
    }
    catch (std::exception &e) {
        std::cerr << "error: " << e.what() << std::endl;
    }
    return 0;
}