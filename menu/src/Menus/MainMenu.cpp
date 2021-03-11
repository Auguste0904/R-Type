/*
** EPITECH PROJECT, 2020
** menu
** File description:
** MainMenu.cpp
*/

//join room
//create room

#include "MainMenu.hpp"
#include "SettingsMenu.hpp"
#include "HtpMenu.hpp"
#include "RoomManagement.hpp"

rtype::MainMenu::MainMenu()
{
    this->_event = rtype::sfml->event;
}

void rtype::MainMenu::runPlay()
{
    std::cout << "PLAY MENU !!!" << std::endl;
    std::cout << sf::VideoMode::getDesktopMode().width << std::endl;
    std::cout << sf::VideoMode::getDesktopMode().height << std::endl;

    std::unique_ptr<rtype::RoomManagement> roomManagement = std::make_unique<rtype::RoomManagement>();
    roomManagement->run();

}

void rtype::MainMenu::runSettings()
{
    std::unique_ptr<rtype::SettingsMenu> settingsMenu = std::make_unique<rtype::SettingsMenu>();
    settingsMenu->run();
}

void rtype::MainMenu::runHtp()
{
    std::unique_ptr<rtype::HtpMenu> htpMenu = std::make_unique<rtype::HtpMenu>();
    htpMenu->run();
}

void rtype::MainMenu::runExit()
{
    rtype::sfml->window->close();
}

void rtype::MainMenu::manage_event_menu()
{
    while (rtype::sfml->window->pollEvent(this->_event)) {
        if (this->_event.type == this->_event.Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            rtype::sfml->window->close();
    }
}

void rtype::MainMenu::run()
{
    while (rtype::sfml->window->isOpen())
    {
        rtype::sfml->window->clear();
        this->manage_event_menu();
        this->background("assets/img/back.jpg");
        this->image(1100, 100, "assets/img2/annonce_1.png", 0.75, 0.75);
        this->button(1600, 300, 0.5, 0.5, this, &rtype::MainMenu::runPlay, "assets/img2/start_game1.png", "assets/img2/start_game2.png");
        this->button(1700, 350, 0.5, 0.5, this, &rtype::MainMenu::runSettings, "assets/img2/options1.png", "assets/img2/options2.png");
        this->button(1550, 400, 0.5, 0.5, this, &rtype::MainMenu::runHtp, "assets/img2/how_to_play_1.png", "assets/img2/how_to_play_2.png");
        this->button(1780, 450, 0.5, 0.5, this, &rtype::MainMenu::runExit, "assets/img2/exit_1.png", "assets/img2/exit_2.png");
        this->image(550, 550, "assets/img2/rtype.png", 4, 4);
        this->image(900, 850, "assets/img2/text1.png", 0.75, 0.75);
        rtype::sfml->window->display();
    }
}