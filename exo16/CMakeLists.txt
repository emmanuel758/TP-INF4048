cmake_minimum_required(VERSION 3.0)

project(exo16 LANGUAGES C)

add_executable(exo16 main.c)

install(TARGETS exo16 RUNTIME DESTINATION bin)
