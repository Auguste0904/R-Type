/*
** EPITECH PROJECT, 2020
** DefaultName
** File description:
** Scene
*/

#ifndef SCENE_HPP
#define SCENE_HPP

class Scene {
    public:
        virtual void init() = 0;

        virtual int handleInput() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

        virtual void pause() {}
        virtual void stop() {}
        virtual void resume() {}

    private:
};

#endif // SCENE_HPP
