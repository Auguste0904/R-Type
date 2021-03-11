/*
** EPITECH PROJECT, 2020
** INDIE
** File description:
** Factory
*/

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <unordered_map>

        class Factory {
        public:
            explicit Factory(irr::IrrlichtDevice *d) noexcept;
            ~Factory() = default;


            // Load or get a music
            sf::Music *getMusic(const std::string &path, const std::string &name);
            sf::Music *getMusic(const std::string &name);

            // Load or get a sound
            sf::SoundBuffer *getSound(const std::string &path, const std::string &name);
            sf::SoundBuffer *getSound(const std::string &name);


        protected:
            std::unordered_map<std::string, sf::Music *> _musics;
            std::unordered_map<std::string, sf::SoundBuffer*> _sounds;
        };

        extern Factory *FACTORY;

#endif // FACTORY_HPP
