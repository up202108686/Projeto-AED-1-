cmake_minimum_required(VERSION 3.23)
project(AED_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AED_1
        main.cpp
        Slot.h
        Student.h
        TurmaH.h
        UcTurma.h)
