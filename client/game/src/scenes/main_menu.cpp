/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** main.cpp
*/

#include "Game.hpp"
#include "scenes.hpp"
#include "Game.hpp"

void playSound(const std::string &path, const game::uint32 &volume)
{
    game::Game::getEngine()->openSound(path);
    game::Game::getEngine()->setSoundVolume(volume);
    game::Game::getEngine()->playSound();
}

sprite_t generate_sprite(const game::int32 &z_index, const std::string &path,
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

void main_menu_background(void)
{
    sprite_t background = generate_sprite(1, "./assets/background_stars.jpeg");
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, background));
}

void main_menu_logo(void)
{
    sprite_t logo = generate_sprite(2, "./assets/rtype.png", sf::Vector2f(550, 550), sf::Vector2f(4, 4));
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, logo));
}

void main_menu_intro(void)
{
    sprite_t intro = generate_sprite(2, "./assets/img2/annonce_1.png", sf::Vector2f(1100, 100), sf::Vector2f(0.75, 0.75));
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, intro));
}

void main_menu_outro(void)
{
    sprite_t outro = generate_sprite(2, "./assets/img2/text1.png", sf::Vector2f(900, 850), sf::Vector2f(0.75, 0.75));
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, outro));
}

void main_menu_button_start_callback(void)
{
    playSound("./assets/musics/valid.ogg", 100);
    #ifdef __SINGLEPLAYER
    game_loop();
    #else
    connect_menu();
    #endif
}

void main_menu_button_start(void)
{
    button_t tmp = {std::make_shared<sf::Texture>(), sf::Sprite(), std::make_shared<sf::Texture>(), sf::Sprite(), main_menu_button_start_callback};
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    tmp.texture_1->loadFromFile("./assets/img2/start_game1.png");
    tmp.sprite_1.setTexture(*(tmp.texture_1));
    tmp.sprite_1.setPosition(sf::Vector2f(1600, 300));
    tmp.sprite_1.setScale(sf::Vector2f(0.5, 0.5));
    tmp.texture_2->loadFromFile("./assets/img2/start_game2.png");
    tmp.sprite_2.setTexture(*(tmp.texture_2));
    tmp.sprite_2.setPosition(sf::Vector2f(1600, 300));
    tmp.sprite_2.setScale(sf::Vector2f(0.5, 0.5));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, tmp));
}

void main_menu_button_options_callback(void)
{
    playSound("./assets/musics/valid.ogg", 100);
    settings_menu();
}

void main_menu_options(void)
{
    button_t tmp = {std::make_shared<sf::Texture>(), sf::Sprite(), std::make_shared<sf::Texture>(), sf::Sprite(), main_menu_button_options_callback};
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    tmp.texture_1->loadFromFile("./assets/img2/options1.png");
    tmp.sprite_1.setTexture(*(tmp.texture_1));
    tmp.sprite_1.setPosition(sf::Vector2f(1700, 350));
    tmp.sprite_1.setScale(sf::Vector2f(0.5, 0.5));
    tmp.texture_2->loadFromFile("./assets/img2/options2.png");
    tmp.sprite_2.setTexture(*(tmp.texture_2));
    tmp.sprite_2.setPosition(sf::Vector2f(1700, 350));
    tmp.sprite_2.setScale(sf::Vector2f(0.5, 0.5));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, tmp));
}

void main_menu_button_htp_callback(void)
{
    playSound("./assets/musics/valid.ogg", 100);
    htp_menu();
}

void main_menu_htp(void)
{
    button_t tmp = {std::make_shared<sf::Texture>(), sf::Sprite(), std::make_shared<sf::Texture>(), sf::Sprite(), main_menu_button_htp_callback};
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    tmp.texture_1->loadFromFile("./assets/img2/how_to_play_1.png");
    tmp.sprite_1.setTexture(*(tmp.texture_1));
    tmp.sprite_1.setPosition(sf::Vector2f(1550, 400));
    tmp.sprite_1.setScale(sf::Vector2f(0.5, 0.5));
    tmp.texture_2->loadFromFile("./assets/img2/how_to_play_2.png");
    tmp.sprite_2.setTexture(*(tmp.texture_2));
    tmp.sprite_2.setPosition(sf::Vector2f(1550, 400));
    tmp.sprite_2.setScale(sf::Vector2f(0.5, 0.5));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, tmp));
}

void main_menu_button_exit_callback(void)
{
    game::Game::getEngine()->close();
}

void main_menu_exit(void)
{
    button_t tmp = {std::make_shared<sf::Texture>(), sf::Sprite(), std::make_shared<sf::Texture>(), sf::Sprite(), main_menu_button_exit_callback};
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    tmp.texture_1->loadFromFile("./assets/img2/exit_1.png");
    tmp.sprite_1.setTexture(*(tmp.texture_1));
    tmp.sprite_1.setPosition(sf::Vector2f(1780, 450));
    tmp.sprite_1.setScale(sf::Vector2f(0.5, 0.5));
    tmp.texture_2->loadFromFile("./assets/img2/exit_2.png");
    tmp.sprite_2.setTexture(*(tmp.texture_2));
    tmp.sprite_2.setPosition(sf::Vector2f(1780, 450));
    tmp.sprite_2.setScale(sf::Vector2f(0.5, 0.5));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, tmp));
}

void main_menu(void)
{
    game::Game::getEngine()->entityManager().clear();
    game::Game::getEngine()->loadLibrary("./lib/libsprite.so");
    game::Game::getEngine()->loadLibrary("./lib/libbutton.so");
    main_menu_background();
    // game::Game::getEngine()->setResolution(sf::Vector2i(1280, 720));
    main_menu_logo();
    main_menu_intro();
    main_menu_outro();
    main_menu_button_start();
    main_menu_options();
    main_menu_htp();
    main_menu_exit();
}
