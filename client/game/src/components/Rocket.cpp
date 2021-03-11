/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Rocket.cpp
*/

#include "Game.hpp"

typedef struct rocket_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    sf::Clock clock;
    bool destroyed;
} rocket_t;

typedef struct enemy1_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    bool died;
    sf::Clock clock;
    game::int32 hp;
    sf::Clock fire;
} enemy1_t;

typedef struct boss_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    bool died;
    sf::Clock clock;
    game::int32 hp;
    sf::Clock fire;
} boss_t;

void systemRocket(void)
{
    auto &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(rocket_t).hash_code());
    auto &components_enemy1 = game::Game::getEngine()->componentManager().getHashComponents(typeid(enemy1_t).hash_code());
    auto &components_boss = game::Game::getEngine()->componentManager().getHashComponents(typeid(boss_t).hash_code());
    static sf::Clock clock;
    const float speed = 15;
    bool move = false;

    if (clock.getElapsedTime().asMilliseconds() >= (1000 / 30)) {
        clock.restart();
        move = true;
    }
    for (size_t i = 0; i < components.size(); i++) {
        rocket_t data = std::any_cast<rocket_t>(components[i].second);
        if (move) {
            for (size_t j = 0; j < components_enemy1.size(); j++) {
                enemy1_t tmp_enemy = std::any_cast<enemy1_t>(components_enemy1[j].second);
                if (data.destroyed == false && (game::Game::collides(data.sprite, tmp_enemy.sprite) || data.sprite.getPosition().x > 2000)) {
                    data.destroyed = true;
                    data.clock.restart();
                    components[i].second = std::any(data);
                    tmp_enemy.hp -= 10;
                    components_enemy1[j].second = std::any(tmp_enemy);
                }
            }
            for (size_t j = 0; j < components_boss.size(); j++) {
                boss_t tmp_enemy = std::any_cast<boss_t>(components_boss[j].second);
                if (data.destroyed == false && (game::Game::collides(data.sprite, tmp_enemy.sprite) || data.sprite.getPosition().x > 2000)) {
                    data.destroyed = true;
                    data.clock.restart();
                    components[i].second = std::any(data);
                    tmp_enemy.hp -= 10;
                    components_boss[j].second = std::any(tmp_enemy);
                }
            }
            if (!data.destroyed) {
                data.sprite.setPosition(sf::Vector2f(data.sprite.getPosition().x + speed, data.sprite.getPosition().y));
                data.sprite.setTextureRect(sf::IntRect(248, 88, 10, 4));
                components[i].second = std::any(data);
            } else {
                data.sprite.setTextureRect(sf::IntRect(232, 85, 11, 9));
                if (data.clock.getElapsedTime().asMilliseconds() >= 70)
                    data.sprite.setTextureRect(sf::IntRect(214, 83, 14, 12));
                if (data.clock.getElapsedTime().asMilliseconds() >= 140) {
                    game::Game::getEngine()->entityManager().removeEntity(components[i].first);
                    i--; // car on vient de delete et on veut pas faire i++ dans le for
                    continue;
                }
                components[i].second = std::any(data);
            }
        }
        game::Game::getEngine()->getWindow()->draw(data.sprite);
    }
}

#ifdef __DEBUG
void __attribute__((destructor)) destruct(void)
{
    std::cout << "[Destruct] Rocket" << std::endl;
}
#endif

void __attribute__((constructor)) construct(void)
{
#ifdef __DEBUG
    std::cout << "[Construct] Rocket" << std::endl;
#endif
    game::Game::getEngine()->systemManager().declareSystem(systemRocket);
}
