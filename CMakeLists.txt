cmake_minimum_required(VERSION 3.8)
project(lab5c)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/Mario.c src/MainState.c src/main.c src/JeuState.c src/GameState.c)
add_executable(lab7yasp ${SOURCE_FILES})