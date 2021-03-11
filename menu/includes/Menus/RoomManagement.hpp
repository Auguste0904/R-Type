/*
** EPITECH PROJECT, 2020
** menu
** File description:
** Play.hpp
*/

#ifndef ROOMMANAGEMENT_HPP_
#define ROOMMANAGEMENT_HPP_

#include "AMenu.hpp"

namespace rtype
{
    class RoomManagement : public AMenu
    {
        public:
            RoomManagement();
            virtual ~RoomManagement() = default;
            void run();
            void manage_event();
            void runJoinRoom();
            void runCreateRoom();

        private:
            sf::Event _event;
            bool _isPressed;
    };
}

#endif
