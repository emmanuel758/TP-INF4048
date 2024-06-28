cmake_minimum_required(VERSION 3.0)

project(exo6 LANGUAGES C)

add_executable(exo6 main.c)

install(TARGETS exo6 RUNTIME DESTINATION bin)
