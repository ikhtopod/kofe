#include "shader.h"

#include <iostream>


Shader::Shader() {}

Shader::~Shader() {}

void Shader::Processing() {
    static unsigned counter = 0;
    std::cout << "[Shader] Processing #" << counter++ << std::endl;
}
