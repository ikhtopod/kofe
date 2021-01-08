#include "material.h"

#include <iostream>


Material::Material() {}

Material::~Material() {}

void Material::Processing() {
    static unsigned counter = 0;
    std::cout << "[Material] Processing #" << counter++ << std::endl;
}
