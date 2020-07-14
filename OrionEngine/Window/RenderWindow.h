#pragma once
#include "../Core/Common.h"
#include "Event.h"
#include "glm/glm.hpp"
#include <string>

namespace oe {

class RenderWindow {
public:
    RenderWindow(const std::string &title, const glm::ivec2 &size, bool fullscreen, uint depthBits, uint stencilBits, uint msaaSamplesCount);
    ~RenderWindow();

    bool ProcessEvent(Event &e);
    void SwapBuffers();
    void SetMousePos(const glm::ivec2 &pos);
    void SetMouseVisible(bool visible);
    void SetVSync(bool state);
    bool GetVSync() const;
    bool IsMSAAEnabled() const;
    glm::ivec2 GetPos() const;
    glm::ivec2 GetSize() const;
    glm::ivec2 GetCenter() const;
    glm::ivec2 GetMousePos() const;
    glm::ivec2 GetMouseDelta() const;
    float GetAspectRatio() const;
    bool IsKeyDown(KeyCode key) const;
    bool IsMouseButtonDown(MouseButton button) const;
    bool IsMouseVisible() const;

private:
    void *mWindow;
    void *mContext;
    bool mIsMsaaEnabled;
};

}