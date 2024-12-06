cmake_minimum_required(VERSION 3.29)
project(projetlo21 C)

set(CMAKE_C_STANDARD 11)

include_directories(DavidCorentin)

add_executable(projetlo21
        DavidCorentin/couche.c
        DavidCorentin/couche.h
        DavidCorentin/main.c
        DavidCorentin/neuronne.c
        DavidCorentin/neuronne.h)
