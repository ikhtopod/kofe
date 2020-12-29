cmake_minimum_required(VERSION 3.16)
project(seductive_dream_engine LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(-DDEBUG -Wall -Wextra)
    add_link_options(-lGL -pthread -lX11 -lXrandr -lXi)
else ()
    add_compile_options(-Wall -Wextra -O2 -flto)
    add_link_options(-lGL -pthread -lX11 -lXrandr -lXi -Wl,--strip-all)
endif ()

if (WIN32)
    set(PROJECT_TARGET sde.exe)
else ()
    set(PROJECT_TARGET sde)
endif ()

add_executable(${PROJECT_TARGET} main.cpp)
target_include_directories(${PROJECT_TARGET} PRIVATE ./thirdparty/glad/include)
