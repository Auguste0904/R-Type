/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Sprite.cpp
*/

#include "Game.hpp"

typedef struct textarea_s
{
    bool focus;
    std::string text;
    sf::Text text_draw;
    sf::Vector2f position;
    game::int32 size;
    game::int32 text_size;
    std::shared_ptr<sf::Font> font;
    std::string label;
} textarea_t;

void systemTextarea(void)
{
    std::vector<std::pair<game::int32, std::any> > &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(textarea_t).hash_code());
    sf::Vector2i mouse = sf::Mouse::getPosition(*(game::Game::getEngine()->getWindow()));
    sf::Vector2u window = game::Game::getEngine()->getWindow()->getSize();

    mouse.x = static_cast<float>(mouse.x) * static_cast<float>((static_cast<float>(1920) / static_cast<float>(window.x)));
    mouse.y = static_cast<float>(mouse.y) * static_cast<float>((static_cast<float>(1080) / static_cast<float>(window.y)));
    for (size_t i = 0; i < components.size(); i++) {
        textarea_t textarea = std::any_cast<textarea_t>(components[i].second);
        if (textarea.focus) {
            if (game::Game::getEngine()->getLastKeyAscii() == 8 && textarea.text.size())
                textarea.text.pop_back();
            else if (game::Game::getEngine()->getLastKeyAscii() >= 32 && static_cast<game::int32>(textarea.text.size()) <= textarea.text_size) {
                textarea.text.push_back(static_cast<char>(game::Game::getEngine()->getLastKeyAscii()));
                std::cout << game::Game::getEngine()->getLastKeyAscii() << std::endl;
            } else if (game::Game::getEngine()->getLastKeyAscii() == 13)
                textarea.focus = false;
        } else {
            if (game::Game::getEngine()->getMouseClickOnce() && mouse.x >= textarea.position.x
            && mouse.x <= textarea.position.x + textarea.size
            && mouse.y >= textarea.position.y
            && mouse.y <= textarea.position.y + 70) {
                textarea.focus = true;
                for (size_t j = 0; j < components.size(); j++) {
                    if (components[i].first != components[j].first) {
                        textarea_t tmp = std::any_cast<textarea_t>(components[j].second);
                        tmp.focus = false;
                        components[j].second = std::any(tmp);
                    }
                }
            }
        }
        components[i].second = std::any(textarea);
        // display
        sf::RectangleShape rectangle(sf::Vector2f(textarea.size, 70));
        rectangle.setPosition(textarea.position);
        rectangle.setFillColor((textarea.focus) ? sf::Color(255, 255, 255, 70) : sf::Color(255, 255, 255, 40));
        game::Game::getEngine()->getWindow()->draw(rectangle);
        textarea.text_draw.setString(textarea.text);
        textarea.text_draw.setPosition(sf::Vector2f(textarea.position.x + 10, textarea.position.y + 10));
        textarea.text_draw.setCharacterSize(50);
        game::Game::getEngine()->getWindow()->draw(textarea.text_draw);
    }
}

#ifdef __DEBUG
void __attribute__((destructor)) destruct(void)
{
    std::cout << "[Destruct] Textarea" << std::endl;
}
#endif

void __attribute__((constructor)) construct(void)
{
    #ifdef __DEBUG
    std::cout << "[Construct] Textarea" << std::endl;
    #endif
    game::Game::getEngine()->systemManager().declareSystem(systemTextarea);
}
