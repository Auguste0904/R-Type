/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** EntityManager.cpp
*/

#include "EntityManager.hpp"
#include "Game.hpp"

/**
 * \brief EntityManager is the constructor.
 * 
 * It initializes a list of entities.
 * 

 **/
game::EntityManager::EntityManager()
{
    this->_entityList = {};
}

/**
 * \brief The addEntity function
 * 
 * add an entity to the list.
 * 
 **/
game::int32 game::EntityManager::addEntity(void)
{
    game::int32 id = -1;
    bool find = false;
    do {
        find = false;
        for (const game::int32 &tmp : this->_entityList) {
            if (tmp == id) {
        // for (size_t i = 0; i < this->_entityList.size(); i++) {
        //     if (this->_entityList[i] == id) {
                find = true;
                id--;
                break;
            }
        }
    } while (find == true);
    this->_entityList.push_back(id);
    return (id);
}

/**
 * \brief The addEntity function
 * 
 * add a defined entity id to the list.
 * 
 **/
game::int32 game::EntityManager::addEntity(const game::int32 &id)
{
    for (const game::int32 &tmp : this->_entityList) {
        if (tmp == id)
            return (-1);
    }
    this->_entityList.push_back(id);
    return (id);
}

/**
 * \brief The removeEntity function
 * 
 * remove an entity from the engine
 * 
 * \param id id to be removed from the list
 **/
void game::EntityManager::removeEntity(const game::int32 &id)
{
    game::Game::getEngine()->componentManager()._REMOVE_COMPONENT_ENTITY(id);
    this->_REMOVE_ENTITY(id);
}

/**
 * \brief NOT MEANT TO BE USED BY GAME DEVELOPER.
 * 
 * Remove an entity from list without calling remove from ComponentManager, SystemManager
 * 
 * \param id id to be removed from the list
 **/
void game::EntityManager::_REMOVE_ENTITY(const game::int32 &id)
{
    this->_entityList.erase(std::remove(this->_entityList.begin(), this->_entityList.end(), id), this->_entityList.end());
}

/**
 * \brief The clear function
 * 
 * clear all entities of the entity list.
 * 
 * \return Return a stactic number which is id of an entity.
 **/
void game::EntityManager::clear(void)
{
    // CALL CLEARINNER FROM COMPONENTMANAGER AND SYSTEMMANAGER
    game::Game::getEngine()->componentManager()._CLEAR();
    this->_CLEAR();
}

/**
 * \brief NOT MEANT TO BE USED BY GAME DEVELOPER !
 * 
 * Clear all entities of the entity list.
 * 
 * \return Return a stactic number which is id of an entity.
 **/
void game::EntityManager::_CLEAR(void)
{
    this->_entityList.clear();
}