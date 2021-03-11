/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** Exception.cpp
*/

#include "Exception.hpp"

/**
 * \brief Game exception constructor
 * 
 * Create a game exception instance
 * 
 *\param message Error message
 *\param returnValue return number
 *
 **/
game::Exception::Exception(const std::string &message, const game::int32 &returnValue) throw()
{
    this->_message = message;
    this->_returnValue = returnValue;
}

/**
 * \brief Game exception constructor
 *
 * Create a game exception instance
 * 
 **/
game::Exception::Exception() throw()
{
    ;
}

/**
 * \brief Get the exception message
 *
 * \return a 'const char *'.
 **/
const char *game::Exception::what() const throw()
{
    return (this->_message.c_str());
}
/**
 * \brief Get the return value
 *
 * \return a 'game::int32'.
 **/
game::int32 game::Exception::getReturnValue(void)
{
    return (this->_returnValue);
}
