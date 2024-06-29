cmake_minimum_required(VERSION 3.0)

project(exo7 LANGUAGES C)

add_executable(exo7 main.c)

install(TARGETS exo7 RUNTIME DESTINATION bin)
