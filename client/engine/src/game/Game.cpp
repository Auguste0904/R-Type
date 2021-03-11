/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-eliot.le-gall
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include <dlfcn.h>

/**
 * \brief Game engine constructor
 *
 * Create a game engine instance, size of the window is by default the client screen size
 *
 * \param title Title of the window. (e.g.: "Best game")
 * \param icon Path to the window icon. (e.g.: "./assets/icon.png")
 **/
game::Game::Game(const std::string &title, const std::string &icon)
{
    game::Game::__ENGINE_(this);
    this->_resolution = {
        static_cast<game::int32>(sf::VideoMode::getDesktopMode().width),
        static_cast<game::int32>(sf::VideoMode::getDesktopMode().height)
    };
    this->_title = title;
    this->_window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(
            static_cast<game::int32>(this->_resolution.x),
            static_cast<game::int32>(this->_resolution.y)
        ),
        this->_title,
        sf::Style::Fullscreen
    );
    this->_view = std::make_unique<sf::View>();
    this->_view->setSize(sf::Vector2f(1920, 1080));
    this->_view->setCenter(sf::Vector2f(1920 / 2, 1080 / 2));
    this->_window->setView(*(this->_view.get()));
    this->_mouseVisible = true;
    this->_fullscreen = true;
    this->_closed = false;
    this->setIcon(icon);
    this->setFramerate(60);
    this->_keyStroke = {};
    this->_callback = NULL;
    if (!this->_music.openFromFile("assets/musics/theme.ogg"))
        throw (game::Exception("Error: bad music construction.", 84));
    this->setMusicVolume(100);
    this->playMusic();
}

game::Game::~Game()
{
    this->unloadAllLibrary();
}

/**
 * \brief Get the engine
 *
 * \return a 'game::Game::__ENGINE_'.
 **/
game::Game *game::Game::getEngine(void)
{
    return (game::Game::__ENGINE_());
}


/**
 * \brief Get the EntityManager
 *
 * \param game
 * \return a 'game::Game::__ENGINE_'.
 **/
game::Game *game::Game::__ENGINE_(Game *game)
{
    static Game *__ENGINE_;

    if (game != nullptr)
        __ENGINE_ = game;
    return (__ENGINE_);
}

/**
 * \brief The scene function init any menu
 *
 * \param callback_init Reference to function whic is a callback
 **/
void game::Game::scene(void (&callback_init)(void))
{
    std::vector<void (*)(void)> &system_list = this->systemManager().getSystems();
    callback_init();
    while (this->_window->isOpen()) {
        try {
            this->manageEvent();
            if (this->_callback)
                this->_callback();
            this->clear();
            system_list = this->systemManager().getSystems();
            for (auto &system : system_list) {
                system();
            }
            this->_window->display();
        } catch (game::exception::ChangeScene &e) {
            #ifdef __DEBUG
            std::cout << "Scene has changed!" << std::endl;
            #endif
        }
    }
}

void game::Game::setCallback(void (*callback)(void))
{
    this->_callback = callback;
}

/**
 * \brief Get the key
 *
 * \param key unicode of the key (ASCII)
 * \return a booleen with a true or false state.
 **/
bool game::Game::getKey(const game::int32 &key)
{
    return (this->_keyStroke[key]);
}


/**
 * \brief Get the last key ascii
 *
 * \return a 'game::int32'.
 **/
game::int32 game::Game::getLastKey(void) const
{
    return (this->_lastKey);
}

/**
 * \brief Get the last key ascii
 *
 * \return a 'game::int32'.
 **/
game::int32 game::Game::getLastKeyAscii(void) const
{
    return (this->_lastKeyAscii);
}

/**
 * \brief Get the mouse click.
 *
 * \return a 'bool'.
 **/
bool game::Game::getMouseClick(void)
{
    return (this->_click);
}

/**
 * \brief Get the Mouse click
 *
 * \return a 'bool'.
 **/
bool game::Game::getMouseClickOnce(void)
{
    return (this->_clickOnce);
}

/**
 * \brief Manage events
 **/
void game::Game::manageEvent(void)
{
    this->_lastKey = -1;
    this->_clickOnce = false;
    this->_lastKeyAscii = 0;
    while (this->_window->pollEvent(this->_event)) {
        if (this->_event.type == this->_event.Closed)
            this->close();
        if (this->_event.type == sf::Event::TextEntered)
            this->_lastKeyAscii = this->_event.text.unicode;
        if (this->_event.type == this->_event.KeyPressed && this->_keyStroke[this->_event.key.code] == false) {
            this->_keyStroke[this->_event.key.code] = true;
            this->_lastKey = this->_event.key.code;
        } else if (this->_event.type == this->_event.KeyReleased)
            this->_keyStroke[this->_event.key.code] = false;
        if (this->_event.type == this->_event.MouseButtonPressed && this->_click == false) {
            this->_clickOnce = true;
            this->_click = true;
        } else if (this->_event.type == this->_event.MouseButtonReleased)
            this->_click = false;
    }
}

