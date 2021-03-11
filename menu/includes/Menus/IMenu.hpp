/*
** EPITECH PROJECT, 2020
** menu
** File description:
** IMenu.hpp
*/

#ifndef IMENU_HPP__
#define IMENU_HPP__

#include "Rtype.hpp"

namespace rtype
{
    class IMenu
    {
        public:
            virtual ~IMenu() = default;

            virtual void run() = 0;
            virtual void background(const std::string &path) = 0;
            virtual void image(float x, float y, const std::string &path, float scale_x, float scale_y) = 0;
            virtual void text(float x, float y, const std::string &str, unsigned int characterSize, sf::Color color) = 0;
    };
}



#endif