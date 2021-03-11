/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** EntityManager.hpp
*/

#ifndef ENTITYMANAGER_HPP__
#define ENTITYMANAGER_HPP__

#include "types.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace game
{
    class EntityManager {
        public:
            EntityManager();
            virtual ~EntityManager() = default;
            game::int32 addEntity(void);
            game::int32 addEntity(const game::int32 &id);
            void removeEntity(const game::int32 &id);
            void _REMOVE_ENTITY(const game::int32 &id);
            void clear(void);
            void _CLEAR(void);
        public:
            std::vector<game::int32> _entityList;
    };
}

#endif