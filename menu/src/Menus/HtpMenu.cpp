/*
** EPITECH PROJECT, 2020
** menu
** File description:
** HtpMenu.cpp
*/

#include "HtpMenu.hpp"

rtype::HtpMenu::HtpMenu()
{
    this->_event = rtype::sfml->event;
    this->_isPressed = false;
}

void rtype::HtpMenu::manage_event_menu()
{
    while (rtype::sfml->window->pollEvent(this->_event)) {
        if (this->_event.type == this->_event.Closed)
            rtype::sfml->window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->_isPressed == false)
            this->_isPressed = true;
    }
}

void rtype::HtpMenu::run()
{
    while (rtype::sfml->window->isOpen())
    {
        rtype::sfml->window->clear();
        this->manage_event_menu();
        if (this->_isPressed == true)
            break;
        this->background("assets/img/back.jpg");
        // this->image(225, 40, "assets/img/htp.png", 1, 1);
        this->text(10, 50, HTP, 80, sf::Color::Blue);
        rtype::sfml->window->display();
    }
}