cmake_minimum_required(VERSION 3.16)
project(seductive_dream_engine LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(-Wall -Wextra -pedantic)
    add_link_options(-lGL -pthread -lX11 -lXrandr -lXi)
else ()
    add_compile_options(-DDEBUG -Wall -Wextra -O2 -flto)
    add_link_options(-lGL -pthread -lX11 -lXrandr -lXi -Wl,--strip-all)
endif ()

add_executable(seductive_dream_engine main.cpp)
