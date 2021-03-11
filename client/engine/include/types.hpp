/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** types.hpp
*/

#ifndef __GAME_TYPES_HPP_
#define __GAME_TYPES_HPP_

#include <sys/types.h>

namespace game {

    typedef struct {
        float x;
        float y;
    } vector2f;

    typedef struct {
        int32_t x;
        int32_t y;
    } vector2i;

    typedef int8_t int8;
    typedef u_int8_t uint8;

    typedef int16_t int16;
    typedef u_int16_t uint16;

    typedef int32_t int32;
    typedef u_int32_t uint32;

}

#endif