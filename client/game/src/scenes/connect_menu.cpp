/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** main.cpp
*/

#include "Game.hpp"
#include "scenes.hpp"
#include "UDPClient.hpp"

void playSound(const std::string &path, const game::uint32 &volume);
void main_menu_background(void);

void connect_back_button_callback(void)
{
    main_menu();
    playSound("./assets/musics/valid.ogg", 100);
    throw (game::exception::ChangeScene());
}

void connect_back_button(void)
{
    button_t tmp = {std::make_shared<sf::Texture>(), sf::Sprite(), std::make_shared<sf::Texture>(), sf::Sprite(), connect_back_button_callback};
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

void connect_join_button_callback(void)
{
    std::vector<std::pair<game::int32, std::any> > &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(textarea_t).hash_code());
    std::string hostname;
    std::string port;

    playSound("./assets/musics/valid.ogg", 100);
    for (auto &component : components) {
        textarea_t textarea = std::any_cast<textarea_t>(component.second);
        if (textarea.label == "hostname")
            hostname = textarea.text;
        else if (textarea.label == "port")
            port = textarea.text;
    }
    udpClient_g.init(std::stoi(port, nullptr, 10), hostname);
    udpClient_g.connect();
    lobby_menu();
    playSound("./assets/musics/valid.ogg", 100);
    throw (game::exception::ChangeScene());
}

void connect_join_button(void)
{
    button_t tmp = {std::make_shared<sf::Texture>(), sf::Sprite(), std::make_shared<sf::Texture>(), sf::Sprite(), connect_join_button_callback};
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    tmp.texture_1->loadFromFile("./assets/img2/join_a_room_1.png");
    tmp.sprite_1.setTexture(*(tmp.texture_1));
    tmp.sprite_1.setPosition(sf::Vector2f(600, 850));
    tmp.sprite_1.setScale(sf::Vector2f(1.5, 1.5));
    tmp.texture_2->loadFromFile("./assets/img2/join_a_room_2.png");
    tmp.sprite_2.setTexture(*(tmp.texture_2));
    tmp.sprite_2.setPosition(sf::Vector2f(600, 850));
    tmp.sprite_2.setScale(sf::Vector2f(1.5, 1.5));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, tmp));
}

void connect_hostname_textarea(void)
{
    textarea_t textarea;
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    textarea.font = std::make_shared<sf::Font>();
    textarea.font->loadFromFile("./assets/font/Symtext.ttf");
    textarea.text_draw.setFillColor(sf::Color(255, 255, 255));
    textarea.text_size = 16;
    textarea.position = sf::Vector2f(300, 500);
    textarea.size = 600;
    textarea.text_draw.setFont(*(textarea.font));
    textarea.label = "hostname";
    textarea.text = "127.0.0.1";
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, textarea));
}

void connect_port_textarea(void)
{
    textarea_t textarea;
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    textarea.font = std::make_shared<sf::Font>();
    textarea.font->loadFromFile("./assets/font/Symtext.ttf");
    textarea.text_draw.setFillColor(sf::Color(255, 255, 255));
    textarea.text_size = 16;
    textarea.position = sf::Vector2f(1000, 500);
    textarea.size = 600;
    textarea.text_draw.setFont(*(textarea.font));
    textarea.label = "port";
    textarea.text = "30306";
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, textarea));
}

void connect_text_host(void)
{
    text_t text;
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    text.font = std::make_shared<sf::Font>();
    text.font->loadFromFile("./assets/font/Symtext.ttf");
    text.text.setFont(*(text.font));
    text.text.setString("Hostname");
    text.text.setCharacterSize(50);
    text.text.setPosition(sf::Vector2f(300, 400));
    text.text.setFillColor(sf::Color(0, 97, 227));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, text));
}

void connect_text_port(void)
{
    text_t text;
    game::int32 id = game::Game::getEngine()->entityManager().addEntity();

    text.font = std::make_shared<sf::Font>();
    text.font->loadFromFile("./assets/font/Symtext.ttf");
    text.text.setFont(*(text.font));
    text.text.setString("Port");
    text.text.setCharacterSize(50);
    text.text.setPosition(sf::Vector2f(1000, 400));
    text.text.setFillColor(sf::Color(0, 97, 227));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, text));
}

void connect_menu(void)
{
    game::Game::getEngine()->entityManager().clear();
    game::Game::getEngine()->loadLibrary("./lib/libsprite.so");
    game::Game::getEngine()->loadLibrary("./lib/libbutton.so");
    game::Game::getEngine()->loadLibrary("./lib/libtext.so");
    game::Game::getEngine()->loadLibrary("./lib/libtextarea.so");
    main_menu_background();
    connect_back_button();
    connect_hostname_textarea();
    connect_port_textarea();
    connect_join_button();
    connect_text_host();
    connect_text_port();
    throw (game::exception::ChangeScene());
}
