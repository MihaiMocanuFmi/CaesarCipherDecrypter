cmake_minimum_required(VERSION 3.24)
project(CaesarCipherDecrypter C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CaesarCipherDecrypter
        main.c decrypter.c)
