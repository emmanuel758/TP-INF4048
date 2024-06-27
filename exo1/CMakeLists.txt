cmake_minimum_required(VERSION 3.0)

project(exo1 LANGUAGES C)

add_executable(exo1 main.c)

install(TARGETS exo1 RUNTIME DESTINATION bin)
