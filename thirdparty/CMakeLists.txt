set(GLAD_PROJECT glad-4.6-core)
set(GLAD_DIRECTORY ${THIRDPARTY_DIRECTORY}/glad/gl/4.6/core)
add_library(${GLAD_PROJECT} STATIC ${GLAD_DIRECTORY}/include/glad/glad.h ${GLAD_DIRECTORY}/src/glad.c)
target_include_directories(${GLAD_PROJECT} PUBLIC ${GLAD_DIRECTORY}/include)

set(STB_PROJECT stb)
set(STB_DIRECTORY ${THIRDPARTY_DIRECTORY}/stb)
add_library(${STB_PROJECT} STATIC ${STB_DIRECTORY}/headers/stb_image.h ${STB_DIRECTORY}/sources/stb_image.c)
target_include_directories(${STB_PROJECT} PUBLIC ${STB_DIRECTORY}/headers)

add_subdirectory(${THIRDPARTY_DIRECTORY}/glm)
add_subdirectory(${THIRDPARTY_DIRECTORY}/glfw)
