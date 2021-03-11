/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** Serializer
*/

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <vector>
#include <stdint.h>

/* ---  protocol client -- */ /*
Le client envoit ses input
IDentity:inputs

inputs is an uint
* 0  0  0  0  0  0  0  0
* |  |  |  |  |  |  |  |
* 1  2  3  4  5  6  7  8
*
* before we don't care
* 1-2 -> unused
* 3 -> up
* 4 -> right
* 5 -> down
* 6 left
* 7 weapon 1
* 8 weapon 2
*
*//* -------------------- */

/* ---  protocol server -- */ /*
IDentity:entityX:entityY ...
int      int     int
*/

namespace rty {
    namespace common {
        class Serializer {
        public:
            Serializer();
            ~Serializer(){}

            // clear internal buffer, call it after send
            void clear() noexcept;

            // for server to send entities
            void appendEntity(int id, int x, int y) noexcept;

            // for clients to send inputs
            void appendPlayerPos(int id, int inputs) noexcept;

            // return the serialized buffer
            const std::vector<int> getBuffer() const noexcept;

            void logBuffer() const noexcept;

        private:
            std::vector<std::vector<int>> _buffer;
        };
    } // namespace common
} // namespace rty

#endif // SERIALIZER_HPP
