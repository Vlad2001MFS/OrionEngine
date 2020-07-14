#include "FirstPersonCamera.h"
#include "glm/ext.hpp"

namespace oe {

FirstPersonCamera::FirstPersonCamera(float fov, float aspectRatio, const glm::vec3 & pos, const glm::vec3 & angles)
    : mFov(fov), mAspectRatio(aspectRatio), mPos(pos), mOldPos(pos), mAngles(angles), mOldAngles(angles), mNearPlane(0.01f), mFarPlane(1000.0f) { }

FirstPersonCamera::~FirstPersonCamera() { }

void FirstPersonCamera::Translate(const glm::vec3 & offset) {
    glm::vec3 newPos = mPos + glm::vec3(glm::transpose(glm::eulerAngleXYZ(mAngles.x, mAngles.y, mAngles.z))*glm::vec4(offset, 1));
    mPos = glm::lerp(mOldPos, newPos, 0.1f);
    mOldPos = mPos;
}

void FirstPersonCamera::Rotate(const glm::vec3 & angles) {
    glm::vec3 newAngles = mAngles + angles;
    mAngles = glm::lerp(mOldAngles, newAngles, 0.1f);
    mOldAngles = mAngles;
}

void FirstPersonCamera::SetFov(float fov) {
    mFov = fov;
}

void FirstPersonCamera::SetAspectRatio(float ratio) {
    mAspectRatio = ratio;
}

void FirstPersonCamera::SetNearPlane(float nearPlane) {
    mNearPlane = nearPlane;
}

void FirstPersonCamera::SetFarPlane(float farPlane) {
    mFarPlane = farPlane;
}

void FirstPersonCamera::SetPosition(const glm::vec3 & pos) {
    mPos = pos;
}

void FirstPersonCamera::SetAngles(const glm::vec3 & angles) {
    mAngles = angles;
}

float FirstPersonCamera::GetFov() const {
    return mFov;
}

float FirstPersonCamera::GetAspectRatio() const {
    return mAspectRatio;
}

float FirstPersonCamera::GetNearPlane() const {
    return mNearPlane;
}

float FirstPersonCamera::GetFarPlane() const {
    return mFarPlane;
}

const glm::vec3 & FirstPersonCamera::GetPosition() const {
    return mPos;
}

const glm::vec3 & FirstPersonCamera::GetAngles() const {
    return mAngles;
}

glm::mat4 FirstPersonCamera::GetViewProjMat() const {
    return glm::perspectiveLH(mFov, mAspectRatio, mNearPlane, mFarPlane)*glm::eulerAngleXYZ(mAngles.x, mAngles.y, mAngles.z)*glm::translate(-mPos);
}

}