cmake_minimum_required(VERSION 3.16)
project(seductive_dream_engine LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDE_PROJECT_TARGET sde)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(-DDEBUG -Wall -Wextra)
    add_link_options(-lGL -pthread -lX11 -lXrandr -lXi)
else ()
    add_compile_options(-Wall -Wextra -O2 -flto)
    add_link_options(-lGL -pthread -lX11 -lXrandr -lXi -Wl,--strip-all)
endif ()

add_subdirectory(./thirdparty/glfw ./thirdparty/glm)

add_executable(${SDE_PROJECT_TARGET} main.cpp ./thirdparty/glad/src/glad.c)

target_include_directories(${SDE_PROJECT_TARGET} PRIVATE
        ./thirdparty/glfw/include
        ./thirdparty/glad/include
        ./thirdparty/glm
        ./thirdparty/stb)

target_link_libraries(${SDE_PROJECT_TARGET} glfw ${GLFW_LIBRARIES})
