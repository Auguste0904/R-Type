#include "UDPClient.hpp"

rty::network::Client::Client() : _resolver(_io_service), _port(0), _socket(_io_service)
{
}

void rty::network::Client::init(int port, const std::string &serverIP)
    /* _resolver(_io_service), _port(port), _socket(_io_service) */
{
    _port = port;

    std::cout << "Connecting to " << serverIP << " on port " << port << std::endl;

    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), serverIP, std::to_string(port));
    _endpoint = *_resolver.resolve(query);
    _socket.open(boost::asio::ip::udp::v4());
    /* std::string sendBuf(std::string("Hello")); */
    /* _socket.send_to(boost::asio::buffer(sendBuf), _endpoint); */
}

rty::network::Client::~Client()
{
    if (_socket.is_open())
        _socket.close();
    std::cerr << "Client is destroyed" << std::endl;
}

std::string rty::network::Client::recvStr(const int size)
{
    boost::array<char, 20001> recvBuf = {};

    recvBuf.assign(0);
    recvUntilTimeout(_endpoint, std::ref(recvBuf), 10);
    return std::string(recvBuf.begin(), recvBuf.begin() + size);
}

boost::optional<boost::system::error_code>
rty::network::Client::recvUntilTimeout(UDPEndpoint &remoteEndpoint,
    boost::array<char, 20001> &recvBuf, int seconds)
{
    boost::optional<boost::system::error_code> timer_result;
    boost::asio::deadline_timer timer(_io_service);
    timer.expires_from_now(boost::posix_time::seconds(seconds));
    timer.async_wait([&timer_result](const boost::system::error_code &err) {
        timer_result.reset(err);
    });
    boost::optional<boost::system::error_code> read_result;
    _socket.async_receive_from(boost::asio::buffer(recvBuf), remoteEndpoint,
        [&read_result](const boost::system::error_code &err, size_t) {
            read_result.reset(err);
        });
    _io_service.reset();
    while (_io_service.run_one()) {
        if (read_result)
            timer.cancel();
        else if (timer_result) {
            _socket.cancel();
        }
    }
    return read_result;
}

void rty::network::Client::connect()
{
    std::string sendBuf(std::string("connect"));
    _socket.send_to(boost::asio::buffer(sendBuf), _endpoint);
}

void rty::network::Client::disconnect(const int id)
{
    char iid = id;
    std::string s("disconn ");
    s.push_back(iid);
    std::string sendBuf(s);

    _socket.send_to(boost::asio::buffer(sendBuf), _endpoint);
}

void rty::network::Client::disobserve(const int id)
{
    char iid = id;
    std::string s("disobserve ");
    s.push_back(iid);
    std::string sendBuf(s);

    _socket.send_to(boost::asio::buffer(sendBuf), _endpoint);
}

void rty::network::Client::sendStr(const std::string &s)
{
    std::cout << "LU send str" << s << std::endl;
    _socket.send_to(boost::asio::buffer(s), _endpoint);
}

std::string rty::network::Client::getLobbyData()
{
    return this->recvStr(200);
}

int rty::network::Client::getPort() const noexcept
{
    return _port;
}

void rty::network::Client::close() noexcept
{
    if (_socket.is_open())
        _socket.close();
}

// global instance
rty::network::Client udpClient_g;
