/*
** EPITECH PROJECT, 2020
** DefaultName
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

Indie::SceneManager::SceneManager() noexcept
{
    _isRemoving = false;
    _isAdding = false;
    _isReplacing = false;
}

void Indie::SceneManager::addScene(sceneRef newScene, bool isReplacing) noexcept
{
    this->_isAdding = true;
    this->_isReplacing = isReplacing;
    this->_newScene = std::move(newScene);
}

void Indie::SceneManager::removeScene() noexcept
{
    this->_isRemoving = true;
}

void Indie::SceneManager::processSceneChanges()
{
    if (this->_isRemoving && !this->_scenes.empty()) {
        this->_scenes.top()->stop();
        this->_scenes.pop();
        if (!this->_scenes.empty()) {
            this->_scenes.top()->resume();
        }
        this->_isRemoving = false;
    }
    if (this->_isAdding) {
        if (!this->_scenes.empty()) {
            if (this->_isReplacing) {
                this->_scenes.pop();
            } else {
                this->_scenes.top()->pause();
            }
        }
        this->_scenes.push(std::move(this->_newScene));
        this->_scenes.top()->init();
        this->_isAdding = false;
    }
}

Indie::sceneRef &Indie::SceneManager::getActiveScene() noexcept
{
    return this->_scenes.top();
}

void Indie::SceneManager::clearToMainMenu()
{
    while (!_scenes.empty() && _scenes.size() > 2) {
        _scenes.pop();
    }
}
