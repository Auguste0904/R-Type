/*
** EPITECH PROJECT, 2020
** menu
** File description:
** Play.cpp
*/

#include "RoomManagement.hpp"
#include "CreateRoom.hpp"
#include "JoinRoom.hpp"

rtype::RoomManagement::RoomManagement()
{
    this->_event = rtype::sfml->event;
    this->_isPressed = false;
}

void rtype::RoomManagement::manage_event()
{
    while(rtype::sfml->window->pollEvent(this->_event)) {
        if (this->_event.type == this->_event.Closed)
            rtype::sfml->window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->_isPressed == false)
            this->_isPressed = true;
    }
}

void rtype::RoomManagement::runCreateRoom()
{
    std::cout << "create room" << std::endl;
    std::unique_ptr<rtype::CreateRoom> createRoom = std::make_unique<rtype::CreateRoom>();
    createRoom->run();

};

void rtype::RoomManagement::runJoinRoom()
{
    std::cout << "join room" << std::endl;
    std::unique_ptr<rtype::JoinRoom> joinRoom = std::make_unique<rtype::JoinRoom>();
    joinRoom->run();
};

void rtype::RoomManagement::run()
{
    while (rtype::sfml->window->isOpen())
    {
        rtype::sfml->window->clear();
        this->manage_event();
        if (this->_isPressed == true)
            break;
        this->background("assets/img/back.jpg");
        this->image(375, 100, "assets/img2/room_management.png", 1.5, 1.5);
        this->button(700, 400, 1, 1, this, &rtype::RoomManagement::runJoinRoom, "assets/img2/join_a_room_1.png", "assets/img2/join_a_room_2.png");
        this->button(650, 700, 1, 1, this, &rtype::RoomManagement::runCreateRoom, "assets/img2/create_a_room_1.png", "assets/img2/create_a_room_2.png");
        rtype::sfml->window->display();
    }
    
};