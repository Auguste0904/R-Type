/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** ComponentManager.cpp
*/

#include "ComponentManager.hpp"

/**
 * \brief Component manager constructor
 *
 * Create a component manager instance
 *
 **/
game::ComponentManager::ComponentManager()
{
    this->_componentMap = {};
}

/**
 * \brief Remove a component entity from component map
 *
 *
 * \param id id of game instance
 **/
void game::ComponentManager::_REMOVE_COMPONENT_ENTITY(const game::int32 &id)
{
    for (auto &elem : this->_componentMap) {
        std::vector<std::pair<game::int32, std::any> >::iterator it = std::find_if(
            elem.second.begin(),
            elem.second.end(),
            [id](std::pair<game::int32, std::any> tmp) mutable {return (tmp.first == id);}
        );
        if (it != elem.second.end()) {
            elem.second.erase(it);
        }
    }
}

/**
 * \brief Clear component map
 *
 *
 **/
void game::ComponentManager::_CLEAR(void)
{
    this->_componentMap.clear();
}