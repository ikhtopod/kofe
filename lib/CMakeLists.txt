set(PROJECT_CORE_TARGET core)

file(GLOB_RECURSE PROJECT_CORE_HEADER_FILES "./headers/core/*.h")
file(GLOB_RECURSE PROJECT_CORE_SOURCE_FILES "./sources/core/*.cpp")

add_library(${PROJECT_CORE_TARGET} STATIC
    ${PROJECT_CORE_HEADER_FILES}
    ${PROJECT_CORE_SOURCE_FILES})

target_include_directories(${PROJECT_CORE_TARGET}
    PUBLIC
    ${THIRDPARTY_DIRECTORY}/glfw/include
    ${THIRDPARTY_DIRECTORY}/glm
    ${PROJECT_LIB_DIRECTORY}/headers
    PRIVATE
    ${PROJECT_LIB_DIRECTORY}/headers/core)

target_link_libraries(${PROJECT_CORE_TARGET}
    glfw ${GLFW_LIBRARIES}
    glad-4.6-core stb)
