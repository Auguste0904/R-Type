/*
** EPITECH PROJECT, 2020
** menu
** File description:
** IMenu.hpp
*/

#ifndef MAINMENU_HPP__
#define MAINMENU_HPP__

#define CENTER_ORIGIN

#include "AMenu.hpp"

namespace rtype
{
    class MainMenu : public AMenu
    {
        public:
            MainMenu();
            virtual ~MainMenu() = default;
            void run();
            void manage_event_menu();
            void runPlay();
            void runSettings();
            void runHtp();
            void runExit();
        private:
            sf::Event _event;
    };
}

#endif