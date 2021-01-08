set(SD_CORE_TARGET core)
set(SD_CORE_DIRECTORY ${SD_LIB_DIRECTORY}/core)

file(GLOB_RECURSE SD_CORE_HEADER_FILES *.h)
file(GLOB_RECURSE SD_CORE_SOURCE_FILES *.cpp)

add_library(${SD_CORE_TARGET} STATIC
    ${SD_CORE_HEADER_FILES}
    ${SD_CORE_SOURCE_FILES})

target_include_directories(${SD_CORE_TARGET} PUBLIC
    ${THIRDPARTY_DIRECTORY}/glfw/include
    ${THIRDPARTY_DIRECTORY}/glm
    ${SD_LIB_DIRECTORY})

target_link_libraries(${SD_CORE_TARGET}
    glfw ${GLFW_LIBRARIES}
    glad-4.6-core stb)
