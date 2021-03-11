#include "UDPServer.hpp"
#include <stdexcept>

static const std::vector<std::string> DIRECTIONS = {
    "NN", "SS", "WW", "EE", "NE", "NW", "SW", "SE"};

static const int WAITING_TIME = 15;

rty::server::network::UdpServer::UdpServer(const int port) :
    _socket(_ioService, UDPEndpoint(boost::asio::ip::udp::v4(), port)),
    _players(), _port(port), _currentID(0)
{
}

rty::server::network::UdpServer::~UdpServer()
{
    if (_socket.is_open())
        _socket.close();
}

void rty::server::network::UdpServer::start()
{
    std::cout << "Starting udp server" << std::endl;
    std::cout << "waiting for connections ..." << std::endl;
    std::cout << "server runs on port: " << _port << std::endl;
    waitForClients();
}

void rty::server::network::UdpServer::send(
    const UDPEndpoint &endpoint, const std::string &msg)
{
    _socket.async_send_to(boost::asio::buffer(msg), endpoint,
        [](const boost::system::error_code &, size_t) {});
}

void rty::server::network::UdpServer::send(char id, const std::string &msg)
{
    for (size_t i = 0; i < _players.size(); i++) {
        if (_players.at(i).second == id)
                _socket.async_send_to(boost::asio::buffer(msg),
                    _players[i].first,
                    [](const boost::system::error_code &, size_t) {});
    }
}

void rty::server::network::UdpServer::connectClient(const UDPEndpoint &endpoint)
{
    bool found = false;
    for (auto &it : _players) {
        if (it.first == endpoint)
            found = true;
    }
    if (found == false) {
        _players.push_back(std::pair<boost::asio::ip::udp::endpoint, int>(endpoint, _currentID));
        _currentID += 1;
    } else {
        return; // TODO check
    }

    std::cout << "[+] New client connected with id " << _currentID-1 << std::endl;
}

void rty::server::network::UdpServer::disconnectClient(char id)
{
    for (size_t i = 0; i < _players.size(); i++) {
        if (_players.at(i).second == id) {
            _players.erase(_players.begin() + i);
            std::cout << "Client disconnected with id " << id << std::endl;
            break;
        }
    }
}

void rty::server::network::UdpServer::readCommand(
    const UDPEndpoint &endpoint, const std::string &cmd)
{
    std::cout << "command: " << cmd << std::endl;
    if (cmd.find("connect") == 0)
        this->connectClient(endpoint);
    else if (cmd.find("disconn") == 0)
        this->disconnectClient(cmd.substr((cmd.find(" ") + 1))[0]);
    else {
        std::cout << "error invalid command: " << cmd << std::endl;
    }
}

void rty::server::network::UdpServer::sendAll(const std::string &msg)
{
    for (auto player : _players) {
        this->send(player.first, msg);
    }
}

void rty::server::network::UdpServer::sendLobbyInfo(int time)
{
    // infoLobby;time;size;totaltime
    std::string info("infoLobby;");
    info += std::to_string(time);
    info += ";";
    auto size = _players.size();
    info += std::to_string(size);
    info += ";";
    info += std::to_string(WAITING_TIME);
    this->sendAll(info);
}

void rty::server::network::UdpServer::sendStartingGame()
{
    std::cout << "Send start game" << std::endl;
    std::string info("startingGame");
    this->sendAll(info);
    usleep(100);

    for (size_t i = 0; i < _players.size(); i++) {
        std::string id("ID" + std::to_string(i));
        this->send((char)i, id);
    }
}

boost::optional<boost::system::error_code>
rty::server::network::UdpServer::recvUntilTimeout(
    UDPEndpoint &remoteEndpoint, boost::array<char, 2000> &recvBuf, int seconds)
{
    boost::optional<boost::system::error_code> timer_result;
    boost::asio::deadline_timer timer(_ioService);
    timer.expires_from_now(boost::posix_time::seconds(seconds));
    timer.async_wait([&timer_result](const boost::system::error_code &err) {
        timer_result.reset(err);
    });
    boost::optional<boost::system::error_code> read_result;
    _socket.async_receive_from(boost::asio::buffer(recvBuf), remoteEndpoint,
        [&read_result](const boost::system::error_code &err, size_t) {
            read_result.reset(err);
        });
    _ioService.reset();
    while (_ioService.run_one()) {
        if (read_result)
            timer.cancel();
        else if (timer_result) {
            _socket.cancel();
        }
    }
    return read_result;
}

