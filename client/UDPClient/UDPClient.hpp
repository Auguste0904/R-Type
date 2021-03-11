#ifndef UDPCLIENT_HPP
#define UDPCLIENT_HPP

/* #include "Exception.hpp" */

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>

namespace rty {
    namespace network {
        using UDPEndpoint = boost::asio::ip::udp::endpoint;

        class Client {
        public:
            void init(int port, const std::string &serverIP = "127.0.0.1");
            Client();

            ~Client();

            /**
             * @brief send disconnection order to the server
             *
             * @param id       id of the player to diconnect
             */
            void disconnect(const int id);

            /**
             * @brief get information on the inprogress lobby
             *
             * @return the received string, cf doc to see the instructions list
             */
            std::string getLobbyData();

            /**
             * @brief recieve a string of given size from server
             *
             * @param size      size of the string to receive in bytes
             *
             * @return string   the received string
             */
            std::string recvStr(const int size);
            boost::optional<boost::system::error_code> recvUntilTimeout(
                UDPEndpoint &remoteEndpoint, boost::array<char, 20001> &recvBuf,
                int seconds);

            /**
             * @brief get the port of the remote or local server
             *
             * @return port     as int
             */
            int getPort() const noexcept;

            /**
             * @brief manually close socket
             */
            void close() noexcept;


            /**
             * @brief connect network client to server with connect command
             *
             * @return id     -1 if error
             */
            void connect();

            void disobserve(const int id);

            void sendStr(const std::string &s);
        private:
            // operations on socket
            boost::asio::io_service _io_service;

            boost::asio::ip::udp::resolver _resolver;

            int _port;

            // socket with the server
            boost::asio::ip::udp::socket _socket;
            // remote server endpoint
            boost::asio::ip::udp::endpoint _endpoint;
        };
    } // namespace network
} // namespace rty

extern rty::network::Client udpClient_g;

#endif // UDPCLIENT_HPP
