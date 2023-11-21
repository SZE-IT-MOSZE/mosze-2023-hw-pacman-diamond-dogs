cmake_minimum_required(VERSION 3.5)

project(MOSZE)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_executable(MOSZE
    main.cpp
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
    PRIVATE SDL2::SDL2
)