/**
 * \brief Get the pointer of the window
 *
 * \return a 'sf::RenderWindow *' type.
 **/
sf::RenderWindow *game::Game::getWindow(void)
{
    return (this->_window.get());
}

/**
 * \brief Get the EntityManager
 *
 * \return a 'game::EntityManager' type filled with x methods which handle entities.
 **/
game::EntityManager &game::Game::entityManager(void)
{
    return (this->_entityManager);
}

/**
 * \brief Get the ComponentManager
 *
 * \return a 'game::ComponentManager' type filled with x methods which handle components.
 **/
game::ComponentManager &game::Game::componentManager(void)
{
    return (this->_componentManager);
}

/**
 * \brief Get the SystemManager
 *
 * \return a 'game::SystemManager' type filled with x methods which handle the system.
 **/
game::SystemManager &game::Game::systemManager(void)
{
    return (this->_systemManager);
}

/**
 * \brief Set window resolution (width-height)
 *
 * \param resolution Height and width of the window (e.g.: {1920, 1080})
 **/
void game::Game::setResolution(const sf::Vector2i &resolution)
{
    if (resolution.x == 0 || resolution.y == 0)
        return;
    this->_resolution = resolution;
    this->close();
    this->_window->create(
        sf::VideoMode(
            static_cast<game::int32>(resolution.x),
            static_cast<game::int32>(resolution.y)
        ),
        this->getTitle(),
        (resolution.x != static_cast<game::int32>(sf::VideoMode::getDesktopMode().width) || resolution.y != static_cast<game::int32>(sf::VideoMode::getDesktopMode().height)) ? (sf::Style::Close) : sf::Style::Fullscreen
    );
    this->_window->setView(*(this->_view.get()));
    this->setIcon(this->getIcon());
    this->setFramerate(60);
}

/**
 * \brief Get window resolution (width-height)
 *
 * \return a 'game::vector2f' type filled with x and y sizes.
 **/
const sf::Vector2i &game::Game::getResolution(void) const
{
    return (this->_resolution);
}

/**
 * \brief Set an icon to the window.
 *
 * \param icon Path to the window icon. (e.g.: "./assets/icon.png")
 **/
void game::Game::setIcon(const std::string &icon)
{
    if (icon.length()) {
        if (!this->_iconName.loadFromFile(icon))
            game::Exception("Error: bad icon construction.", 84);
        this->_window->setIcon(this->_iconName.getSize().x, this->_iconName.getSize().y, this->_iconName.getPixelsPtr());
        this->_icon = icon;
    }
}

/**
 * \brief Get active icon image path.
 *
 * \return Path string to the window icon. (e.g.: "./assets/icon.png")
 **/
const std::string &game::Game::getIcon(void) const
{
    return (this->_icon);
}

/**
 * \brief Set a title to the window.
 *
 * \param title Title of the window. (e.g.: "R-Type")
 **/
void game::Game::setTitle(const std::string &title)
{
    this->_window->setTitle(title);
    this->_title = title;
}

/**
 * \brief Get the active window title/name
 *
 * \return String which contains the window title. (e.g.: "R-Type")
 **/
const std::string &game::Game::getTitle(void) const
{
    return (this->_title);
}

/**
 * \brief Change the sound volume.
 *
 * \param volume Number x of the volume (x / 100). (e.g.: 50)
 **/
void game::Game::setSoundVolume(const game::uint8 &volume)
{
    this->_soundVolume = volume;
}

/**
 * \brief Get active sound value, which stands for the audio volume
 *
 * \return Unisgned 8-bit int with a range from 0 to 100%
 **/
const game::uint8 &game::Game::getSoundVolume(void) const
{
    return (this->_soundVolume);
}

/**
 * \brief Change the music volume.
 *
 * \param volume Number x of the volume (x / 100). (e.g.: 50)
 **/
void game::Game::setMusicVolume(const game::uint8 &volume)
{
    this->_musicVolume = volume;
}

/**
 * \brief Get active music value, which stands for the audio volume
 *
 * \return Unisgned 8-bit int with a range from 0 to 100%
 **/
const game::uint8 &game::Game::getMusicVolume(void) const
{
    return (this->_musicVolume);
}

/**
 * \brief Set the mouse visible on the screen.
 *
 * \param visible Booleen defined by a true or false state. (e.g.: True)
 **/
void game::Game::setMouseVisible(const bool &visible)
{
    this->_window->setMouseCursorVisible(visible);
    this->_mouseVisible = visible;
}

/**
 * \brief Check if the mouse is visible or not with a boolean type.
 *
 * \return Bool
 **/
const bool &game::Game::isMouseVisible(void) const
{
    return (this->_mouseVisible);
}

/**
 * \brief Set the screen resolution to fullscreen.
 *
 * \param fullscreen Booleen defined by a true or false state. (e.g.: True)
 **/
