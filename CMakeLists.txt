cmake_minimum_required(VERSION 3.16)
project(kofe LANGUAGES C CXX)

set(ASSIMP_BUILD_ZLIB ON)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_TARGET kofe)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-DDEBUG -DGLM_ENABLE_EXPERIMENTAL -Wall)
    add_link_options(-lGL -pthread -lX11 -lXrandr -lXi -Wextra)
else ()
    add_compile_options(-DGLM_ENABLE_EXPERIMENTAL -Wall)
    add_link_options(-lGL -pthread -lX11 -lXrandr -lXi -Wextra -O2 -flto -Wl,--strip-all)
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
    if(WIN32)
        set(DESTINATION_RESOURCE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${RESOURCES_DIR}")
    else()
        set(DESTINATION_RESOURCE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR}")
    endif()

    if (EXISTS "${DESTINATION_RESOURCE_DIRECTORY}" AND IS_DIRECTORY "${BIN_RES_DIR}")

        add_custom_command(TARGET ${PROJECT_TARGET} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory
            ${DESTINATION_RESOURCE_DIRECTORY})
    endif ()

    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_DIR}" AND
            IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_DIR}")

        add_custom_command(TARGET ${PROJECT_TARGET} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_DIR}
            ${DESTINATION_RESOURCE_DIRECTORY})
    endif ()
endforeach ()
##########################
