cmake_minimum_required(VERSION 3.29)
project(Projet C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet main.c
        neuronne.h
        neuronne.c
        couche.h
        couche.c)
