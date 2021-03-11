/*
** EPITECH PROJECT, 2020
** menu
** File description:
** SettingsMenu.cpp
*/

#include "SettingsMenu.hpp"

rtype::SettingsMenu::SettingsMenu()
{
    this->_event = rtype::sfml->event;
    this->_isEscPressed = false;
    this->_isReleased = false;
    this->_isClicked = false;
}

void rtype::SettingsMenu::clickMute(int pos_x, int pos_y, float scale_x, float scale_y)
{
    sf::Texture texture;
    auto cursor = rtype::sfml->mouse.getPosition();

    // if (this->_isReleased == true)
    //     this->_isReleased = false;
    // std::cout << "State 2: " << this->_isClicked << ", " << this->_isReleased << std::endl;
    if (!texture.loadFromFile("assets/img/mute_2.png"))
        throw rtype::Exception("Error: bad loaded texture");
    auto size = texture.getSize();
    this->image(pos_x, pos_y, "assets/img/mute_2.png", scale_x, scale_y);
    if ((cursor.x > pos_x && cursor.x < pos_x + (size.x * scale_x)) && (cursor.y > pos_y && cursor.y < pos_y + (size.y * scale_y))) {
        this->image(pos_x, pos_y, "assets/img/mute_2.png", scale_x, scale_y);
        if (this->_event.type == this->_event.MouseButtonPressed && this->_event.mouseButton.button == sf::Mouse::Left && this->_isClicked == false)
            this->_isClicked = true;
        if (this->_event.type == this->_event.MouseButtonReleased && this->_event.mouseButton.button == sf::Mouse::Left && this->_isClicked == true) {
            this->_isReleased = true;
            this->_isClicked = false;
        }
    }
}

void rtype::SettingsMenu::clickVolume(int pos_x, int pos_y, float scale_x, float scale_y)
{
    sf::Texture texture;
    auto cursor = rtype::sfml->mouse.getPosition();

    // if (this->_isReleased == true)
    //     this->_isReleased = false;
    // std::cout << "State 1: " << this->_isClicked << ", " << this->_isReleased << std::endl;
    if (!texture.loadFromFile("assets/img/volume_2.png"))
        throw rtype::Exception("Error: bad loaded texture");
    auto size = texture.getSize();
    this->image(pos_x, pos_y, "assets/img/volume_2.png", scale_x, scale_y);
    if ((cursor.x > pos_x && cursor.x < pos_x + (size.x * scale_x)) && (cursor.y > pos_y && cursor.y < pos_y + (size.y * scale_y))) {
        this->image(pos_x, pos_y, "assets/img/volume_2.png", scale_x, scale_y);
        if (this->_event.type == this->_event.MouseButtonPressed && this->_event.mouseButton.button == sf::Mouse::Left && this->_isClicked == false)
            this->_isClicked = true;
        if (this->_event.type == this->_event.MouseButtonReleased && this->_event.mouseButton.button == sf::Mouse::Left && this->_isClicked == true) {
            this->_isReleased = true;
            this->_isClicked = false;
        }
    }
}

void rtype::SettingsMenu::w1920x1080()
{
    std::cout << "RESIZE 1920 x 1080" << std::endl;
    rtype::sfml->window->close();
    rtype::sfml->window->create(sf::VideoMode(1920, 1080), "R-Type", sf::Style::Close | sf::Style::Resize);
    rtype::sfml->window->setFramerateLimit(60);
}

void rtype::SettingsMenu::w1366x768()
{
    std::cout << "RESIZE 1366 x 768" << std::endl;
    rtype::sfml->window->close();
    rtype::sfml->window->create(sf::VideoMode(1366, 768), "R-Type", sf::Style::Close | sf::Style::Resize);
    rtype::sfml->window->setFramerateLimit(60);
}

void rtype::SettingsMenu::w1280x720()
{
    std::cout << "RESIZE 1280 x 720" << std::endl;
    rtype::sfml->window->close();
    rtype::sfml->window->create(sf::VideoMode(1280, 720), "R-Type", sf::Style::Close | sf::Style::Resize);
    rtype::sfml->window->setFramerateLimit(60);
}

void rtype::SettingsMenu::manage_event_menu()
{
    while (rtype::sfml->window->pollEvent(this->_event)) {
        if (this->_event.type == this->_event.Closed)
            rtype::sfml->window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->_isEscPressed == false)
            this->_isEscPressed = true;
    }
}

void rtype::SettingsMenu::run()
{
    while (rtype::sfml->window->isOpen())
    {
        rtype::sfml->window->clear();
        this->manage_event_menu();
        if (this->_isEscPressed == true)
            break;
        this->background("assets/img/back.jpg");
        (this->_isReleased == true && this->_isClicked == true) ? this->clickMute(1350, 400, 0.1, 0.1) : this->clickVolume(1350, 400, 0.1, 0.1);
        this->button(800, 450, 0.5, 0.5, this, &rtype::SettingsMenu::w1920x1080, "assets/img/1920x1080_1.png", "assets/img/1920x1080_2.png");
        this->button(800, 600, 0.5, 0.5, this, &rtype::SettingsMenu::w1366x768, "assets/img/1366x768_1.png", "assets/img/1366x768_2.png");
        this->button(800, 750, 0.5, 0.5, this, &rtype::SettingsMenu::w1280x720, "assets/img/1280x720_1.png", "assets/img/1280x720_2.png");
        rtype::sfml->window->display();
    }
}