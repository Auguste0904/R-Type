/*
** EPITECH PROJECT, 2020
** DefaultName
** File description:
** SceneManager
*/

#pragma once

#include <memory>
#include <stack>
#include "Scene.hpp"

namespace rty {

    using sceneRef = std::unique_ptr<Scene>;

    class SceneManager {
        public:
            SceneManager() noexcept;
            ~SceneManager() {}

            void addScene(sceneRef newScene, bool isReplacing = true) noexcept;
            void removeScene() noexcept;
            void processSceneChanges();
            void clearToMainMenu();
            sceneRef &getActiveScene() noexcept;


        private:
            std::stack<sceneRef> _scenes;
            sceneRef _newScene;

            bool _isRemoving;
            bool _isAdding;
            bool _isReplacing;
    };
}
