cmake_minimum_required(VERSION 3.0)

project(exo17 LANGUAGES C)

add_executable(exo17 main.c)

install(TARGETS exo17 RUNTIME DESTINATION bin)
