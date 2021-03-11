#ifndef EXCEPTION_HPP__
#define EXCEPTION_HPP__

#include "types.hpp"
#include <exception>
#include <iostream>

namespace game
{
    class Exception : public std::exception
    {
    public:
        Exception(const std::string &message, const game::int32 &returnValue) throw();
        Exception() throw();
        ~Exception() throw() = default;

        virtual const char *what() const throw();
        game::int32 getReturnValue(void);

    protected:
        std::string _message = "An error occured";
        game::int32 _returnValue = 0;
    };
}

#endif