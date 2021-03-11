/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** Serializer
*/

#include "Serializer.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <iostream>

rty::common::Serializer::Serializer()
{

}

// clear internal buffer, call it after send
void rty::common::Serializer::clear() noexcept
{
    _buffer.clear();
}

// for server to send entities
void rty::common::Serializer::appendEntity(int id, int x, int y) noexcept
{
    std::vector<int> tmp{id, x, y};
    _buffer.push_back(tmp);
}

// for clients to send inputs
void rty::common::Serializer::appendPlayerPos(int id, int inputs) noexcept
{
    std::vector<int> tmp{id, inputs};
    _buffer.push_back(tmp);
}

// return the serialized buffer
const std::vector<int> rty::common::Serializer::getBuffer() const noexcept
{
    std::vector<int> tmp;

    for (size_t i = 0; i < _buffer.size(); i++) {
        for (size_t j = 0; j < _buffer.at(i).size(); j++) {
            tmp.push_back(_buffer.at(i).at(j));
        }
    }
    return tmp;
}

void rty::common::Serializer::logBuffer() const noexcept
{
    std::cout << "\nbuff: {" << std::endl;
    for (size_t i = 0; i < _buffer.size(); i++) {
        if (_buffer.at(i).size() == 2) { // client
            std::cout << "client inputs: ";
            for (size_t j = 0; j < _buffer.at(i).size(); j++) {
                std::cout << _buffer.at(i).at(j) << " ";
            }
        } else { // server
            std::cout << "entity pos: ";
            for (size_t j = 0; j < _buffer.at(i).size(); j++) {
                std::cout << _buffer.at(i).at(j) << " ";
            }
        }
        std::cout << "" << std::endl;
    }
    std::cout << "\n}" << std::endl;
}
