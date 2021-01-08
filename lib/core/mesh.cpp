#include "mesh.h"

#include <iostream>


Mesh::Mesh() {}

Mesh::~Mesh() {}

void Mesh::Processing() {
    static unsigned counter = 0;
    std::cout << "[Mesh] Processing #" << counter++ << std::endl;
}
