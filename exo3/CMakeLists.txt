cmake_minimum_required(VERSION 3.0)

project(exo3 LANGUAGES C)

add_executable(exo3 main.c)

install(TARGETS exo3 RUNTIME DESTINATION bin)
