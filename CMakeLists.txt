cmake_minimum_required(VERSION 3.28)

project(gc LANGUAGES C)

add_executable(gc
        src/main.c
        src/object.c
        src/object.h
        src/vm.c
        src/vm.h
)
