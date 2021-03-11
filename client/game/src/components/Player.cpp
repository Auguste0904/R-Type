/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Player.cpp
*/

#include "Game.hpp"
#include "UDPClient.hpp"
#include <string>

typedef struct player_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    std::string label;
    game::uint32 hp;
    sf::Clock fire;
} player_t;

typedef struct rocket_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    sf::Clock clock;
    bool destroyed;
} rocket_t;

std::vector<std::string> split(const std::string& str, const std::string& delim);
player_t generate_player(const std::string &path, const sf::Vector2f &position, const sf::Vector2f &scale, const std::string &label);

void playerManager(void)
{
    static bool init = false;

    if (init == false) {
        std::string data = udpClient_g.recvStr(64); // METTRE DATA PLAYER !!!!!!!!
        std::cout << "Data players init: " << data << std::endl;
        std::vector<std::string> parsed = split(data, ";");
        const std::vector<std::string> labels = {"blue", "red", "yellow", "green"};

        auto &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(player_t).hash_code());
        while (components.size() < parsed.size()) {
            std::vector<std::string> parsed_parsed = split(parsed[components.size()], ":");
            player_t play = generate_player("assets/sprites/vaisseau1_L-to-R.png", sf::Vector2f(std::stoi(parsed_parsed[0], nullptr, 10), std::stoi(parsed_parsed[1], nullptr, 10)), sf::Vector2f(3, 3), labels[components.size()]);
            game::int32 id = game::Game::getEngine()->entityManager().addEntity();
            game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, play));
        }
        init = true;
    }
}

extern std::string PLAYER_ID;

void systemPlayer(void)
{
    playerManager();
    auto &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(player_t).hash_code());
    static sf::Clock clock;
    const float speed = 7;
    std::string data_player = "";

    bool move = false;
    if (clock.getElapsedTime().asMilliseconds() >= (1000 / 30)) {
        clock.restart();
        move = true;
    }
    std::string moves = "";
    if (move) {
        // read server
        auto s = udpClient_g.recvStr(64);
        data_player = s; // METTRE data_player !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        std::cout << "Data players: " << data_player << std::endl;
        if (data_player != "") {
            std::vector<std::string> parsed = split(data_player, ";");
            for (size_t i = 0; i < components.size(); i++) {
                std::vector<std::string> parsed_parsed = split(parsed[i], ":");
                player_t tmp_player = std::any_cast<player_t>(components[i].second);
                tmp_player.sprite.setPosition(sf::Vector2f(std::stoi(parsed_parsed[0], nullptr, 10), std::stoi(parsed_parsed[1], nullptr, 10)));
                components[i].second = std::any(tmp_player);
            }
        }
    }
    if (move) {
        std::string moves = "";
        if (game::Game::getEngine()->getKey(sf::Keyboard::Up)) {
            moves += "u";
        }
        if (game::Game::getEngine()->getKey(sf::Keyboard::Down)) {
            moves += "d";
        }
        if (game::Game::getEngine()->getKey(sf::Keyboard::Right)) {
            moves += "r";
        }
        if (game::Game::getEngine()->getKey(sf::Keyboard::Left)) {
            moves += "l";
        }
        if (game::Game::getEngine()->getKey(sf::Keyboard::Space)) {
            moves += "s";
        }
        std::string tmpp = PLAYER_ID[2] + moves;
        udpClient_g.sendStr(tmpp);
    }
    for (size_t i = 0; i < components.size(); i++) {
        player_t data = std::any_cast<player_t>(components[i].second);
// //        std::string moves = "";
//         if (move) {
//             if (game::Game::getEngine()->getKey(sf::Keyboard::Up)) {
// //                moves += "u";
//                 if (data.sprite.getPosition().y >= speed) {
//                     data.sprite.setPosition(data.sprite.getPosition().x, data.sprite.getPosition().y - speed);
//                     data.sprite.setTextureRect(sf::IntRect(63, 0, 31, 14));
//                 }
//             }
//             if (game::Game::getEngine()->getKey(sf::Keyboard::Down)) {
// //                moves += "d";
//                 if (data.sprite.getPosition().y <= 1080 - (speed + data.sprite.getGlobalBounds().height)) {
//                     data.sprite.setPosition(data.sprite.getPosition().x, data.sprite.getPosition().y + speed);
//                     data.sprite.setTextureRect(sf::IntRect(0, 0, 31, 14));
//                 }
//             }
//             if (game::Game::getEngine()->getKey(sf::Keyboard::Left)) {
//                 // moves += "l";
//                 if (data.sprite.getPosition().x >= speed) {
//                     data.sprite.setPosition(data.sprite.getPosition().x - speed, data.sprite.getPosition().y);
//                     if (game::Game::getEngine()->getKey(sf::Keyboard::Up) == false && game::Game::getEngine()->getKey(sf::Keyboard::Down) == false)
//                         data.sprite.setTextureRect(sf::IntRect(31, 0, 32, 14));
//                 }
//             }
//             if (game::Game::getEngine()->getKey(sf::Keyboard::Right)) {
//                 // moves += "r";
//                 if (data.sprite.getPosition().x <= 1920 / 2) {
//                     data.sprite.setPosition(data.sprite.getPosition().x + speed, data.sprite.getPosition().y);
//                     if (game::Game::getEngine()->getKey(sf::Keyboard::Up) == false && game::Game::getEngine()->getKey(sf::Keyboard::Down) == false)
//                         data.sprite.setTextureRect(sf::IntRect(31, 0, 32, 14));
//                 }
//             }
//             if (game::Game::getEngine()->getKey(sf::Keyboard::Space)) {
//                 if (data.fire.getElapsedTime().asMilliseconds() >= 200) {
//                     data.fire.restart();
//                     rocket_t rocket;
//                     rocket.destroyed = false;
//                     rocket.texture = std::make_shared<sf::Texture>();
//                     rocket.texture->loadFromFile("assets/sprites/r-typesheet1.png");
//                     rocket.sprite.setTexture(*(rocket.texture));
//                     rocket.sprite.setScale(sf::Vector2f(2.5, 2.5));
//                     rocket.sprite.setPosition(sf::Vector2f(data.sprite.getPosition().x + 20, data.sprite.getPosition().y + 5));
//                     rocket.sprite.setTextureRect(sf::IntRect(248, 88, 10, 4));
//                     game::int32 id = game::Game::getEngine()->entityManager().addEntity();
//                     game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, rocket));
//                 }
//             }
//             /* udpClient_g.sendStr(moves); */
//             components[i].second = std::any(data);
//         }
        if (data.label == "blue")
            data.sprite.setColor(sf::Color(200, 200, 255, 255));
        else if (data.label == "red")
            data.sprite.setColor(sf::Color(255, 200, 200, 255));
        else if (data.label == "yellow")
            data.sprite.setColor(sf::Color(255, 255, 200, 255));
        else if (data.label == "green")
            data.sprite.setColor(sf::Color(200, 255, 200, 255));
        game::Game::getEngine()->getWindow()->draw(data.sprite);
    }
}

#ifdef __DEBUG
void __attribute__((destructor)) destruct(void)
{
    std::cout << "[Destruct] player" << std::endl;
}
#endif

void __attribute__((constructor)) construct(void)
{
#ifdef __DEBUG
    std::cout << "[Construct] player" << std::endl;
#endif
    game::Game::getEngine()->systemManager().declareSystem(systemPlayer);
}
