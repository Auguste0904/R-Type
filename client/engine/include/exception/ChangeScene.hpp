#ifndef CHANGESCENE_HPP__
#define CHANGESCENE_HPP__

#include "types.hpp"
#include <exception>
#include <iostream>

namespace game::exception
{
    class ChangeScene : public std::exception
    {
        public:
            ChangeScene() throw() = default;
            virtual ~ChangeScene() throw() = default;
    };
}

#endif