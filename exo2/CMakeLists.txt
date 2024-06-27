cmake_minimum_required(VERSION 3.0)

project(exo2 LANGUAGES C)

add_executable(exo2 main.c)

install(TARGETS exo2 RUNTIME DESTINATION bin)
