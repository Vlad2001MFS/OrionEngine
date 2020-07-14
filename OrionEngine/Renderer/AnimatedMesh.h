#pragma once
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Texture2D.h"
#include "Material.h"
#include <string>
#include <vector>

namespace oe {

//struct AnimatedVertex {
//    AnimatedVertex();
//    AnimatedVertex(const glm::vec3 &pos, const glm::vec3 &normal, const glm::vec2 &texCoord, int boneIndex, float boneWeight);
//
//    glm::vec3 position;
//    glm::vec3 normal;
//    glm::vec2 texCoord;
//    int boneIndex;
//    float boneWeight;
//};
//
//struct Bone {
//    Bone();
//    Bone(const Bone *parent, const glm::mat4 &local);
//
//    const Bone *parent;
//    glm::mat4 local, absolute;
//};
//
//class AnimatedSubMesh {
//public:
//    AnimatedSubMesh(const std::vector<AnimatedVertex> &vertices, const std::vector<uint> indices,
//                  const std::string &diffuseMapPath, const std::string &specularMapPath, const Material &material);
//    ~AnimatedSubMesh();
//
//    const std::vector<AnimatedVertex> &GetVertices() const;
//    const std::vector<uint> &GetIndices() const;
//    const VertexBuffer *GetVertexBuffer() const;
//    const IndexBuffer *GetIndexBuffer() const;
//    const Texture2D *GetDiffuseMap() const;
//    const Texture2D *GetSpecularMap() const;
//    const Material &GetMaterial() const;
//
//private:
//    std::vector<AnimatedVertex> mVertices;
//    std::vector<uint> mIndices;
//    VertexBuffer *mVertexBuffer;
//    IndexBuffer *mIndexBuffer;
//    Texture2D *mDiffuseMap, *mSpecularMap;
//    Material mMaterial;
//};
//
//class AnimatedMesh {
//public:
//    AnimatedMesh(const std::string &filename);
//    ~AnimatedMesh();
//
//    const std::vector<AnimatedSubMesh*> &GetSubMeshes() const;
//
//private:
//    std::vector<AnimatedSubMesh*> mSubMeshes;
//};

}