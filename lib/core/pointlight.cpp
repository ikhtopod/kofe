#include "pointlight.h"

#include "everywhere.h"
#include "mesh.h"


namespace {

static const std::vector<Vertex> VERTICES {
    { { 0.000000, 0.000000, 0.000000 }, { 0.0, 0.0 } }, // dummy item
    { { 0.000000, -0.100000, -0.000000 }, { 0.0, 0.0 } },
    { { 0.000000, -0.086603, -0.050000 }, { 0.0, 0.0 } },
    { { 0.029389, -0.086603, -0.040451 }, { 0.0, 0.0 } },
    { { 0.000000, -0.050000, -0.086603 }, { 0.0, 0.0 } },
    { { 0.000000, 0.000000, -0.100000 }, { 0.0, 0.0 } },
    { { 0.058779, 0.000000, -0.080902 }, { 0.0, 0.0 } },
    { { 0.050904, -0.050000, -0.070063 }, { 0.0, 0.0 } },
    { { 0.000000, 0.050000, -0.086603 }, { 0.0, 0.0 } },
    { { 0.000000, 0.086603, -0.050000 }, { 0.0, 0.0 } },
    { { 0.029389, 0.086603, -0.040451 }, { 0.0, 0.0 } },
    { { 0.050904, 0.050000, -0.070063 }, { 0.0, 0.0 } },
    { { 0.000000, 0.100000, 0.000000 }, { 0.0, 0.0 } },
    { { 0.047553, 0.086603, -0.015451 }, { 0.0, 0.0 } },
    { { 0.082364, 0.050000, -0.026762 }, { 0.0, 0.0 } },
    { { 0.082364, -0.050000, -0.026762 }, { 0.0, 0.0 } },
    { { 0.047553, -0.086603, -0.015451 }, { 0.0, 0.0 } },
    { { 0.095106, 0.000000, -0.030902 }, { 0.0, 0.0 } },
    { { 0.082364, -0.050000, 0.026762 }, { 0.0, 0.0 } },
    { { 0.047553, -0.086603, 0.015451 }, { 0.0, 0.0 } },
    { { 0.082364, 0.050000, 0.026762 }, { 0.0, 0.0 } },
    { { 0.095106, -0.000000, 0.030902 }, { 0.0, 0.0 } },
    { { 0.047553, 0.086603, 0.015451 }, { 0.0, 0.0 } },
    { { 0.050904, -0.050000, 0.070063 }, { 0.0, 0.0 } },
    { { 0.029389, -0.086603, 0.040451 }, { 0.0, 0.0 } },
    { { 0.050904, 0.050000, 0.070063 }, { 0.0, 0.0 } },
    { { 0.058779, -0.000000, 0.080902 }, { 0.0, 0.0 } },
    { { 0.029389, 0.086603, 0.040451 }, { 0.0, 0.0 } },
    { { 0.000000, -0.050000, 0.086603 }, { 0.0, 0.0 } },
    { { 0.000000, -0.086603, 0.050000 }, { 0.0, 0.0 } },
    { { 0.000000, 0.050000, 0.086603 }, { 0.0, 0.0 } },
    { { 0.000000, -0.000000, 0.100000 }, { 0.0, 0.0 } },
    { { 0.000000, 0.086603, 0.050000 }, { 0.0, 0.0 } },
    { { -0.050904, -0.050000, 0.070063 }, { 0.0, 0.0 } },
    { { -0.029389, -0.086603, 0.040451 }, { 0.0, 0.0 } },
    { { -0.050904, 0.050000, 0.070063 }, { 0.0, 0.0 } },
    { { -0.058779, -0.000000, 0.080902 }, { 0.0, 0.0 } },
    { { -0.029389, 0.086603, 0.040451 }, { 0.0, 0.0 } },
    { { -0.082364, 0.050000, 0.026762 }, { 0.0, 0.0 } },
    { { -0.095106, -0.000000, 0.030902 }, { 0.0, 0.0 } },
    { { -0.047553, 0.086603, 0.015451 }, { 0.0, 0.0 } },
    { { -0.047553, -0.086603, 0.015451 }, { 0.0, 0.0 } },
    { { -0.082364, -0.050000, 0.026762 }, { 0.0, 0.0 } },
    { { -0.047553, 0.086603, -0.015451 }, { 0.0, 0.0 } },
    { { -0.047553, -0.086603, -0.015451 }, { 0.0, 0.0 } },
    { { -0.095106, 0.000000, -0.030902 }, { 0.0, 0.0 } },
    { { -0.082364, -0.050000, -0.026762 }, { 0.0, 0.0 } },
    { { -0.082364, 0.050000, -0.026762 }, { 0.0, 0.0 } },
    { { -0.029389, -0.086603, -0.040451 }, { 0.0, 0.0 } },
    { { -0.058779, 0.000000, -0.080902 }, { 0.0, 0.0 } },
    { { -0.050904, -0.050000, -0.070063 }, { 0.0, 0.0 } },
    { { -0.029389, 0.086603, -0.040451 }, { 0.0, 0.0 } },
    { { -0.050904, 0.050000, -0.070063 }, { 0.0, 0.0 } }
};

static std::vector<GLuint> indices {
    1, 2, 3,
    5, 7, 4,
    9, 11, 8,
    4, 3, 2,
    8, 6, 5,
    9, 12, 10,
    10, 14, 11,
    7, 16, 3,
    11, 17, 6,
    10, 12, 13,
    1, 3, 16,
    6, 15, 7,
    15, 19, 16,
    14, 21, 17,
    13, 12, 22,
    1, 16, 19,
    17, 18, 15,
    13, 20, 14,
    18, 24, 19,
    20, 26, 21,
    22, 12, 27,
    1, 19, 24,
    21, 23, 18,
    22, 25, 20,
    23, 29, 24,
    25, 31, 26,
    27, 12, 32,
    1, 24, 29,
    26, 28, 23,
    27, 30, 25,
    28, 34, 29,
    30, 36, 31,
    32, 12, 37,
    1, 29, 34,
    31, 33, 28,
    32, 35, 30,
    35, 39, 36,
    37, 12, 40,
    1, 34, 41,
    36, 42, 33,
    37, 38, 35,
    33, 41, 34,
    40, 12, 43,
    1, 41, 44,
    39, 46, 42,
    40, 47, 38,
    42, 44, 41,
    38, 45, 39,
    1, 44, 48,
    45, 50, 46,
    43, 52, 47,
    46, 48, 44,
    47, 49, 45,
    43, 12, 51,
    1, 48, 2,
    49, 4, 50,
    51, 8, 52,
    50, 2, 48,
    52, 5, 49,
    51, 12, 9,
    5, 6, 7,
    9, 10, 11,
    4, 7, 3,
    8, 11, 6,
    10, 13, 14,
    7, 15, 16,
    11, 14, 17,
    6, 17, 15,
    15, 18, 19,
    14, 20, 21,
    17, 21, 18,
    13, 22, 20,
    18, 23, 24,
    20, 25, 26,
    21, 26, 23,
    22, 27, 25,
    23, 28, 29,
    25, 30, 31,
    26, 31, 28,
    27, 32, 30,
    28, 33, 34,
    30, 35, 36,
    31, 36, 33,
    32, 37, 35,
    35, 38, 39,
    36, 39, 42,
    37, 40, 38,
    33, 42, 41,
    39, 45, 46,
    40, 43, 47,
    42, 46, 44,
    38, 47, 45,
    45, 49, 50,
    43, 51, 52,
    46, 50, 48,
    47, 52, 49,
    49, 5, 4,
    51, 9, 8,
    50, 4, 2,
    52, 8, 5
};

std::shared_ptr<Mesh> CreateSphere() {
    std::shared_ptr<Shader> tempShader {
        new Shader {
                std::filesystem::path { R"vert(./resources/shaders/default.vert)vert" },
                std::filesystem::path { R"frag(./resources/shaders/default.frag)frag" },
        }
    };

    tempShader->SetUniformProcessingFunc([](Shader*) {});

    std::shared_ptr<Texture> tempTexture {
        new Texture {
                std::filesystem::path { R"png(./resources/textures/texture_01.png)png" },
        }
    };

    std::shared_ptr<Material> tempMaterial { new Material {} };
    tempMaterial->GetShaders().Add(tempShader);
    tempMaterial->GetTextures().Add(tempTexture);

    Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Add(tempMaterial);
    size_t materialId = Everywhere::Instance().Get<MaterialStorage>().GetMaterials().Size() - 1;

    std::shared_ptr<Mesh> mesh { new Mesh(::VERTICES, ::indices) };
    mesh->SetMaterialId(materialId);

    return mesh;
}

} // namespace


PointLight::PointLight() :
    Light {} {
    m_children.Add(std::shared_ptr<Object>(::CreateSphere()));
}
