/*
** EPITECH PROJECT, 2020
** menu
** File description:
** Play.cpp
*/

#include "Play.hpp"

rtype::Play::Play()
{
    this->_event = rtype::sfml->event;
    this->_isPressed = false;
}

void rtype::Play::run()
{
    while (rtype::sfml->window->isOpen())
    {
        rtype::sfml->window->clear();
        this->background("assets/img/back.jpg");
        rtype::sfml->window->display();
    }
    
}