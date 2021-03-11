/*
** EPITECH PROJECT, 2020
** menu
** File description:
** AMenu.cpp
*/

#include "AMenu.hpp"

void rtype::AMenu::run()
{
    ;
}

void rtype::AMenu::background(const std::string &path)
{
    sf::Sprite sprite;
    sf::Texture texture;

    if (path.length() < 1)
        throw rtype::Exception("Error: bad background path");
    if (!texture.loadFromFile(path))
        throw rtype::Exception("Error: bad texture construction");
    sprite.setTexture(texture);
    rtype::sfml->window->draw(sprite);
}

void rtype::AMenu::image(float x, float y, const std::string &path, float scale_x, float scale_y)
{
    sf::Sprite sprite;
    sf::Texture texture;

    if (path.length() < 1)
        throw rtype::Exception("Error: bad background path");
    if (!texture.loadFromFile(path))
        throw rtype::Exception("Error: bad texture construction");
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(x, y));
    sprite.setScale(sf::Vector2f(scale_x, scale_y));
    rtype::sfml->window->draw(sprite);
}

void rtype::AMenu::text(float x, float y, const std::string &str, unsigned int characterSize, sf::Color color)
{
    sf::Text text;
    sf::Font font;

    if (!font.loadFromFile("assets/font/Symtext.ttf"))
        throw rtype::Exception("Error: bad font construction");
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setPosition(sf::Vector2f(x, y));
    text.setFillColor(color);
    text.setString(str);
    rtype::sfml->window->draw(text);
}

rtype::AMenu::~AMenu()
{
    ;
}