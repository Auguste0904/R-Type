/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** IGame.hpp
*/

#ifndef __GAME_HPP_
#define __GAME_HPP_

#define __DEBUG
//#define __SINGLEPLAYER

#include "types.hpp"
#include "Exception.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "ChangeScene.hpp"

namespace game {

    class Game {
        public:
            Game(const std::string &title = "", const std::string &icon = "");
            virtual ~Game();
            static Game *getEngine(void);
            static Game *__ENGINE_(Game *game = nullptr);
            game::EntityManager &entityManager(void);
            game::ComponentManager &componentManager(void);
            game::SystemManager &systemManager(void);
            void scene(void (&callback_init)(void));
            // void changeScene(void (&callback_init)(void));
            void setResolution(const sf::Vector2i &resolution);
            const sf::Vector2i &getResolution(void) const;
            sf::RenderWindow *getWindow(void);
            void setIcon(const std::string &icon);
            const std::string &getIcon(void) const;
            void setTitle(const std::string &title);
            const std::string &getTitle(void) const;
            void setSoundVolume(const game::uint8 &volume);
            const game::uint8 &getSoundVolume(void) const;
            void setMusicVolume(const game::uint8 &volume);
            const game::uint8 &getMusicVolume(void) const;
            void setMouseVisible(const bool &visible);
            const bool &isMouseVisible(void) const;
            void setFullscreen(const bool &fullscreen);
            const bool &isFullscreen(void) const;
            void setFramerate(const game::uint8 &framerate);
            const game::uint8 &getFramerate(void) const;
            void close(void);
            void playMusic(void);
            void openSound(const std::string &pathSound);
            void playSound(void);
            const bool &isClosed(void) const;
            void clear(const sf::Color &color = sf::Color::Black);
            void loadLibrary(const std::string &lib);
            void unloadLibrary(const std::string &lib);
            void unloadAllLibrary(void);
            bool getKey(const game::int32 &key);
            bool getMouseClick(void);
            bool getMouseClickOnce(void);
            game::int32 getLastKey(void) const;
            game::int32 getLastKeyAscii(void) const;
            void setCallback(void (*callback)(void));
            static bool collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2);
        private:
            void manageEvent(void);

            void (*_callback)(void);
            game::int32 _lastKeyAscii;
            game::int32 _lastKey;
            sf::Event _event;
            std::unordered_map<game::int32, bool> _keyStroke;
            bool _click;
            bool _clickOnce;
            game::EntityManager _entityManager;
            game::ComponentManager _componentManager;
            game::SystemManager _systemManager;
            std::unique_ptr<sf::RenderWindow> _window = nullptr;
            sf::Image _iconName;
            sf::Music _music;
            sf::SoundBuffer _soundBuffer;
            sf::Sound _sound;
            sf::Vector2i _resolution;
            std::string _icon;
            std::string _title;
            game::uint8 _soundVolume;
            game::uint8 _musicVolume;
            bool _mouseVisible;
            bool _fullscreen;
            game::uint8 _framerate;
            bool _closed;
            std::unique_ptr<sf::View> _view;
            std::vector<std::pair<std::string, void *> > _libList = {};
    };

}

#endif
