cmake_minimum_required(VERSION 3.5)

project(MOSZE)


set(SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/SDL2/cmake)
set(SDL2_ttf_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/SDL_ttf/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL2_ttf REQUIRED)

add_executable(MOSZE
    main.cpp
    entity.cpp
    entity.hpp
    enemy.cpp
    enemy.hpp
    player.cpp
    player.hpp
    inventory.cpp
    inventory.hpp
    text.cpp
    text.hpp
    maze.cpp
    maze.hpp
    #projectile.hpp
    #projectile.cpp
    #texturelist.cpp
    #texturelist.h
    #texture.cpp
    #texture.h
)

target_include_directories(MOSZE
    PUBLIC ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(MOSZE 
    ${SDL2_LIBRARIES} 
    SDL2_ttf::SDL2_ttf
)
