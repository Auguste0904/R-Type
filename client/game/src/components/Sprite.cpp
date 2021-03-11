/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Sprite.cpp
*/

#include "Game.hpp"

typedef struct sprite_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    game::uint32 z_index;
} sprite_t;

void systemDisplay(void)
{
    auto &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(sprite_t).hash_code());
    std::vector<game::uint32> list_z_index = {};
    game::uint32 tmp_id;
    //std::vector<std::pair<game::int32, std::any> >::iterator it;

    for (auto &component : components) {
        tmp_id = (std::any_cast<sprite_t>(component.second)).z_index;
        if (list_z_index.size() == 0)
            list_z_index.push_back(tmp_id);
        else {
            for (size_t i = 0; i < list_z_index.size(); i++) {
                if ((std::any_cast<sprite_t>(component.second)).z_index == list_z_index[i])
                    break;
                if (i == list_z_index.size() - 1)
                    list_z_index.push_back(std::any_cast<sprite_t>(component.second).z_index);
            }
        }
    }
    std::sort(list_z_index.begin(), list_z_index.end());
    for (game::uint32 &index : list_z_index) {
        for (auto &component : components) {
            sprite_t data = std::any_cast<sprite_t>(component.second);
            if (data.z_index != index)
                continue;
            game::Game::getEngine()->getWindow()->draw(data.sprite);
        }
    }
}

#ifdef __DEBUG
void __attribute__((destructor)) destruct(void)
{
    std::cout << "[Destruct] Sprite" << std::endl;
}
#endif

void __attribute__((constructor)) construct(void)
{
    #ifdef __DEBUG
    std::cout << "[Construct] Sprite" << std::endl;
    #endif
    game::Game::getEngine()->systemManager().declareSystem(systemDisplay);
}
