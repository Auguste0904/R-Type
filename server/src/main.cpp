/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** main.cpp
*/

#include <stdlib.h>
#include <stdexcept>
#include "Server.hpp"
#include <iostream>

int main(int ac, const char **av)
{
    int port;

    try {
        if (ac == 2) {
            port = std::stoi(av[1]);
        } else {
            port = 30306;
        }
        rty::server::Server s(port);
        s.start();
    }
    catch(std::exception& e) {
        std::cerr << "Fatal error (main catch): " << e.what() << std::endl;
         return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
