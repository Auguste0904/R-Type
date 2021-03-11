/*
** EPITECH PROJECT, 2020
** menu
** File description:
** Play.hpp
*/

#ifndef PLAY_HPP_
#define PLAY_HPP_

#include "AMenu.hpp"

namespace rtype
{
    class Play : public AMenu
    {
        public:
            Play();
            virtual ~Play() = default;
            void run();

        private:
            sf::Event _event;
            bool _isPressed;
    };
}

#endif
