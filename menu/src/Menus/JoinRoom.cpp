/*
** EPITECH PROJECT, 2020
** menu
** File description:
** JoinRoom.cpp
*/

#include "JoinRoom.hpp"

rtype::JoinRoom::JoinRoom() {
    this->_event = rtype::sfml->event;
    this->_isPressed = false;
};

void rtype::JoinRoom::manage_event() {
    while (rtype::sfml->window->pollEvent(this->_event)) {
        if (this->_event.type == this->_event.Closed)
            rtype::sfml->window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            this->_isPressed = true;
    }
};

std::string rtype::JoinRoom::enter_text() 
{
    std::string str;

    if (this->_event.type == sf::Event::TextEntered)
    {
        if (_event.text.unicode < 128) {
            str = str + static_cast<char>(_event.text.unicode);
        }
        //std::cout << "str = " + str << std::endl;
        //this->text(10, 50, str, 80, sf::Color::Blue);
    }
    return str;
}

void rtype::JoinRoom::run() {
    while (rtype::sfml->window->isOpen())
    {
        rtype::sfml->window->clear();
        this->manage_event();
        if (this->_isPressed == true)
            break;
        this->background("assets/img/back.jpg");
        //std::string str = this->enter_text();
        //std::cout << " str =* " + str << std::endl;
        rtype::sfml->window->display();
    }
};