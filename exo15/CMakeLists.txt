cmake_minimum_required(VERSION 3.0)

project(exo15 LANGUAGES C)

add_executable(exo15 main.c)

install(TARGETS exo15 RUNTIME DESTINATION bin)
