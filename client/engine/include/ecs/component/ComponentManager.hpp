/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** ComponentManager.hpp
*/

#ifndef COMPONENTMANAGER_HPP__
#define COMPONENTMANAGER_HPP__

#include "types.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <any>
#include <algorithm>

namespace game
{
    class ComponentManager
    {
        public:
            ComponentManager();
            virtual ~ComponentManager() = default;
            void _REMOVE_COMPONENT_ENTITY(const game::int32 &id);

            template<typename T>
            void addComponent(const std::pair<game::int32, T> &component)
            {
                this->_componentMap[typeid(decltype(component.second)).hash_code()].push_back(component);
            }

            template<typename T>
            void addHashComponent(const std::size_t &hash_type, const std::pair<game::int32, T> &component)
            {
                this->_componentMap[hash_type].push_back(component);
            }

            void removeHashComponent(const std::size_t &hash_type, const game::int32 &id)
            {
                std::vector<std::pair<game::int32, std::any> > &tmp_list = this->_componentMap[hash_type];
                std::vector<std::pair<game::int32, std::any> >::iterator it = std::find_if(
                    tmp_list.begin(),
                    tmp_list.end(),
                    [id](std::pair<game::int32, std::any> tmp) mutable {return (tmp.first == id);}
                );
                if (it != tmp_list.end()) {
                    tmp_list.erase(it);
                }
            }

            template<typename T>
            void removeComponent(const T &type, const game::int32 &id)
            {
                std::vector<std::pair<game::int32, std::any> > &tmp_list = this->_componentMap[typeid(decltype(type)).hash_code()];
                std::vector<std::pair<game::int32, std::any> >::iterator it = std::find_if(
                    tmp_list.begin(),
                    tmp_list.end(),
                    [id](std::pair<game::int32, std::any> tmp) mutable {return (tmp.first == id);}
                );
                if (it != tmp_list.end()) {
                    tmp_list.erase(it);
                }
            }

            template<typename T>
            std::vector<std::pair<game::int32, std::any> > &getComponents(const T &type)
            {
                return (this->_componentMap[typeid(decltype(type)).hash_code()]);
            }

            std::vector<std::pair<game::int32, std::any> > &getHashComponents(const std::size_t &hash_type)
            {
                return (this->_componentMap[hash_type]);
            }

            void _CLEAR(void);

        private:
//            std::unordered_map<std::type_index, std::vector<std::pair<game::int32, std::any> > > _componentMap;
            std::unordered_map<std::size_t, std::vector<std::pair<game::int32, std::any> > > _componentMap;
    };
}

#endif