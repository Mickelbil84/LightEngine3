#include "le3_sprite.h"

LE3Sprite::LE3Sprite(std::string name, LE3Material* material, LE3Texture* spriteTexture) : LE3Object(name)
{
    m_material = material;
    m_spriteTexture = spriteTexture;

    std::vector<LE3Vertex> square;
    glm::vec3 v1(-1.f, -1.f, 0.f);
    glm::vec3 v2(-1.f,  1.f, 0.f);
    glm::vec3 v3( 1.f,  1.f, 0.f);
    glm::vec3 v4( 1.f, -1.f, 0.f);
    glm::vec2 u1(0.f, 0.f);
    glm::vec2 u2(0.f, 1.f);
    glm::vec2 u3(1.f, 1.f);
    glm::vec2 u4(1.f, 0.f);
    glm::vec3 n(0.f, 0.f, 1.f);
    square.push_back(VertexFromGLM(v1, u1, n));
    square.push_back(VertexFromGLM(v2, u2, n));
    square.push_back(VertexFromGLM(v3, u3, n));
    square.push_back(VertexFromGLM(v1, u1, n));
    square.push_back(VertexFromGLM(v3, u3, n));
    square.push_back(VertexFromGLM(v4, u4, n));
    m_mesh = new LE3Mesh<LE3Vertex>();
    m_mesh->LoadMeshData(square);
}

void LE3Sprite::Draw()
{
    if (!m_material || !m_mesh || !m_spriteTexture)
        return;
    m_material->SetDiffuseTexture(m_spriteTexture);
    m_material->bUseDiffuseTexture = true;
    m_material->GetShader()->Use();
    m_material->GetShader()->Uniform("model", m_globalModelMatrix);
    m_material->Apply();
    // glClear(GL_DEPTH_BUFFER_BIT);
    m_mesh->Draw();
}

void LE3Sprite::UpdateAssets(LE3AssetManager& assets)
{
    m_material = assets.GetMaterial(m_materialName);
    m_spriteTexture = assets.GetTexture(m_spriteTextureName);
}

LE3Material* LE3Sprite::GetMaterial()
{
    return m_material;
}