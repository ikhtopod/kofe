#include <cstdlib>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/normal.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/matrix_decompose.hpp"


#define STB_IMAGE_IMPLEMENTATION
#define STB_ONLY_PNG

#include <stb_image.h>


int main() {
    std::cout << "Hello, The Seductive Dream engine!" << std::endl;
    return EXIT_SUCCESS;
}
