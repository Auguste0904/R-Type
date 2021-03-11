/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** parallax.cpp
*/

#include "Game.hpp"

typedef struct parallax_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    game::uint32 z_index;
    float speed;
} parallax_t;

void systemParallax(void)
{
    auto &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(parallax_t).hash_code());
    std::vector<game::uint32> list_z_index = {};
    game::uint32 tmp_id;
    static sf::Clock clock;
    //std::vector<std::pair<game::int32, std::any> >::iterator it;

    for (auto &component : components) {
        tmp_id = (std::any_cast<parallax_t>(component.second)).z_index;
        if (list_z_index.size() == 0)
            list_z_index.push_back(tmp_id);
        else {
            for (size_t i = 0; i < list_z_index.size(); i++) {
                if ((std::any_cast<parallax_t>(component.second)).z_index == list_z_index[i])
                    break;
                if (i == list_z_index.size() - 1)
                    list_z_index.push_back(std::any_cast<parallax_t>(component.second).z_index);
            }
        }
    }
    std::sort(list_z_index.begin(), list_z_index.end());
    bool move = false;
    if (clock.getElapsedTime().asMilliseconds() >= (1000 / 30)) {
        clock.restart();
        move = true;
    }
    for (game::uint32 &index : list_z_index) {
        for (size_t i = 0; i < components.size(); i++) {
            parallax_t data = std::any_cast<parallax_t>(components[i].second);
            if (data.z_index != index)
                continue;
            if (move) {
                data.sprite.setPosition(data.sprite.getPosition().x + data.speed, data.sprite.getPosition().y);
                components[i].second = std::any(data);
            }
            sf::Vector2f pos = data.sprite.getPosition();
            do {
                data.sprite.setPosition(data.sprite.getPosition().x - data.sprite.getGlobalBounds().width , data.sprite.getPosition().y);
                game::Game::getEngine()->getWindow()->draw(data.sprite);
            } while (data.sprite.getPosition().x > 0);
            data.sprite.setPosition(pos);
            game::Game::getEngine()->getWindow()->draw(data.sprite);
            do {
                data.sprite.setPosition(data.sprite.getPosition().x + data.sprite.getGlobalBounds().width , data.sprite.getPosition().y);
                game::Game::getEngine()->getWindow()->draw(data.sprite);
            } while (data.sprite.getPosition().x + data.sprite.getGlobalBounds().width < 1920);
        }
    }
}

#ifdef __DEBUG
void __attribute__((destructor)) destruct(void)
{
    std::cout << "[Destruct] parallax" << std::endl;
}
#endif

void __attribute__((constructor)) construct(void)
{
    #ifdef __DEBUG
    std::cout << "[Construct] parallax" << std::endl;
    #endif
    game::Game::getEngine()->systemManager().declareSystem(systemParallax);
}
