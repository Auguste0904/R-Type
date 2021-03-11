/*
** EPITECH PROJECT, 2020
** menu
** File description:
** main.cpp
*/

#include "Rtype.hpp"
#include "Main.hpp"
#include "Exception.hpp"
#include "MainMenu.hpp"

static void launchRtype()
{
    rtype::sfml = new rtype::Sfml();
    rtype::sfml->window = std::make_unique<sf::RenderWindow>();
    rtype::sfml->view = std::make_unique<sf::View>();
    rtype::sfml->window->create(sf::VideoMode(
                              sf::VideoMode::getDesktopMode().width,
                              sf::VideoMode::getDesktopMode().height),
                          "R-Type",
                          sf::Style::Fullscreen | sf::Style::Resize);
    rtype::sfml->window->setFramerateLimit(60);
    // #ifdef CENTER_ORIGIN
    // rtype::sfml->view = std::unique_ptr<sf::View>(new sf::View);
    // rtype::sfml->view->setSize(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
    // rtype::sfml->view->setCenter(sf::Vector2f(0, 0));
    // rtype::sfml->window->setView(*rtype::sfml->view);
    // #endif
    rtype::sfml->theme.openFromFile("assets/musics/theme.ogg");
    rtype::sfml->theme.play();
    rtype::sfml->theme.setLoop(true);
    std::unique_ptr<rtype::MainMenu> mainMenu = std::make_unique<rtype::MainMenu>();
    mainMenu->run();
    delete rtype::sfml;
}

int main(int ac, const char **av, const char **env)
{
    if (ac != 1)
        return (std::cerr << "Error: too much arguments" << std::endl, 84);
    av = av;
    if (!env) {
        std::cerr << "Error: no environmenent variable" << std::endl;
        return (84);
    }
    try
    {
        launchRtype();
    }
    catch (const rtype::Exception &e)
    {
        std::cerr << e.what() << '\n';
        return (84);
    }
    return 0;
}
