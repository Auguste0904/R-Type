/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** Slider.cpp
*/

#include "Game.hpp"

typedef struct slider_s
{
    std::shared_ptr<sf::Texture> texture_1;
    sf::Sprite sprite_1;
    bool grab;
} slider_t;

void systemSlider(void)
{
    auto &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(slider_t).hash_code());

    for (auto &component : components)
    {
        slider_t data = std::any_cast<slider_t>(component.second);
        data.grab = false;
        sf::Vector2i mouse = sf::Mouse::getPosition(*(game::Game::getEngine()->getWindow()));
        sf::Vector2u window = game::Game::getEngine()->getWindow()->getSize();
        mouse.x = static_cast<float>(mouse.x) * static_cast<float>((static_cast<float>(1920) / static_cast<float>(window.x)));
        mouse.y = static_cast<float>(mouse.y) * static_cast<float>((static_cast<float>(1080) / static_cast<float>(window.y)));
        game::Game::getEngine()->getWindow()->draw(data.sprite_1);
        if (mouse.x >= data.sprite_1.getPosition().x && mouse.x <= (data.sprite_1.getPosition().x + data.sprite_1.getScale().x * data.texture_1->getSize().x) && mouse.y >= data.sprite_1.getPosition().y && mouse.y <= (data.sprite_1.getPosition().y + data.sprite_1.getScale().y * data.texture_1->getSize().y))
        {
            if (game::Game::getEngine()->getMouseClick())
                data.grab = true;
        }
    }
}

#ifdef __DEBUG
void __attribute__((destructor)) destruct(void)
{
    std::cout << "[Destruct] slider" << std::endl;
}
#endif

void __attribute__((constructor)) construct(void)
{
#ifdef __DEBUG
    std::cout << "[Construct] slider" << std::endl;
#endif
    game::Game::getEngine()->systemManager().declareSystem(systemSlider);
}
