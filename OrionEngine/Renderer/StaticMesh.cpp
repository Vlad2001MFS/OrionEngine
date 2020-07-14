#include "StaticMesh.h"
#include "../Core/Common.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

namespace oe {

StaticVertex::StaticVertex() : position(0, 0, 0), normal(0, 0, 0), texCoord(0, 0) { }

StaticVertex::StaticVertex(const glm::vec3 & pos, const glm::vec3 & normal, const glm::vec2 & texCoord) : position(pos), normal(normal), texCoord(texCoord) { }

StaticSubMesh::StaticSubMesh(const std::vector<StaticVertex>& vertices, const std::vector<uint> indices,
                             const std::string & diffuseMapPath, const std::string & specularMapPath, const Material & material)
    : mVertices(vertices), mIndices(indices), mVertexBuffer(nullptr), mIndexBuffer(nullptr), mDiffuseMap(nullptr), mSpecularMap(nullptr), mMaterial(material) {
    mVertexBuffer = new VertexBuffer(vertices.data(), sizeof(StaticVertex)*vertices.size(), false);
    mIndexBuffer = new IndexBuffer(indices.data(), sizeof(uint)*indices.size(), false);
    if (!diffuseMapPath.empty()) {
        mDiffuseMap = new Texture2D(diffuseMapPath);
    }
    if (!specularMapPath.empty()) {
        mSpecularMap = new Texture2D(specularMapPath);
    }
}

StaticSubMesh::~StaticSubMesh() {
    OE_SAFE_DELETE(mSpecularMap);
    OE_SAFE_DELETE(mDiffuseMap);
    OE_SAFE_DELETE(mIndexBuffer);
    OE_SAFE_DELETE(mVertexBuffer);
}

const std::vector<StaticVertex>& StaticSubMesh::GetVertices() const {
    return mVertices;
}

const std::vector<uint>& StaticSubMesh::GetIndices() const {
    return mIndices;
}

const VertexBuffer * StaticSubMesh::GetVertexBuffer() const {
    return mVertexBuffer;
}

const IndexBuffer * StaticSubMesh::GetIndexBuffer() const {
    return mIndexBuffer;
}

const Texture2D * StaticSubMesh::GetDiffuseMap() const {
    return mDiffuseMap;
}

const Texture2D * StaticSubMesh::GetSpecularMap() const {
    return mSpecularMap;
}

const Material & StaticSubMesh::GetMaterial() const {
    return mMaterial;
}

void ProcessNode(std::vector<StaticSubMesh*> &subMeshes, const aiScene * scene, const aiNode *node) {
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        std::vector<StaticVertex> meshVertices;
        std::vector<uint> meshIndices;
        std::string meshDiffuseMapPath, meshSpecularMapPath;

        meshVertices.resize(mesh->mNumVertices);
        for (int k = 0; k < mesh->mNumVertices; k++) {
            memcpy(&meshVertices[k].position, &mesh->mVertices[k], sizeof(aiVector3D));
            memcpy(&meshVertices[k].normal, &mesh->mNormals[k], sizeof(aiVector3D));
            memcpy(&meshVertices[k].texCoord, &mesh->mTextureCoords[0][k], sizeof(aiVector2D));
        }
        meshIndices.reserve(mesh->mNumFaces * 3);
        for (int k = 0; k < mesh->mNumFaces; k++) {
            aiFace &face = mesh->mFaces[k];
            meshIndices.push_back(face.mIndices[0]);
            meshIndices.push_back(face.mIndices[1]);
            meshIndices.push_back(face.mIndices[2]);
        }

        aiString diffusePath, specularPath;
        if (scene->mMaterials[mesh->mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE) != 0 &&
            scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &diffusePath) == AI_SUCCESS) {
            meshDiffuseMapPath = diffusePath.C_Str();
        }
        if (scene->mMaterials[mesh->mMaterialIndex]->GetTextureCount(aiTextureType_SPECULAR) != 0 &&
            scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_SPECULAR, 0, &specularPath) == AI_SUCCESS) {
            meshSpecularMapPath = specularPath.C_Str();
        }

        aiMaterialProperty *prop[8];
        memcpy(prop, scene->mMaterials[mesh->mMaterialIndex]->mProperties, sizeof(prop));

        glm::vec3 ambient(1, 1, 1), diffuse(1, 1, 1), specular(1, 1, 1);
        float specPower = 32;
        scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
        scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
        scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, specular);
        scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_SHININESS, specPower);

        StaticSubMesh *subMesh = new StaticSubMesh(meshVertices, meshIndices, meshDiffuseMapPath, meshSpecularMapPath, 
                                                   Material(ambient, diffuse, specular, specPower));
        subMeshes.push_back(subMesh);
    }
    for (int i = 0; i < node->mNumChildren; i++)
        ProcessNode(subMeshes, scene, node->mChildren[i]);
}

StaticMesh::StaticMesh(const std::string & filename) {
    Assimp::Importer imp;
    const aiScene *scene = imp.ReadFile(filename, aiProcess_FlipWindingOrder | aiProcess_GenSmoothNormals);
    ProcessNode(mSubMeshes, scene, scene->mRootNode);
}

StaticMesh::~StaticMesh() {
    for (auto &subMesh : mSubMeshes) {
        OE_SAFE_DELETE(subMesh);
    }
}

const std::vector<StaticSubMesh*>& StaticMesh::GetSubMeshes() const {
    return mSubMeshes;
}

}