cmake_minimum_required(VERSION 3.16)
project(kofe LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_TARGET kofe)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(-DDEBUG -DGLM_ENABLE_EXPERIMENTAL -Wall -Wextra)
    add_link_options(-lGL -pthread -lX11 -lXrandr -lXi)
else ()
    add_compile_options(-DGLM_ENABLE_EXPERIMENTAL -Wall -Wextra -O2 -flto)
    add_link_options(-lGL -pthread -lX11 -lXrandr -lXi -Wl,--strip-all)
endif ()

set(THIRDPARTY_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
set(PROJECT_LIB_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory(${THIRDPARTY_DIRECTORY})
add_subdirectory(${PROJECT_LIB_DIRECTORY})

add_executable(${PROJECT_TARGET} main.cpp)

target_link_libraries(${PROJECT_TARGET} core)


##### Copy Resources #####
set(RESOURES_DIRETORIES resources)

foreach (RESOURCES_DIR ${RESOURES_DIRETORIES})
    if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR}" AND
            IS_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR}")

        add_custom_command(TARGET ${PROJECT_TARGET} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory
            ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR})
    endif ()

    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_DIR}" AND
            IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_DIR}")

        add_custom_command(TARGET ${PROJECT_TARGET} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_DIR}
            ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR})
    endif ()
endforeach ()
##########################
