/*
** EPITECH PROJECT, 2020
** menu
** File description:
** JoinRoom.hpp
*/

#ifndef JOINROOM_HPP_
#define JOINROOM_HPP_

#include "AMenu.hpp"

namespace rtype
{
    class JoinRoom : public AMenu
    {
        public:
            JoinRoom();
            virtual ~JoinRoom() = default;
            void run();
            void manage_event();
            std::string enter_text();

        private:
            sf::Event _event;
            bool _isPressed;
    };

}
#endif