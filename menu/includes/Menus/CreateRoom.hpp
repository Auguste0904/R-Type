/*
** EPITECH PROJECT, 2020
** menu
** File description:
** CreateRoom.hpp
*/

#ifndef CREATEROOM_HPP_
#define CREATEROOM_HPP_

#include "AMenu.hpp"

namespace rtype
{
    class CreateRoom : public AMenu
    {
        public:
            CreateRoom();
            virtual ~CreateRoom() = default;
            void run();
            void manage_event();

        private:
            sf::Event _event;
            bool _isPressed;
    };

}
#endif