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


set(THIRDPARTY_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
add_subdirectory(${THIRDPARTY_DIRECTORY})


add_executable(${SDE_PROJECT_TARGET} main.cpp)

target_include_directories(${SDE_PROJECT_TARGET} PRIVATE
    ${THIRDPARTY_DIRECTORY}/glfw/include
    ${THIRDPARTY_DIRECTORY}/glm)

target_link_libraries(${SDE_PROJECT_TARGET} glfw ${GLFW_LIBRARIES} glad stb)


##### Copy Resources #####
set(RESOURES_DIRETORIES resources)

foreach (RESOURCES_DIR ${RESOURES_DIRETORIES})
    if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR}" AND IS_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR}")
        add_custom_command(TARGET ${SDE_PROJECT_TARGET} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory
            ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR})
    endif ()

    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_DIR}" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_DIR}")
        add_custom_command(TARGET ${SDE_PROJECT_TARGET} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR})
    endif ()
endforeach ()
##########################
