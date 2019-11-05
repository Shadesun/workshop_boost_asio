#include "udp_client.hpp"

client::client(boost::asio::io_service &io_service, const std::string &ip, short port, const std::string &dest_ip, short dest_port)
: _ios(io_service), _socket(io_service, udp::endpoint(boost::asio::ip::address::from_string(ip), port)),
_server_endpoint(boost::asio::ip::address::from_string(dest_ip), dest_port),
_in(io_service, ::dup(STDIN_FILENO)), _input_buffer(1024), _data{0}
{
    read();
    read_inupt();
}

void client::write()
{
    _socket.async_send_to(_input_buffer.data(), _server_endpoint, boost::bind(&client::handle_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void client::handle_write(const boost::system::error_code &error, size_t got)
{
    if (!error) {
        read_inupt();
    }
    else
        std::cerr << error << std::endl;
}

void client::read_inupt()
{
    //reads from cin since std::cin is thread-unsafe
    boost::asio::async_read_until(_in, _input_buffer, '\n', boost::bind(&client::handle_read_input, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void client::handle_read_input(const boost::system::error_code &error, size_t bytes_transferred)
{
    //calls our write function
    if (!error) {
        write();
    }
    else {
        std::cerr << error.message() << std::endl;
        delete this;
    }
}

void client::read()
{
    _socket.async_receive_from(boost::asio::buffer(_data), _sender_endpoint, boost::bind(&client::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void client::handle_read(const boost::system::error_code &error, size_t got)
{
    if (!error) {
        std::cout << _data.data();
        read_inupt();
    }
    else
        std::cerr << error.message() << std::endl;
}

int main(int argc, char **argv)
{
    std::string ip = "127.0.0.1";
    short port = 4245;
    std::string target_ip = "127.0.0.1";
    short target_port = 4244;
    boost::asio::io_service ios;

    try {
        client cli(ios, ip, port, target_ip, target_port);
        ios.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}