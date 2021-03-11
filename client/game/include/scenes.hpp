/*
** EPITECH PROJECT, 2020
** client
** File description:
** scenes.hpp
*/

#ifndef __SCENES_HPP_
#define __SCENES_HPP_

#include "types.hpp"
#include <memory>

typedef struct sprite_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    game::uint32 z_index;
} sprite_t;

typedef struct button_s
{
    std::shared_ptr<sf::Texture> texture_1;
    sf::Sprite sprite_1;
    std::shared_ptr<sf::Texture> texture_2;
    sf::Sprite sprite_2;
    void (&function)(void);
} button_t;

typedef struct text_s
{
    std::shared_ptr<sf::Font> font;
    sf::Text text;
    std::string label;
} text_t;

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

typedef struct slider_s
{
    std::shared_ptr<sf::Texture> texture_1;
    sf::Sprite sprite_1;
    bool grab;
} slider_t;

typedef struct parallax_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    game::uint32 z_index;
    float speed;
} parallax_t;

typedef struct player_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    std::string label;
    game::uint32 hp;
    sf::Clock fire;
} player_t;

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

typedef struct rocketEnemy_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    sf::Clock clock;
    bool destroyed;
} rocket_enemy_t;

typedef struct music_s
{
    sf::Music music;
} music_t;

typedef struct boss_s
{
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    bool died;
    sf::Clock clock;
    game::int32 hp;
    sf::Clock fire;
} boss_t;

void main_menu(void);
void htp_menu(void);
void connect_menu(void);
void settings_menu(void);
void lobby_menu(void);
void game_loop();
void game_over(void);

#endif
