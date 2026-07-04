cmake_minimum_required(VERSION 4.2)
project(ProgrammingBasics C)

set(CMAKE_C_STANDARD 23)

add_executable(ProgrammingBasics src/verschluesselungen/main.c
        src/verschluesselungen/caeser.c
        src/verschluesselungen/caeser.h
        src/verschluesselungen/verschluesselungen.h
        src/src.h)
