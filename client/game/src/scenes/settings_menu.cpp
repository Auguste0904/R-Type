/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** main.cpp
*/

#include "Game.hpp"
#include "scenes.hpp"

void playSound(const std::string &path, const game::uint32 &volume);

void settings_back_button_callback(void)
{
    playSound("./assets/musics/valid.ogg", 100);
    main_menu();
    throw (game::exception::ChangeScene());
}

void settings_back_button(void)
{
    button_t tmp = {std::make_shared<sf::Texture>(), sf::Sprite(), std::make_shared<sf::Texture>(), sf::Sprite(), settings_back_button_callback};
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

sprite_t generate_sprite_settings(const game::int32 &z_index, const std::string &path,
const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Vector2f &scale = sf::Vector2f(1, 1))
{
    sprite_t tmp;
    tmp.z_index = z_index;
    tmp.texture = std::make_shared<sf::Texture>();
    tmp.texture->loadFromFile(path);
    tmp.sprite.setTexture(*(tmp.texture));
    tmp.sprite.setPosition(position);
    tmp.sprite.setScale(scale);
    return (tmp);
}

void settings_menu_background(void)
{
    sprite_t background = generate_sprite_settings(1, "./assets/background_stars.jpeg");
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, background));
}

void settings_menu_logo(void)
{
    sprite_t logo = generate_sprite_settings(2, "./assets/rtype.png", sf::Vector2f(650, 80), sf::Vector2f(2, 2));
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, logo));
}

void settings_menu_button_1920_callback(void)
{
    playSound("./assets/musics/valid.ogg", 100);
    std::cout << "1920 x 1080" << std::endl;
    game::Game::getEngine()->setResolution(sf::Vector2i(1920, 1080));
}

void settings_menu_1920(void)
{
    button_t tmp = {std::make_shared<sf::Texture>(), sf::Sprite(), std::make_shared<sf::Texture>(), sf::Sprite(), settings_menu_button_1920_callback};
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    tmp.texture_1->loadFromFile("./assets/img2/1920x1080_1.png");
    tmp.sprite_1.setTexture(*(tmp.texture_1));
    tmp.sprite_1.setPosition(sf::Vector2f(800, 450));
    tmp.sprite_1.setScale(sf::Vector2f(0.5, 0.5));
    tmp.texture_2->loadFromFile("./assets/img2/1920x1080_2.png");
    tmp.sprite_2.setTexture(*(tmp.texture_2));
    tmp.sprite_2.setPosition(sf::Vector2f(800, 450));
    tmp.sprite_2.setScale(sf::Vector2f(0.5, 0.5));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, tmp));
}

void settings_menu_button_1366_callback(void)
{
    playSound("./assets/musics/valid.ogg", 100);
    std::cout << "1366 x 768" << std::endl;
    game::Game::getEngine()->setResolution(sf::Vector2i(1366, 768));
}

void settings_menu_1366(void)
{
    button_t tmp = {std::make_shared<sf::Texture>(), sf::Sprite(), std::make_shared<sf::Texture>(), sf::Sprite(), settings_menu_button_1366_callback};
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    tmp.texture_1->loadFromFile("./assets/img2/1366x768_1.png");
    tmp.sprite_1.setTexture(*(tmp.texture_1));
    tmp.sprite_1.setPosition(sf::Vector2f(800, 600));
    tmp.sprite_1.setScale(sf::Vector2f(0.5, 0.5));
    tmp.texture_2->loadFromFile("./assets/img2/1366x768_2.png");
    tmp.sprite_2.setTexture(*(tmp.texture_2));
    tmp.sprite_2.setPosition(sf::Vector2f(800, 600));
    tmp.sprite_2.setScale(sf::Vector2f(0.5, 0.5));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, tmp));
}

void settings_menu_button_1280_callback(void)
{
    playSound("./assets/musics/valid.ogg", 100);
    std::cout << "1280 x 720" << std::endl;
    game::Game::getEngine()->setResolution(sf::Vector2i(1280, 720));
}

void settings_menu_1280(void)
{
    button_t tmp = {std::make_shared<sf::Texture>(), sf::Sprite(), std::make_shared<sf::Texture>(), sf::Sprite(), settings_menu_button_1280_callback};
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    tmp.texture_1->loadFromFile("./assets/img2/1280x720_1.png");
    tmp.sprite_1.setTexture(*(tmp.texture_1));
    tmp.sprite_1.setPosition(sf::Vector2f(800, 750));
    tmp.sprite_1.setScale(sf::Vector2f(0.5, 0.5));
    tmp.texture_2->loadFromFile("./assets/img2/1280x720_2.png");
    tmp.sprite_2.setTexture(*(tmp.texture_2));
    tmp.sprite_2.setPosition(sf::Vector2f(800, 750));
    tmp.sprite_2.setScale(sf::Vector2f(0.5, 0.5));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, tmp));
}

void settings_menu(void)
{
    game::Game::getEngine()->entityManager().clear();
    game::Game::getEngine()->loadLibrary("./lib/libsprite.so");
    game::Game::getEngine()->loadLibrary("./lib/libbutton.so");
    game::Game::getEngine()->loadLibrary("./lib/libslider.so");
    settings_menu_background();
    settings_menu_logo();
    settings_back_button();
    settings_menu_1920();
    settings_menu_1366();
    settings_menu_1280();
    throw (game::exception::ChangeScene());
}
