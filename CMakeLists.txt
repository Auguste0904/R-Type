cmake_minimum_required(VERSION 3.10)

project(r-type)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(UNIX)
    add_definitions(-Wall -Wextra -g3 -pedantic -Wno-deprecated-copy -lboost_serialization)
elseif(WIN32)

else()

endif(UNIX)

# Handle Conan
include(build/conanbuildinfo.cmake)
conan_basic_setup()

# ---------------------- client -------------------------------
add_executable(r-type_client
    client/game/src/main.cpp
    client/engine/src/game/Game.cpp
    client/engine/src/exception/Exception.cpp
    client/engine/src/ecs/entity/EntityManager.cpp
    client/engine/src/ecs/component/ComponentManager.cpp
    client/engine/src/ecs/system/SystemManager.cpp
    client/UDPClient/UDPClient.cpp
    client/game/src/scenes/main_menu.cpp
    client/game/src/scenes/htp_menu.cpp
    client/game/src/scenes/connect_menu.cpp
    client/game/src/scenes/settings_menu.cpp
    client/game/src/scenes/lobby_menu.cpp
    client/game/src/scenes/game_loop.cpp
    client/game/src/scenes/game_over.cpp
)

target_include_directories(r-type_client PRIVATE
    ./client/engine
    ./client/engine/include
    ./client/engine/include/game
    ./client/engine/include/exception
    ./client/engine/include/ecs
    ./client/engine/include/ecs/component
    ./client/engine/include/ecs/entity
    ./client/engine/include/ecs/system
    ./client/engine/src
    ./client/game/include
    ./client/UDPClient/
    ./common/Serializer
    ./common/UdpPacket
)

target_link_libraries(r-type_client -rdynamic ${CONAN_LIBS} -lpthread -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -ldl)











# ---------------------- server -------------------------------

add_executable(r-type_server
    server/src/main.cpp
    server/src/Server/Server.cpp
    server/src/UDPServer/UDPServer.cpp
    common/Serializer/Serializer.cpp
)

target_include_directories(r-type_server PRIVATE
    ./server
    ./server/include
    ./server/src
    ./server/src/UDPServer/
    ./server/src/Server
    ./common/Serializer
    )

target_link_libraries(r-type_server ${CONAN_LIBS} -lboost_serialization -lpthread)











# ---------------------- components -------------------------------

# Sprite
add_library(sprite SHARED
    client/game/src/components/Sprite.cpp
)
target_include_directories(sprite PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
)
target_link_libraries(sprite -fPIC -shared ${CONAN_LIBS})

# Button
add_library(button SHARED
    client/game/src/components/Button.cpp
)
target_include_directories(button PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
)
target_link_libraries(button -fPIC -shared ${CONAN_LIBS})

# Text
add_library(text SHARED
    client/game/src/components/Text.cpp
)
target_include_directories(text PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
)
target_link_libraries(text -fPIC -shared ${CONAN_LIBS})

# Textarea
add_library(textarea SHARED
    client/game/src/components/Textarea.cpp
)
target_include_directories(textarea PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
)
target_link_libraries(textarea -fPIC -shared ${CONAN_LIBS})

# Slider
add_library(slider SHARED
    client/game/src/components/Slider.cpp
)
target_include_directories(slider PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
)
target_link_libraries(slider -fPIC -shared ${CONAN_LIBS})

# Parallax
add_library(parallax SHARED
    client/game/src/components/Parallax.cpp
)
target_include_directories(parallax PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
)
target_link_libraries(parallax -fPIC -shared ${CONAN_LIBS})

# Player
add_library(player SHARED
    client/game/src/components/Player.cpp
)
target_include_directories(player PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
    client/UDPClient/
)
target_link_libraries(player -fPIC -shared ${CONAN_LIBS})

# Rocket
add_library(rocket SHARED
    client/game/src/components/Rocket.cpp
)
target_include_directories(rocket PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
)
target_link_libraries(rocket -fPIC -shared ${CONAN_LIBS})

# Enemy1
add_library(enemy1 SHARED
    client/game/src/components/Enemy1.cpp
)
target_include_directories(enemy1 PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
)
target_link_libraries(enemy1 -fPIC -shared ${CONAN_LIBS})

# Rocket Enemy
add_library(rocketEnemy SHARED
    client/game/src/components/RocketEnemy.cpp
)
target_include_directories(rocketEnemy PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
)
target_link_libraries(rocketEnemy -fPIC -shared ${CONAN_LIBS})

# Mob Spawner
add_library(mobspawner SHARED
    client/game/src/components/MobSpawner.cpp
)
target_include_directories(mobspawner PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
)
target_link_libraries(mobspawner -fPIC -shared ${CONAN_LIBS})


# Boss
add_library(boss SHARED
    client/game/src/components/Boss.cpp
)
target_include_directories(boss PRIVATE
    client/engine/include/game
    client/engine/include
    client/engine/include/ecs/component
    client/engine/include/exception
    client/engine/include/ecs/entity
    client/engine/include/ecs/system
)
target_link_libraries(boss -fPIC -shared ${CONAN_LIBS})

execute_process(COMMAND cp -r ../assets .)
add_custom_command(TARGET r-type_client COMMAND cp -r ./lib ..)
