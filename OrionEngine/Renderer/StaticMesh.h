#pragma once
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Texture2D.h"
#include "Material.h"
#include <string>
#include <vector>

namespace oe {

struct StaticVertex {
    StaticVertex();
    StaticVertex(const glm::vec3 &pos, const glm::vec3 &normal, const glm::vec2 &texCoord);

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

class StaticSubMesh {
public:
    StaticSubMesh(const std::vector<StaticVertex> &vertices, const std::vector<uint> indices,
                  const std::string &diffuseMapPath, const std::string &specularMapPath, const Material &material);
    ~StaticSubMesh();

    const std::vector<StaticVertex> &GetVertices() const;
    const std::vector<uint> &GetIndices() const;
    const VertexBuffer *GetVertexBuffer() const;
    const IndexBuffer *GetIndexBuffer() const;
    const Texture2D *GetDiffuseMap() const;
    const Texture2D *GetSpecularMap() const;
    const Material &GetMaterial() const;

private:
    std::vector<StaticVertex> mVertices;
    std::vector<uint> mIndices;
    VertexBuffer *mVertexBuffer;
    IndexBuffer *mIndexBuffer;
    Texture2D *mDiffuseMap, *mSpecularMap;
    Material mMaterial;
};

class StaticMesh {
public:
    StaticMesh(const std::string &filename);
    ~StaticMesh();

    const std::vector<StaticSubMesh*> &GetSubMeshes() const;

private:
    std::vector<StaticSubMesh*> mSubMeshes;
};

}