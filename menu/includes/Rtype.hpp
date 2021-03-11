/*
** EPITECH PROJECT, 2020
** menu
** File description:
** IMenu.hpp
*/

#ifndef RTYPE_HPP__
#define RTYPE_HPP__

    /* C++ */
#include <iostream>
#include <string>
#include <memory>

    /* SFML */
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace rtype
{
    class Sfml
    {
        public:
            std::unique_ptr<sf::RenderWindow> window;
            std::unique_ptr<sf::View> view;
            sf::Event event;
            sf::Mouse mouse;
            sf::Music theme;
            float R_RATIO;
    };

    typedef enum direction_e {
        Up,
        Down,
        Right,
        Left,
        Shoot,
        None
    } direction_t;

    extern rtype::Sfml *sfml;
}

#endif