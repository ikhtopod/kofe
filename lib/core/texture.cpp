#include "texture.h"

#include <iostream>


Texture::Texture() {}

Texture::~Texture() {}

void Texture::Processing() {
    static unsigned counter = 0;
    std::cout << "[Texture] Processing #" << counter++ << std::endl;
}
