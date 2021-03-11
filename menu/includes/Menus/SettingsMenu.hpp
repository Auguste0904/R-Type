/*
** EPITECH PROJECT, 2020
** menu
** File description:
** SettingsMenu.hpp
*/

#ifndef SETTINGSMENU_HPP__
#define SETTINGSMENU_HPP__

#include "AMenu.hpp"

namespace rtype
{
    class SettingsMenu : public AMenu
    {
        public:
            SettingsMenu();
            virtual ~SettingsMenu() = default;
            void run();
            void manage_event_menu();
            void w1920x1080();
            void w1366x768();
            void w1280x720();
        private:
            void clickVolume(int pos_x, int pos_y, float scale_x, float scale_y);
            void clickMute(int pos_x, int pos_y, float scale_x, float scale_y);
            sf::Event _event;
            float _ratio;
            bool _isEscPressed;
            bool _isClicked;
            bool _isReleased;
    };
}

#endif