void game::Game::setFullscreen(const bool &fullscreen)
{
    if (fullscreen == this->_fullscreen)
        return;
    if (fullscreen == true) {
        this->close();
        this->_window->create(
            sf::VideoMode(
                sf::VideoMode::getDesktopMode().width,
                sf::VideoMode::getDesktopMode().height
            ),
            this->getTitle(),
            sf::Style::Fullscreen
        );
    } else {
        this->close();
        this->_window->create(
            sf::VideoMode(
                static_cast<game::int32>(this->getResolution().x),
                static_cast<game::int32>(this->getResolution().y)
            ),
            this->getTitle(),
            sf::Style::Close | sf::Style::Resize
        );
    }
    this->_fullscreen = fullscreen;
}

/**
 * \brief Check if the window is windowed or not and return a true or false state.
 *
 * \return Bool
 **/
const bool &game::Game::isFullscreen(void) const
{
    return (this->_fullscreen);
}

/**
 * \brief Limit the framerate to a maximum fixed frequency. If a limit is set, the window will use a small delay after each call to display() to ensure that the current frame lasted long enough to match the framerate limit. SFML will try to match the given limit as much as it can, but since it internally uses sf::sleep, whose precision depends on the underlying OS, the results may be a little unprecise as well (for example, you can get 65 FPS when requesting 60).
 *
 * \param volume Number x in frames per seconds. (e.g.: 30)
 **/
void game::Game::setFramerate(const game::uint8 &framerate)
{
    this->_window->setFramerateLimit(framerate);
    this->_framerate = framerate;
}

/**
 * \brief Get framerate value as an unsigned 8-bit int
 *
 * \return 8-bit unsigned int
 **/
const game::uint8 &game::Game::getFramerate(void) const
{
    return (this->_framerate);
}

/**
 * \brief Close the window and destroy all the attached resources.
 **/
void game::Game::close(void)
{
    this->_closed = true;
    this->_window->close();
}

void game::Game::playMusic()
{
    this->_music.setVolume(this->_musicVolume);
    this->_music.setLoop(true);
    this->_music.play();
}

void game::Game::openSound(const std::string &pathSound)
{
    if (!this->_soundBuffer.loadFromFile(pathSound))
        throw (game::Exception("Error: bad sound construction.", 84));
}

void game::Game::playSound()
{
    this->_sound.setBuffer(this->_soundBuffer);
    this->_sound.setVolume(this->_soundVolume);
    this->_sound.play();
}

/**
 * \brief Check if the engine window is closed as a boolean value
 *
 * \return Boolean
 **/
const bool &game::Game::isClosed(void) const
{
    return (this->_closed);
}

/**
 * \brief Clear window with a specified color or not
 *
 * \param color Takes a sf::Color argument as a RGB color
 **/
void game::Game::clear(const sf::Color &color)
{
    this->_window->clear(color);
}

/**
 * \brief The loadLibrary function load the shared libraries given in paramter.
 *
 * \param lib std::string which is the name of the shared library.
 **/
void game::Game::loadLibrary(const std::string &lib)
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
// CODE WINDOWS CLARA
{
    void *tmp_ld = NULL;
    std::string str = ".exe";
    std::string tmp_lib = lib;

    for (auto &elem : this->_libList) {
        if (elem.first == lib) {
            return;
        }
    }
    tpm_lib.append(str);
    tmp_ld = LoadLibrary(tmp_lib);
    if (tmp_ld == NULL)
        throw (game::Exception(std::string(GetLastError())));
    this->_libList.push_back({lib, tmp_ld});
}
#else
// CODE LINUX
{
    void *tmp_ld = NULL;

    for (auto &elem : this->_libList) {
        if (elem.first == lib)
            return;
    }
    tmp_ld = dlopen(lib.c_str(), RTLD_NOW);
    if (tmp_ld == NULL)
        throw (game::Exception(std::string(dlerror()), 84));
    this->_libList.push_back({lib, tmp_ld});
}
#endif

/**
 * \brief The unloadLibrary function unload the shared libraries given in paramter.
 *
 * \param lib std::string which is the name of the shared library.
 **/
void game::Game::unloadLibrary(const std::string &lib)
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
{
    for(size_t i = 0; i < this->_libList.size(); i++) {
        if (this->_libList[i].first == lib) {
            FreeLibrary(this->_libList[i].second);
            this->_libList.erase(this->_libList.begin() + i);
            return;
        }
    }
}
#else
{
    for (size_t i = 0; i < this->_libList.size(); i++) {
        if (this->_libList[i].first == lib) {
            dlclose(this->_libList[i].second);
            this->_libList.erase(this->_libList.begin() + i);
            return;
        }
    }
}
#endif

/**
 * \brief The unloadLibrary function unload all the shared libraries.
 **/
void game::Game::unloadAllLibrary(void)
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
{
    while(this->_libList.size()) {
        FreeLibrary(this->_liblist[0].second);
        this->_libList.erase(this->_libList.begin());
    }
}
#else
{
    while (this->_libList.size()) {
        dlclose(this->_libList[0].second);
        this->_libList.erase(this->_libList.begin());
    }
}
#endif

/**
 * \brief The collides function get collision between two sprites.
 *
 * \return Return booleen which is a true or false state.
 **/
bool game::Game::collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
{
    return (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()));
}