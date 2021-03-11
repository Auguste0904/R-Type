/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** SystemManager.hpp
*/

#ifndef SYSTEMMANAGER_HPP__
#define SYSTEMMANAGER_HPP__

#include "types.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace game
{
    class SystemManager {
        public:
            SystemManager();
            virtual ~SystemManager() = default;
            void declareSystem(void (&function)(void));
            void removeSystem(void (&function)(void));
            std::vector<void (*)(void)> &getSystems(void);
        private:
            std::vector<void (*)(void)> _systemList;
    };
}

#endif