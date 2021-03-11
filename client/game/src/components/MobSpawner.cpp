/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Enemy1.cpp
*/

#include "Game.hpp"

void game_over(void);

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

void systemMobSpawner(void)
{
    static game::int32 mobs = 0;
    game::int32 mobCount = 0;
    const game::int32 mobLimit = 20;
    auto &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(enemy1_t).hash_code());
    const std::vector<game::int32> pos = {10, 500, 800, 100, 250, 800, 600, 300, 200, 300, 850, 10, 200, 700, 800, 500, 10, 500, 800, 100, 250, 800, 600, 300, 200, 300, 850, 10, 200, 700, 800, 500, 10, 500, 800, 100, 250, 800, 600, 300, 200, 300, 850, 10, 200, 700, 800, 500};
    const std::vector<game::int32> posOffset = {1, 50, 80, 10, 25, 80, 60, 30, 20, 30, 85, 1, 20, 70, 80, 50, 1, 50, 80, 10, 25, 80, 60, 30, 20, 30, 85, 1, 20, 70, 80, 50, 1, 50, 80, 10, 25, 80, 60, 30, 20, 30, 85, 1, 20, 70, 80, 50};

    mobCount = components.size();
    for (size_t i = mobCount; i < 5 && mobs < mobLimit; i++) {
        enemy1_t enemy;
        enemy.hp = 10;
        enemy.died = false;
        enemy.texture = std::make_shared<sf::Texture>();
        enemy.texture->loadFromFile("assets/sprites/r-typesheet11.png");
        enemy.sprite.setTexture(*(enemy.texture));
        enemy.sprite.setScale(sf::Vector2f(3, 3));
        enemy.sprite.setPosition(sf::Vector2f(1920 + posOffset[mobs] * 2.5, pos[mobs]));
        game::int32 id = game::Game::getEngine()->entityManager().addEntity();
        game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, enemy));
        mobs++;
    }
    if (mobs == mobLimit && mobCount == 0) {
        boss_t enemy;
        enemy.hp = 300;
        enemy.died = false;
        enemy.texture = std::make_shared<sf::Texture>();
        enemy.texture->loadFromFile("assets/sprites/r-typesheet32.png");
        enemy.sprite.setTexture(*(enemy.texture));
        enemy.sprite.setScale(sf::Vector2f(3, 3));
        enemy.sprite.rotate(270);
        enemy.sprite.setPosition(sf::Vector2f(1920, 1080 / 1.25));
        game::int32 id = game::Game::getEngine()->entityManager().addEntity();
        game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, enemy));
        mobs++;
    }
    if (mobs == mobLimit + 1 && game::Game::getEngine()->componentManager().getHashComponents(typeid(boss_t).hash_code()).size() == 0) {
        game_over();
    }
}

#ifdef __DEBUG
void __attribute__((destructor)) destruct(void)
{
    std::cout << "[Destruct] mobSpawner" << std::endl;
}
#endif

void __attribute__((constructor)) construct(void)
{
#ifdef __DEBUG
    std::cout << "[Construct] mobSpawner" << std::endl;
#endif
    game::Game::getEngine()->systemManager().declareSystem(systemMobSpawner);
}
