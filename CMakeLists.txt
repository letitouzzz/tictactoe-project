cmake_minimum_required(VERSION 4.0)
project(main C)

set(CMAKE_C_STANDARD 11)

add_executable(main
        main.c
        "PLAY (Valentin).c"
        "SETTINGS (Maxime).c"
        "PLAY (Antoine S).c"
        "STATS (Antoine T).c"
        SETTINGS.h
        "PLAY(1V1).h"
        "PLAY(VS IA).h"
)

