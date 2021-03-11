/*
** EPITECH PROJECT, 2020
** DefaultName
** File description:
** SoundPlayer
*/

#include "SoundPlayer.hpp"

static sf::Sound SOUND;

void Indie::Utils::SoundPlayer::playSound(sf::SoundBuffer *buffer, int volume)
{
    SOUND.setBuffer(*buffer);
    SOUND.setVolume(volume);
    SOUND.stop();
    SOUND.play();
}

void Indie::Utils::SoundPlayer::playMusic(sf::Music *music, int volume, bool loop)
{
    music->setVolume(volume);
    music->setLoop(loop);
    music->play();
}

void Indie::Utils::SoundPlayer::stopMusic(sf::Music *music)
{
    music->stop();
}
