/*
** EPITECH PROJECT, 2020
** menu
** File description:
** Exception.hpp
*/

#ifndef EXCEPTION_HPP__
#define EXCEPTION_HPP__

#include "Rtype.hpp"

namespace rtype
{
    class Exception : public std::exception
    {
    public:
        Exception(const std::string &message) throw();
        Exception() throw();
        ~Exception() throw() = default;

        virtual const char *what() const throw();

    protected:
        std::string message = "An error occured";
    };
}

#endif