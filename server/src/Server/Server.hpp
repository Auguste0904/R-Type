/*
** EPITECH PROJECT, 2020
** Server
** File description:
** Server
*/

#ifndef SERVER_CPP
#define SERVER_CPP

#include "UDPServer.hpp"
#include <vector>
#include <utility>

namespace rty {
    namespace server {
    class Server {
        public:
            Server(int port);
            ~Server() {}
            void start();

        private:
            rty::server::network::UdpServer _udpServer;
            std::vector<std::pair<int, int>> _pos;
    };
    }
}

#endif // SERVER_CPP
