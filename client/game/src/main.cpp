/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** main.cpp
*/

#include "Game.hpp"
#include "scenes.hpp"
#include <string>

int main()
{
    try {
        game::Game gameEngine("R-Type", "assets/icon.png");
        gameEngine.scene(main_menu);
    } catch (game::Exception &e) {
        std::cerr << e.what() << std::endl;
        return (e.getReturnValue());
    } catch (const std::bad_any_cast &e) {
        std::cerr << "Error: bad any cast." << std::endl;
        return (84);
    } catch (const std::exception &e) {
        std::cerr << "Error: an error occured." << std::endl;
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error: an error occured." << std::endl;
        return (84);
    }
}
