cmake_minimum_required(VERSION 3.29)
project(DavidCorentin C)

set(CMAKE_C_STANDARD 11)

add_executable(DavidCorentin main.c
        couche.h
        couche.c
        neuronne.c)
