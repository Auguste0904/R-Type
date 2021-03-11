/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Sprite.cpp
*/

#include "Game.hpp"

typedef struct button_s
{
    std::shared_ptr<sf::Texture> texture_1;
    sf::Sprite sprite_1;
    std::shared_ptr<sf::Texture> texture_2;
    sf::Sprite sprite_2;
    void (&function)(void);
} button_t;

void systemMenu(void)
{
    auto &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(button_t).hash_code());

    for (auto &component : components) {
        button_t data = std::any_cast<button_t>(component.second);
        sf::Vector2i mouse = sf::Mouse::getPosition(*(game::Game::getEngine()->getWindow()));
        sf::Vector2u window = game::Game::getEngine()->getWindow()->getSize();
        mouse.x = static_cast<float>(mouse.x) * static_cast<float>((static_cast<float>(1920) / static_cast<float>(window.x)));
        mouse.y = static_cast<float>(mouse.y) * static_cast<float>((static_cast<float>(1080) / static_cast<float>(window.y)));
        if (mouse.x >= data.sprite_1.getPosition().x
        && mouse.x <= (data.sprite_1.getPosition().x + data.sprite_1.getScale().x * data.texture_1->getSize().x)
        && mouse.y >= data.sprite_1.getPosition().y
        && mouse.y <= (data.sprite_1.getPosition().y + data.sprite_1.getScale().y * data.texture_1->getSize().y)) {
            game::Game::getEngine()->getWindow()->draw(data.sprite_2);
            if (game::Game::getEngine()->getMouseClickOnce())
                data.function();
        } else {
            game::Game::getEngine()->getWindow()->draw(data.sprite_1);
        }
    }
}

#ifdef __DEBUG
void __attribute__((destructor)) destruct(void)
{
    std::cout << "[Destruct] Button" << std::endl;
}
#endif

void __attribute__((constructor)) construct(void)
{
    #ifdef __DEBUG
    std::cout << "[Construct] Button" << std::endl;
    #endif
    game::Game::getEngine()->systemManager().declareSystem(systemMenu);
}