int rty::server::network::UdpServer::waitForClients()
{
    boost::array<char, 2000> recvBuf = {};
    UDPEndpoint remoteEndpoint;

    recvBuf.assign(0);

    // wait for the first connection
    while (_players.size() == 0) {
        auto read_result = this->recvUntilTimeout(remoteEndpoint, recvBuf, 99);
        if (*read_result) {
            throw std::runtime_error(
                std::string("No client connected - ") + (*read_result).message());
        }
        this->readCommand(
            remoteEndpoint, std::string(recvBuf.begin(), recvBuf.end()));
    }

    // listen for other players during x seconds
    auto t = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now() - t).count();
    auto size = 1;
    auto waiting_time = WAITING_TIME; // TODO
    while (size < 4 && elapsed <= waiting_time) {
        size = _players.size();
        recvBuf.assign(0);
        this->sendLobbyInfo(elapsed);
        boost::optional<boost::system::error_code> timer_result;
        boost::asio::deadline_timer timer(_ioService);
        timer.expires_from_now(boost::posix_time::seconds(1));
        timer.async_wait([&timer_result](const boost::system::error_code &err) {
            timer_result.reset(err);
        });
        boost::optional<boost::system::error_code> read_result;
        _socket.async_receive_from(boost::asio::buffer(recvBuf), remoteEndpoint,
            [&read_result](const boost::system::error_code &err, size_t) {
                read_result.reset(err);
            });
        bool time = false;
        _ioService.reset();
        while (_ioService.run_one()) {
            if (read_result)
                timer.cancel();
            else if (timer_result) {
                _socket.cancel();
                elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now() - t)
                              .count();
                time = true;
            }
        }
        if (time) {
            continue;
        }
        if (*read_result)
            throw std::runtime_error(
                (*read_result).message());
        this->readCommand(
            remoteEndpoint, std::string(recvBuf.begin(), recvBuf.end()));
        elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now() - t)
                      .count();
    }
    size = _players.size();
    return size;
}

rty::server::network::ServerPlayer rty::server::network::UdpServer::getPlayers() const noexcept
{
    return _players;
}

std::string rty::server::network::UdpServer::readPlayerInput()
{
    boost::array<char, 2000> recvBuf = {};
    UDPEndpoint endpoint;

    auto read_result = this->recvUntilTimeout(endpoint, recvBuf, 5);
        if (*read_result)
            return "";
    std::string cmd = std::string(recvBuf.begin(), recvBuf.end());
    // cmd = std::string(cmd.c_str());
    return cmd;
}

std::string rty::server::network::UdpServer::readAll()
{
    boost::system::error_code error;
    boost::array<char, 2000> recvBuf = {};
    UDPEndpoint endpoint;

    auto read_result = this->recvUntilTimeout(endpoint, recvBuf, 5);
    if (*read_result)
        throw std::runtime_error((*read_result).message());
    std::string cmd = std::string(recvBuf.begin(), recvBuf.end());
    cmd = std::string(cmd.c_str());
    std::cout << "[*] recved: " << cmd << std::endl;
    if (cmd.find("killServer") == 0)
        throw std::runtime_error("End of the server");
    if (cmd.find("move") == 0 || cmd.find("bomb") == 0 ||
        cmd.find("stop") == 0) {
        if (this->verifID(endpoint, cmd.substr((cmd.find(" ") + 1))[0]))
            if (cmd.find("move") == 0 &&
                std::find(DIRECTIONS.begin(), DIRECTIONS.end(),
                    cmd.substr(cmd.find(" ") + 3, 2)) == DIRECTIONS.end()) {
                std::cout << "[-] error4 invalid command: " << cmd << std::endl;
                return std::string("none");
            }
        return cmd;
    }
    else if (cmd.find("disconn") == 0) {
        if (this->verifID(endpoint, cmd.substr((cmd.find(" ") + 1))[0]))
            return cmd;
        else {
            std::cout << "error4 invalid command: " << cmd << std::endl;
        }
    }
    return std::string("none");
}

bool rty::server::network::UdpServer::verifID(const UDPEndpoint &, const char id)
{
    /* for (auto &it : _players) { */
    /*     for (size_t i = 0; i < it.second.size(); i++) { */
    /*         if (it.second[i].first == id) { */
    /*             return true; */
    /*         } */
    /*     } */
    /* } */
    /* return false; */
}
