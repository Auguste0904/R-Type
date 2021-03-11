/*
** EPITECH PROJECT, 2020
** DefaultName
** File description:
** SoundPlayer
*/

#pragma once

#include "Core.hpp"

#define PLAY_SWITCH(_gamedata) \
        Indie::Utils::SoundPlayer::playSound(_gameData->factory->getSound("switch"), _gameData->settings.soundVolume)


namespace Indie {
    namespace Utils {
        class SoundPlayer {
            public:
                static void playSound(sf::SoundBuffer *buffer, int volume);
                static void playMusic(sf::Music *music, int volume, bool loop = true);
                static void stopMusic(sf::Music *music);
        };
    } // Utils
} // Indie
