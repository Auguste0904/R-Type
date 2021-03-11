/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** main.cpp
*/

#include "Game.hpp"
#include "scenes.hpp"

void main_menu_background(void);
void playSound(const std::string &path, const game::uint32 &volume);

void game_over_text(void)
{
    text_t text;
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    text.font = std::make_shared<sf::Font>();
    text.font->loadFromFile("./assets/font/Symtext.ttf");
    text.text.setFont(*(text.font));
    text.text.setString("              GAME OVER !\n\n\n\n   Click on the arrow button\nto come back to the main menu");
    text.text.setCharacterSize(60);
    text.text.setPosition(sf::Vector2f(420, 1080 / 6));
    text.text.setFillColor(sf::Color(0, 97, 227));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, text));
}

void game_over_back_button_callback(void)
{
    playSound("./assets/musics/valid.ogg", 100);
    main_menu();
    throw (game::exception::ChangeScene());
}

void game_over_back_button(void)
{
    button_t tmp = {std::make_shared<sf::Texture>(), sf::Sprite(), std::make_shared<sf::Texture>(), sf::Sprite(), game_over_back_button_callback};
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    tmp.texture_1->loadFromFile("./assets/img2/arrow_1.png");
    tmp.sprite_1.setTexture(*(tmp.texture_1));
    tmp.sprite_1.setPosition(sf::Vector2f(20, 20));
    tmp.sprite_1.setScale(sf::Vector2f(0.15, 0.15));
    tmp.texture_2->loadFromFile("./assets/img2/arrow_2.png");
    tmp.sprite_2.setTexture(*(tmp.texture_2));
    tmp.sprite_2.setPosition(sf::Vector2f(20, 20));
    tmp.sprite_2.setScale(sf::Vector2f(0.15, 0.15));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, tmp));
}

void game_over(void)
{
    game::Game::getEngine()->entityManager().clear();
    game::Game::getEngine()->loadLibrary("./lib/libsprite.so");
    game::Game::getEngine()->loadLibrary("./lib/libbutton.so");
    game::Game::getEngine()->loadLibrary("./lib/libtext.so");
    main_menu_background();
    game_over_text();
    game_over_back_button();
    throw (game::exception::ChangeScene());
}
