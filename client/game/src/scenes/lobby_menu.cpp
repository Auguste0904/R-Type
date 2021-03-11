/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** main.cpp
*/

#include "Game.hpp"
#include "scenes.hpp"
#include "UDPClient.hpp"
#include <string>

void main_menu_background(void);
void settings_menu_logo(void);
void playSound(const std::string &path, const game::uint32 &volume);
void test_player(void);
// player_t generate_player(const std::string &path, const sf::Vector2f &position, const sf::Vector2f &scale, const std::string &label);

std::string PLAYER_ID = "";

void print_timer(const std::string &string)
{
    auto &text = game::Game::getEngine()->componentManager().getHashComponents(typeid(text_t).hash_code());
    text_t timer;

    for (size_t i = 0; i < text.size(); i++) {
        timer = std::any_cast<text_t>(text[i].second);
        if (timer.label == "timer") {
            timer.text.setString(string);
            text[i].second = std::any(timer);
            return;
        }
    }

    game::int32 id = game::Game::getEngine()->entityManager().addEntity();
    timer.font = std::make_shared<sf::Font>();
    timer.font->loadFromFile("./assets/font/Symtext.ttf");
    timer.text.setFont(*(timer.font));
    timer.text.setString(string);
    timer.label = "timer";
    timer.text.setCharacterSize(50);
    timer.text.setPosition(sf::Vector2f(500, 500));
    timer.text.setFillColor(sf::Color(255, 255, 255));
    game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, timer));
}

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

void test_clb(void)
{
    playSound("./assets/musics/valid.ogg", 100);
    std::string a = udpClient_g.getLobbyData();
    std::cout << "|" << a << "|" << std::endl;
    int nbPlayers = 1;
    if (a[0] != 's') {
        auto splited_str = split(a, ";");
        int current_time = std::stoi(splited_str[1], nullptr, 10);
        nbPlayers = std::stoi(splited_str[2], nullptr, 10); // POur toi gugus
        int total_time = std::stoi(splited_str[3], nullptr, 10);

        print_timer("Time remaining: " + std::to_string(total_time - current_time));
        std::vector<std::string> color = {"red", "blue", "yellow", "green"};
        // for (int i = 0; i <= nbPlayers; i++) {
        //     // <<< LA TU AFFICHES LES VAISEAU !!
        //     /* test_player(); */
        // }
    } else {
        game::Game::getEngine()->setCallback(NULL);
        std::string b = udpClient_g.getLobbyData();
        if (b[0] == 'I') {
            PLAYER_ID = b;
            std::cout << PLAYER_ID << std::endl;
            sleep(1);
        }
        game_loop();
        throw (game::exception::ChangeScene());
    }
}

void lobby_menu(void)
{
    game::Game::getEngine()->entityManager().clear();
    game::Game::getEngine()->loadLibrary("./lib/libsprite.so");
    game::Game::getEngine()->loadLibrary("./lib/libbutton.so");
    game::Game::getEngine()->loadLibrary("./lib/libtext.so");
    main_menu_background();
    settings_menu_logo();
    game::Game::getEngine()->setCallback(&test_clb);
    throw (game::exception::ChangeScene());
}
