/*
** EPITECH PROJECT, 2020
** menu
** File description:
** CreateRoom.cpp
*/

#include "CreateRoom.hpp"

rtype::CreateRoom::CreateRoom()
{
    this->_event = rtype::sfml->event;
    this->_isPressed = false;
};

void rtype::CreateRoom::manage_event()
{
    while (rtype::sfml->window->pollEvent(this->_event)) {
        if (this->_event.type == this->_event.Closed)
            rtype::sfml->window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            this->_isPressed = true;
    }
};

void rtype::CreateRoom::run()
{
    while (rtype::sfml->window->isOpen())
    {
        rtype::sfml->window->clear();
        this->manage_event();
        if (this->_isPressed == true)
            break;
        this->background("assets/img/back.jpg");
        rtype::sfml->window->display();
    }
    
}