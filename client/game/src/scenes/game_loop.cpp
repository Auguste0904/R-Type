/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** main.cpp
*/

#include "Game.hpp"
#include "scenes.hpp"
#include "UDPClient.hpp"
#include <vector>

void playSound(const std::string &path, const game::uint32 &volume);

parallax_t generate_parallax(const game::int32 &z_index, const std::string &path,
const sf::Vector2f &position = sf::Vector2f(0, 0), const sf::Vector2f &scale = sf::Vector2f(1, 1), const float &speed = 0)
{
    parallax_t tmp;
    tmp.z_index = z_index;
    tmp.texture = std::make_shared<sf::Texture>();
    tmp.texture->loadFromFile(path);
    tmp.sprite.setTexture(*(tmp.texture));
    tmp.sprite.setPosition(position);
    tmp.sprite.setScale(scale);
    tmp.speed = speed;
    return (tmp);
}

player_t generate_player(
                    const std::string &path,
                    const sf::Vector2f &position = sf::Vector2f(0, 0),
                    const sf::Vector2f &scale = sf::Vector2f(1, 1),
                    const std::string &label = "")
{
    player_t tmp;
    tmp.texture = std::make_shared<sf::Texture>();
    tmp.texture->loadFromFile(path);
    tmp.sprite.setTexture(*(tmp.texture));
    tmp.sprite.setPosition(position);
    tmp.sprite.setScale(scale);
    tmp.label = label;
    tmp.hp = 100;
    tmp.sprite.setTextureRect(sf::IntRect(31, 0, 32, 14));
    return (tmp);
}

void parallax_background(void)
{
    parallax_t background = generate_parallax(1, "./assets/img2/parallax/background.png", sf::Vector2f(0, 0), sf::Vector2f(2.4, 2.4), -0.5);
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, background));
}

void parallax_planet_1(void)
{
    parallax_t background = generate_parallax(5, "./assets/img2/parallax/planet_1.png", sf::Vector2f(200, 600), sf::Vector2f(2.5, 2.5), -1.5);
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, background));
}

void parallax_planet_2(void)
{
    parallax_t background = generate_parallax(3, "./assets/img2/parallax/planet_2.png", sf::Vector2f(800, 300), sf::Vector2f(2.5, 2.5), -2);
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, background));
}

void parallax_planet_3(void)
{
    parallax_t background = generate_parallax(4, "./assets/img2/parallax/planet_3.png", sf::Vector2f(1300, 20), sf::Vector2f(2.5, 2.5), -2.5);
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, background));
}

void parallax_planet_4(void)
{
    parallax_t background = generate_parallax(2, "./assets/img2/parallax/planet_4.png", sf::Vector2f(1800, 900), sf::Vector2f(2.5, 2.5), -1);
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, background));
}

void test_player()
{
    player_t play = generate_player("assets/sprites/vaisseau1_L-to-R.png", sf::Vector2f(200, 500), sf::Vector2f(3, 3), "red");
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, play));
}

void test_rocket(void)
{
    rocket_t rocket;
    rocket.destroyed = false;
    rocket.texture = std::make_shared<sf::Texture>();
    rocket.texture->loadFromFile("assets/sprites/r-typesheet1.png");
    rocket.sprite.setTexture(*(rocket.texture));
    rocket.sprite.setScale(sf::Vector2f(2.5, 2.5));
    rocket.sprite.setPosition(sf::Vector2f(500, 500));
    rocket.sprite.setTextureRect(sf::IntRect(248, 88, 10, 4));
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, rocket));
}

void game_loop()
{
    game::Game::getEngine()->entityManager().clear();
    game::Game::getEngine()->loadLibrary("./lib/libtext.so");

    game::Game::getEngine()->loadLibrary("./lib/libparallax.so");
    game::Game::getEngine()->loadLibrary("./lib/libplayer.so");
    game::Game::getEngine()->loadLibrary("./lib/librocket.so");
    game::Game::getEngine()->loadLibrary("./lib/libenemy1.so");
    game::Game::getEngine()->loadLibrary("./lib/librocketEnemy.so");
    game::Game::getEngine()->loadLibrary("./lib/libmobspawner.so");
    game::Game::getEngine()->loadLibrary("./lib/libboss.so");
    parallax_background();
    parallax_planet_4();
    parallax_planet_2();
    parallax_planet_3();
    parallax_planet_1();

    #ifdef __SINGLEPLAYER
    test_player();
    #endif
    throw (game::exception::ChangeScene());
}
