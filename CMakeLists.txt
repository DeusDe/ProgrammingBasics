cmake_minimum_required(VERSION 4.2)
project(ProgrammingBasics C)

set(CMAKE_C_STANDARD 23)

add_executable(ProgrammingBasics src/main.c
        src/verschluesselungen/caeser.c
        src/verschluesselungen/caeser.h
        src/verschluesselungen/verschluesselungen.h
        src/main.h
        src/Datentypen/datentypen.h
        src/Datentypen/linked_list/linked_list_int.c
        src/Datentypen/linked_list/linked_list_int.h
)
