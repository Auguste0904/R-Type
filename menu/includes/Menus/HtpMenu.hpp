/*
** EPITECH PROJECT, 2020
** menu
** File description:
** HtpMenu.hpp
*/

#ifndef HTPMENU_HPP__
#define HTPMENU_HPP__

#include "AMenu.hpp"

#define HTP "WESH J'ECRIS DANS LE DEFINE\n DANS LE HPP"

namespace rtype
{
    class HtpMenu : public AMenu
    {
        public:
            HtpMenu();
            virtual ~HtpMenu() = default;
            void run();
            void manage_event_menu();
        private:
            sf::Event _event;
            bool _isPressed;
    };
}

#endif