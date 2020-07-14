#pragma once
#include "glm/glm.hpp"

namespace oe {

class FirstPersonCamera {
public:
    FirstPersonCamera(float fov, float aspectRatio, const glm::vec3 &pos, const glm::vec3 &angles);
    ~FirstPersonCamera();

    void Translate(const glm::vec3 &offset);
    void Rotate(const glm::vec3 &angles);

    void SetFov(float fov);
    void SetAspectRatio(float ratio);
    void SetNearPlane(float nearPlane);
    void SetFarPlane(float farPlane);
    void SetPosition(const glm::vec3 &pos);
    void SetAngles(const glm::vec3 &angles);

    float GetFov() const;
    float GetAspectRatio() const;
    float GetNearPlane() const;
    float GetFarPlane() const;
    const glm::vec3 &GetPosition() const;
    const glm::vec3 &GetAngles() const;
    glm::mat4 GetViewProjMat() const;

private:
    float mFov, mAspectRatio, mNearPlane, mFarPlane;
    glm::vec3 mPos, mOldPos, mAngles, mOldAngles;
};

}