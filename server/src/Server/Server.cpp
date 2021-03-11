/*
** EPITECH PROJECT, 2020
** Server
** File description:
** Server
*/

#include "Server.hpp"
#include <string>
#include <iostream>

rty::server::Server::Server(int port) : _udpServer(port)
{

}

void rty::server::Server::start()
{
    _udpServer.start();
    std::cout << "Ending start" << std::endl;
    _udpServer.sendStartingGame();

    for (size_t i = 0; i < _udpServer.getPlayers().size(); i++) {
        _pos.push_back(std::pair<int, int>(100, 100 + (i * 200)));
    }

    while(_udpServer.getPlayers().size() > 0) {
        std::string a = _udpServer.readPlayerInput();
        usleep(0.1);
        if (a == "") {
            //
        } else if (!a.empty() && a.size() >= 1) {
            int index = a[0];
            char final = a[1];

            switch (final) {
                case 'u':
                    _pos.at(index - '0').second -= 7;
                    std::cout << "-----------------------------------------"<<std::endl;
                    break;
                case 'd':
                    _pos.at(index - '0').second += 7;
                    break;
                case 'r':
                    _pos.at(index - '0').first += 7;
                    break;
                case 'l':
                    _pos.at(index - '0').first -= 7;
                    break;
                case 's':
                    // TODO
                    break;
            }
        }
        std::string tmp = "";
        for (size_t i = 0; i < _udpServer.getPlayers().size(); i++) {
            tmp += std::to_string(_pos.at(i).first) + ":" + std::to_string(_pos.at(i).second);
            if (i < _udpServer.getPlayers().size() - 1)
                tmp += ";";
        }
        _udpServer.sendAll(tmp);
    }
}
