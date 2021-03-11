/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Enemy1.cpp
*/

#include "Game.hpp"

typedef struct enemy1_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    bool died;
    sf::Clock clock;
    game::int32 hp;
    sf::Clock fire;
} enemy1_t;

typedef struct rocketEnemy_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    sf::Clock clock;
    bool destroyed;
} rocket_enemy_t;

void systemEnemy1(void)
{
    auto &components = game::Game::getEngine()->componentManager().getHashComponents(typeid(enemy1_t).hash_code());
    static sf::Clock clock;
    const float speed = 2.5;

    bool move = false;
    if (clock.getElapsedTime().asMilliseconds() >= (1000 / 30)) {
        clock.restart();
        move = true;
    }
    for (size_t i = 0; i < components.size(); i++) {
        enemy1_t data = std::any_cast<enemy1_t>(components[i].second);
        if (move) {
            sf::IntRect rect = {66, 0, 33, 31};
            if (data.sprite.getPosition().x > (1920 - (data.sprite.getGlobalBounds().width + 20))) {
                data.sprite.setPosition(sf::Vector2f(data.sprite.getPosition().x - speed, data.sprite.getPosition().y));
                data.sprite.setTextureRect(rect);
                components[i].second = std::any(data);
            } else {
                if (data.died == false && data.hp <= 0) {
                    data.died = true;
                    data.clock.restart();
                    components[i].second = std::any(data);
                }
                if (!data.died) {
                    data.sprite.setTextureRect(rect);
                    if (data.clock.getElapsedTime().asMilliseconds() >= 200) {
                        data.clock.restart();
                        rect.left -= 33;
                        if (rect.left <= 0)
                            rect.left = 66;
                        data.sprite.setTextureRect(rect);
                    }
                } else {
                    data.sprite.setColor(sf::Color(255, 255, 255, (data.clock.getElapsedTime().asMilliseconds() % 100 > 50) ? 96 : 255));
                    if (data.clock.getElapsedTime().asMilliseconds() >= 500) {
                        game::Game::getEngine()->entityManager().removeEntity(components[i].first);
                        i--;
                        continue;
                    }
                }
                components[i].second = std::any(data);
            }
        }
        if (data.fire.getElapsedTime().asMilliseconds() >= 1000 && data.sprite.getPosition().x < (1920 - (data.sprite.getGlobalBounds().width / 2))) {
            data.fire.restart();
            components[i].second = std::any(data);
            rocket_enemy_t rocket;
            rocket.destroyed = false;
            rocket.texture = std::make_shared<sf::Texture>();
            rocket.texture->loadFromFile("assets/sprites/r-typesheet1.png");
            rocket.sprite.setTexture(*(rocket.texture));
            rocket.sprite.setScale(sf::Vector2f(2.5, 2.5));
            rocket.sprite.setPosition(sf::Vector2f(data.sprite.getPosition().x, data.sprite.getPosition().y + 20));
            rocket.sprite.setTextureRect(sf::IntRect(266, 88, 10, 4));
            game::int32 id = game::Game::getEngine()->entityManager().addEntity();
            game::Game::getEngine()->componentManager().addComponent(std::make_pair(id, rocket));
        }
        game::Game::getEngine()->getWindow()->draw(data.sprite);
    }
}

#ifdef __DEBUG
void __attribute__((destructor)) destruct(void)
{
    std::cout << "[Destruct] enemy1" << std::endl;
}
#endif

void __attribute__((constructor)) construct(void)
{
#ifdef __DEBUG
    std::cout << "[Construct] enemy1" << std::endl;
#endif
    game::Game::getEngine()->systemManager().declareSystem(systemEnemy1);
}
