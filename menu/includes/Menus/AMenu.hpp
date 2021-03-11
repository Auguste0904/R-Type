/*
** EPITECH PROJECT, 2020
** menu
** File description:
** IMenu.hpp
*/

#ifndef AMENU_HPP__
#define AMENU_HPP__

#include "IMenu.hpp"
#include "Exception.hpp"

namespace rtype
{
    class AMenu : public IMenu
    {
    public:
        virtual ~AMenu();

        virtual void run() override;
        template <class T>
        void button(float x, float y, float scale_x, float scale_y, T *obj, void (T::*ptr)(), const std::string &path = "", const std::string &placeholder = "");
        void background(const std::string &path) override;
        void image(float x, float y, const std::string &path, float scale_x, float scale_y) override;
        void text(float x, float y, const std::string &str, unsigned int characterSize, sf::Color color) override;
    };
}

template <class T>
void rtype::AMenu::button(float x, float y, float scale_x, float scale_y, T *obj, void (T::*ptr)(), const std::string &path, const std::string &placeholder)
{
    sf::Event event = rtype::sfml->event;
    sf::Texture texture;
    auto cursor = rtype::sfml->mouse.getPosition();

    if (!texture.loadFromFile(path))
        throw rtype::Exception("Error: bad loaded texture");

    auto size = texture.getSize();
    this->image(x, y, path, scale_x, scale_y);
    if ((cursor.x > x && cursor.x < x + (size.x * scale_x)) && (cursor.y > y && cursor.y < y + (size.y * scale_y))) {
        while (rtype::sfml->window->pollEvent(event)) {
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                (obj->*ptr)();
                return;
            }
        }
        this->image(x, y, placeholder, scale_x, scale_y);
    } else {
        this->image(x, y, path, scale_x, scale_y);
    }
}

#endif