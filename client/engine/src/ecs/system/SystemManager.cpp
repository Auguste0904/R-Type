/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** SystemManager.cpp
*/

#include "SystemManager.hpp"
#include <vector>
#include <iterator>
#include <algorithm>

/**
 * \brief System manager constructor
 *
 * Create a system manager instance
 *
 **/
game::SystemManager::SystemManager()
{
    this->_systemList = {};
}


/**
 * \brief Declare the system variables 
 *
 * \param 
 * 
 **/
void game::SystemManager::declareSystem(void (&function)(void))
{
    for (size_t i = 0; i < this->_systemList.size(); i++) {
        if (function == this->_systemList[i]) {
            this->_systemList.erase(this->_systemList.begin() + i);
            break;
        }
    }
    this->_systemList.push_back(function);
}


/**
 * \brief Delete the system variables
 *
 * 
 * \param function 'game::Game::__ENGINE_'.
 **/
void game::SystemManager::removeSystem(void (&function)(void))
{
    std::vector<void (*)(void)>::iterator it = std::find_if(
        this->_systemList.begin(),
        this->_systemList.end(),
        [function](void (*tmp)(void)) mutable {return (tmp == &function);}
    );
    if (it != this->_systemList.end()) {
        this->_systemList.erase(it);
    }
}


/**
 * \brief Get the system
 *
 * 
 * \return a 'std::vector<void (*) (void)> &'.
 **/
std::vector<void (*)(void)> &game::SystemManager::getSystems(void)
{
    return (this->_systemList);
}