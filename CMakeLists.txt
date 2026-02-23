cmake_minimum_required(VERSION 3.16)
project(6502-emu)

add_executable(emu)

file(GLOB SRC "src/*")
find_package(Catch2 REQUIRED)

target_sources(emu PRIVATE ${SRC})
target_include_directories(emu PRIVATE "include")

add_subdirectory("test")