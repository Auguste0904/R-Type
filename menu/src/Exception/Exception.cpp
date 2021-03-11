/*
** EPITECH PROJECT, 2019
** Game_Jam
** File description:
** game.cpp
*/

#include "Exception.hpp"

rtype::Exception::Exception(const std::string &message) throw()
{
    this->message = message;
}

rtype::Exception::Exception() throw()
{
    ;
}

const char *rtype::Exception::what() const throw()
{
    return (this->message.c_str());
}