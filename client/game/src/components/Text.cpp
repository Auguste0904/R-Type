/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Sprite.cpp
*/

#include "Game.hpp"

typedef struct text_s
{
    std::shared_ptr<sf::Font> font;
    sf::Text text;
    std::string label;
} text_t;

void systemDisplayText(void)
{
    auto &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(text_t).hash_code());
    std::vector<game::uint32> list_z_index = {};

    for (auto &component : components) {
        text_t data = std::any_cast<text_t>(component.second);
        game::Game::getEngine()->getWindow()->draw(data.text);
    }
}

#ifdef __DEBUG
void __attribute__((destructor)) destruct(void)
{
    std::cout << "[Destruct] Text" << std::endl;
}
#endif

void __attribute__((constructor)) construct(void)
{
#ifdef __DEBUG
    std::cout << "[Construct] Text" << std::endl;
#endif
    game::Game::getEngine()->systemManager().declareSystem(systemDisplayText);
}
