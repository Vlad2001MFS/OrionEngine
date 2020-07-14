#include "RenderWindow.h"
#include "../Core/BuildConfig.h"
#include "../Core/Debug.h"
#include "SDL2/SDL.h"

namespace oe {

static const int gKeyCodes[] =
{
    SDL_SCANCODE_UNKNOWN,

    SDL_SCANCODE_A, SDL_SCANCODE_B, SDL_SCANCODE_C, SDL_SCANCODE_D, SDL_SCANCODE_E,
    SDL_SCANCODE_F, SDL_SCANCODE_G, SDL_SCANCODE_H, SDL_SCANCODE_I, SDL_SCANCODE_J,
    SDL_SCANCODE_K, SDL_SCANCODE_L, SDL_SCANCODE_M, SDL_SCANCODE_N, SDL_SCANCODE_O,
    SDL_SCANCODE_P, SDL_SCANCODE_Q, SDL_SCANCODE_R, SDL_SCANCODE_S, SDL_SCANCODE_T,
    SDL_SCANCODE_U, SDL_SCANCODE_V, SDL_SCANCODE_W, SDL_SCANCODE_X, SDL_SCANCODE_Y,
    SDL_SCANCODE_Z,

    SDL_SCANCODE_0, SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3, SDL_SCANCODE_4,
    SDL_SCANCODE_5, SDL_SCANCODE_6, SDL_SCANCODE_7, SDL_SCANCODE_8, SDL_SCANCODE_9,

    SDL_SCANCODE_RETURN, SDL_SCANCODE_ESCAPE, SDL_SCANCODE_BACKSPACE,
    SDL_SCANCODE_TAB, SDL_SCANCODE_SPACE,

    SDL_SCANCODE_F1, SDL_SCANCODE_F2, SDL_SCANCODE_F3, SDL_SCANCODE_F4, SDL_SCANCODE_F5,
    SDL_SCANCODE_F6, SDL_SCANCODE_F7, SDL_SCANCODE_F8, SDL_SCANCODE_F9, SDL_SCANCODE_F10,
    SDL_SCANCODE_F11, SDL_SCANCODE_F12,

    SDL_SCANCODE_PAUSE, SDL_SCANCODE_INSERT, SDL_SCANCODE_HOME, SDL_SCANCODE_PAGEUP, SDL_SCANCODE_PAGEDOWN, 
    SDL_SCANCODE_DELETE, SDL_SCANCODE_END, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN,

    SDL_SCANCODE_KP_0, SDL_SCANCODE_KP_1, SDL_SCANCODE_KP_2, SDL_SCANCODE_KP_3, SDL_SCANCODE_KP_4, 
    SDL_SCANCODE_KP_5, SDL_SCANCODE_KP_6, SDL_SCANCODE_KP_7, SDL_SCANCODE_KP_8, SDL_SCANCODE_KP_9,

    SDL_SCANCODE_LCTRL, SDL_SCANCODE_RCTRL, SDL_SCANCODE_LSHIFT, SDL_SCANCODE_RSHIFT, 
    SDL_SCANCODE_LALT, SDL_SCANCODE_RALT, SDL_SCANCODE_LGUI, SDL_SCANCODE_RGUI,
};

constexpr uint gMouseButtons[] = {
    SDL_BUTTON_LEFT,
    SDL_BUTTON_RIGHT,
    SDL_BUTTON_MIDDLE,
    SDL_BUTTON_X1,
    SDL_BUTTON_X2
};

KeyCode GetKeyCodeFromSDLScanCode(const sint key) {
    switch (key) {
        case SDL_SCANCODE_A:
            return KeyCode::A;
            break;
        case SDL_SCANCODE_B:
            return KeyCode::B;
            break;
        case SDL_SCANCODE_C:
            return KeyCode::C;
            break;
        case SDL_SCANCODE_D:
            return KeyCode::D;
            break;
        case SDL_SCANCODE_E:
            return KeyCode::E;
            break;
        case SDL_SCANCODE_F:
            return KeyCode::F;
            break;
        case SDL_SCANCODE_G:
            return KeyCode::G;
            break;
        case SDL_SCANCODE_H:
            return KeyCode::H;
            break;
        case SDL_SCANCODE_I:
            return KeyCode::I;
            break;
        case SDL_SCANCODE_J:
            return KeyCode::J;
            break;
        case SDL_SCANCODE_K:
            return KeyCode::K;
            break;
        case SDL_SCANCODE_L:
            return KeyCode::L;
            break;
        case SDL_SCANCODE_M:
            return KeyCode::M;
            break;
        case SDL_SCANCODE_N:
            return KeyCode::N;
            break;
        case SDL_SCANCODE_O:
            return KeyCode::O;
            break;
        case SDL_SCANCODE_P:
            return KeyCode::P;
            break;
        case SDL_SCANCODE_Q:
            return KeyCode::Q;
            break;
        case SDL_SCANCODE_R:
            return KeyCode::R;
            break;
        case SDL_SCANCODE_S:
            return KeyCode::S;
            break;
        case SDL_SCANCODE_T:
            return KeyCode::T;
            break;
        case SDL_SCANCODE_U:
            return KeyCode::U;
            break;
        case SDL_SCANCODE_V:
            return KeyCode::V;
            break;
        case SDL_SCANCODE_W:
            return KeyCode::W;
            break;
        case SDL_SCANCODE_X:
            return KeyCode::X;
            break;
        case SDL_SCANCODE_Y:
            return KeyCode::Y;
            break;
        case SDL_SCANCODE_Z:
            return KeyCode::Z;
            break;
        case SDL_SCANCODE_0:
            return KeyCode::Num0;
            break;
        case SDL_SCANCODE_1:
            return KeyCode::Num1;
            break;
        case SDL_SCANCODE_2:
            return KeyCode::Num2;
            break;
        case SDL_SCANCODE_3:
            return KeyCode::Num3;
            break;
        case SDL_SCANCODE_4:
            return KeyCode::Num4;
            break;
        case SDL_SCANCODE_5:
            return KeyCode::Num5;
            break;
        case SDL_SCANCODE_6:
            return KeyCode::Num6;
            break;
        case SDL_SCANCODE_7:
            return KeyCode::Num7;
            break;
        case SDL_SCANCODE_8:
            return KeyCode::Num8;
            break;
        case SDL_SCANCODE_9:
            return KeyCode::Num9;
            break;
        case SDL_SCANCODE_RETURN:
            return KeyCode::Return;
            break;
        case SDL_SCANCODE_ESCAPE:
            return KeyCode::Escape;
            break;
        case SDL_SCANCODE_BACKSPACE:
            return KeyCode::BackSpace;
            break;
        case SDL_SCANCODE_TAB:
            return KeyCode::Tab;
            break;
        case SDL_SCANCODE_SPACE:
            return KeyCode::Space;
            break;
        case SDL_SCANCODE_F1:
            return KeyCode::F1;
            break;
        case SDL_SCANCODE_F2:
            return KeyCode::F2;
            break;
        case SDL_SCANCODE_F3:
            return KeyCode::F3;
            break;
        case SDL_SCANCODE_F4:
            return KeyCode::F4;
            break;
        case SDL_SCANCODE_F5:
            return KeyCode::F5;
            break;
        case SDL_SCANCODE_F6:
            return KeyCode::F6;
            break;
        case SDL_SCANCODE_F7:
            return KeyCode::F7;
            break;
        case SDL_SCANCODE_F8:
            return KeyCode::F8;
            break;
        case SDL_SCANCODE_F9:
            return KeyCode::F9;
            break;
        case SDL_SCANCODE_F10:
            return KeyCode::F10;
            break;
        case SDL_SCANCODE_F11:
            return KeyCode::F11;
            break;
        case SDL_SCANCODE_F12:
            return KeyCode::F12;
            break;
        case SDL_SCANCODE_PAUSE:
            return KeyCode::Pause;
            break;
        case SDL_SCANCODE_INSERT:
            return KeyCode::Insert;
            break;
        case SDL_SCANCODE_HOME:
            return KeyCode::Home;
            break;
        case SDL_SCANCODE_PAGEUP:
            return KeyCode::PageUp;
            break;
        case SDL_SCANCODE_PAGEDOWN:
            return KeyCode::PageDown;
            break;
        case SDL_SCANCODE_DELETE:
            return KeyCode::Delete;
            break;
        case SDL_SCANCODE_END:
            return KeyCode::End;
            break;
        case SDL_SCANCODE_LEFT:
            return KeyCode::Left;
            break;
        case SDL_SCANCODE_RIGHT:
            return KeyCode::Right;
            break;
        case SDL_SCANCODE_UP:
            return KeyCode::Up;
            break;
        case SDL_SCANCODE_DOWN:
            return KeyCode::Down;
            break;
        case SDL_SCANCODE_KP_0:
            return KeyCode::Numpad0;
            break;
        case SDL_SCANCODE_KP_1:
            return KeyCode::Numpad1;
            break;
        case SDL_SCANCODE_KP_2:
            return KeyCode::Numpad2;
            break;
        case SDL_SCANCODE_KP_3:
            return KeyCode::Numpad3;
            break;
        case SDL_SCANCODE_KP_4:
            return KeyCode::Numpad4;
            break;
        case SDL_SCANCODE_KP_5:
            return KeyCode::Numpad5;
            break;
        case SDL_SCANCODE_KP_6:
            return KeyCode::Numpad6;
            break;
        case SDL_SCANCODE_KP_7:
            return KeyCode::Numpad7;
            break;
        case SDL_SCANCODE_KP_8:
            return KeyCode::Numpad8;
            break;
        case SDL_SCANCODE_KP_9:
            return KeyCode::Numpad9;
            break;
        case SDL_SCANCODE_LCTRL:
            return KeyCode::LControl;
            break;
        case SDL_SCANCODE_LSHIFT:
            return KeyCode::LShift;
            break;
        case SDL_SCANCODE_LALT:
            return KeyCode::LAlt;
            break;
        case SDL_SCANCODE_LGUI:
            return KeyCode::LSystem;
            break;
        case SDL_SCANCODE_RCTRL:
            return KeyCode::RControl;
            break;
        case SDL_SCANCODE_RSHIFT:
            return KeyCode::RShift;
            break;
        case SDL_SCANCODE_RALT:
            return KeyCode::RAlt;
            break;
        case SDL_SCANCODE_RGUI:
            return KeyCode::RSystem;
            break;
        default:
            return KeyCode::Unknown;
            break;
    }
}

RenderWindow::RenderWindow(const std::string & title, const glm::ivec2 & size, bool fullscreen, uint depthBits, uint stencilBits, uint msaaSamplesCount)
    : mWindow(nullptr), mContext(nullptr), mIsMsaaEnabled(msaaSamplesCount > 0) {
    OE_LOG_INFO("Initializing RenderWindow...");
    if (SDL_Init(SDL_INIT_VIDEO)) {
        OE_LOG_ERROR("Failed to initialize SDL. Error: %s", SDL_GetError());
        OE_LOG_INFO("Initializing RenderWindow... FAILED");
    }
#ifdef OE_DEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depthBits);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, stencilBits);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, msaaSamplesCount > 0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaaSamplesCount);
    mWindow = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!mWindow) {
        OE_LOG_ERROR("Failed to create window. Error: %s", SDL_GetError());
        OE_LOG_INFO("Initializing RenderWindow... FAILED");
    }
    if (SDL_CaptureMouse(SDL_TRUE) != 0) {

        OE_LOG_ERROR("Failed to capture mouse. Error: %s", SDL_GetError());
        OE_LOG_INFO("Initializing RenderWindow... FAILED");
    }
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    SetMousePos(GetCenter());
    //SDL_SetWindowGrab(static_cast<SDL_Window*>(mWindow), SDL_TRUE);
    mContext = SDL_GL_CreateContext(static_cast<SDL_Window*>(mWindow));
    if (!mContext) {
        OE_LOG_ERROR("Failed to create OpenGL Context. Error: %s", SDL_GetError());
        OE_LOG_INFO("Initializing RenderWindow... FAILED");
    }
    OE_LOG_INFO("Initializing RenderWindow... OK");
}

RenderWindow::~RenderWindow() { 
    OE_LOG_INFO("Shutdowning RenderWindow...");
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(static_cast<SDL_Window*>(mWindow));
    SDL_Quit();
    OE_LOG_INFO("Shutdowning RenderWindow... OK");
}

bool RenderWindow::ProcessEvent(Event & e) {
    SDL_Event sdlEvent;
    if (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
            {
                e.type = EventType::Close;
                break;
            }
            case SDL_WINDOWEVENT:
            {
                switch (sdlEvent.window.type) {
                    case SDL_WINDOWEVENT_RESIZED:
                    {
                        e.type = EventType::Resize;
                        e.resize.width = sdlEvent.window.data1;
                        e.resize.height = sdlEvent.window.data2;
                        break;
                    }
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                    {
                        e.type = EventType::LostFocus;
                        break;
                    }
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                    {
                        e.type = EventType::GetFocus;
                        break;
                    }
                }
                break;
            }
            case SDL_KEYDOWN:
            {
                e.type = EventType::KeyDown;
                e.key.code = GetKeyCodeFromSDLScanCode(sdlEvent.key.keysym.scancode);
                e.key.alt = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LALT] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RALT];
                e.key.control = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LCTRL] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RCTRL];
                e.key.shift = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LSHIFT] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RSHIFT];
                e.key.system = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LGUI] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RGUI];
                break;
            }
            case SDL_KEYUP:
            {
                e.type = EventType::KeyUp;
                e.key.code = GetKeyCodeFromSDLScanCode(sdlEvent.key.keysym.scancode);
                e.key.alt = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LALT] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RALT];
                e.key.control = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LCTRL] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RCTRL];
                e.key.shift = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LSHIFT] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RSHIFT];
                e.key.system = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LGUI] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RGUI];
                break;
            }
            case SDL_MOUSEWHEEL:
            {
                e.type = EventType::MouseWheel;
                e.mouseWheel.direction = sdlEvent.wheel.direction;
                e.mouseWheel.x = sdlEvent.wheel.x;
                e.mouseWheel.y = sdlEvent.wheel.y;
                unsigned int mouseState = SDL_GetMouseState(nullptr, nullptr);
                e.mouseWheel.control = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LCTRL] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RCTRL];
                e.mouseWheel.leftButton = (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) == SDL_BUTTON(SDL_BUTTON_LEFT);
                e.mouseWheel.middleButton = (mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE)) == SDL_BUTTON(SDL_BUTTON_MIDDLE);
                e.mouseWheel.rightButton = (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)) == SDL_BUTTON(SDL_BUTTON_RIGHT);
                e.mouseWheel.shift = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LSHIFT] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RSHIFT];
                e.mouseWheel.xButton1 = (mouseState & SDL_BUTTON(SDL_BUTTON_X1)) == SDL_BUTTON(SDL_BUTTON_X1);
                e.mouseWheel.xButton2 = (mouseState & SDL_BUTTON(SDL_BUTTON_X2)) == SDL_BUTTON(SDL_BUTTON_X2);
                break;
            }
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
            {
                if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
                    e.type = EventType::MouseButtonDown;
                }
                else if (sdlEvent.type == SDL_MOUSEBUTTONUP) {
                    e.type = EventType::MouseButtonUp;
                }
                switch (sdlEvent.button.button) {
                    case SDL_BUTTON_LEFT:
                    {
                        e.mouseButton.btn = MouseButton::Left;
                        break;
                    }
                    case SDL_BUTTON_MIDDLE:
                    {
                        e.mouseButton.btn = MouseButton::Middle;
                        break;
                    }
                    case SDL_BUTTON_RIGHT:
                    {
                        e.mouseButton.btn = MouseButton::Right;
                        break;
                    }
                    case SDL_BUTTON_X1:
                    {
                        e.mouseButton.btn = MouseButton::XButton1;
                        break;
                    }
                    case SDL_BUTTON_X2:
                    {
                        e.mouseButton.btn = MouseButton::XButton2;
                        break;
                    }
                }
                e.mouseButton.x = sdlEvent.button.x;
                e.mouseButton.y = sdlEvent.button.y;
                break;
            }
            case SDL_MOUSEMOTION:
            {
                static int lastX = 0, lastY = 0;
                static bool first = true;
                if (first) {
                    first = false;
                    lastX = sdlEvent.motion.x;
                    lastY = sdlEvent.motion.y;
                }
                e.type = EventType::MouseMove;
                e.mouseMove.x = sdlEvent.motion.x;
                e.mouseMove.y = sdlEvent.motion.y;
                e.mouseMove.deltaX = lastX - sdlEvent.motion.x;//sdlEvent.motion.xrel;
                e.mouseMove.deltaY = lastY - sdlEvent.motion.y;//sdlEvent.motion.yrel;
                lastX = sdlEvent.motion.x;
                lastY = sdlEvent.motion.y;
                break;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

void RenderWindow::SwapBuffers() { 
    SDL_GL_SwapWindow(static_cast<SDL_Window*>(mWindow));
}

void RenderWindow::SetMousePos(const glm::ivec2 & pos) {
    SDL_WarpMouseInWindow(static_cast<SDL_Window*>(mWindow), pos.x, pos.y);
}

void RenderWindow::SetMouseVisible(bool visible) {
    SDL_ShowCursor(visible);
}

void RenderWindow::SetVSync(bool state) { 
    SDL_GL_SetSwapInterval(state);
}

bool RenderWindow::GetVSync() const {
    return SDL_GL_GetSwapInterval();
}

bool RenderWindow::IsMSAAEnabled() const {
    return mIsMsaaEnabled;
}

glm::ivec2 RenderWindow::GetPos() const {
    glm::ivec2 pos;
    SDL_GetWindowPosition(static_cast<SDL_Window*>(mWindow), &pos.x, &pos.y);
    return pos;
}

glm::ivec2 RenderWindow::GetSize() const {
    glm::ivec2 size;
    SDL_GetWindowSize(static_cast<SDL_Window*>(mWindow), &size.x, &size.y);
    return size;
}

glm::ivec2 RenderWindow::GetCenter() const {
    return GetSize()/2;
}

glm::ivec2 RenderWindow::GetMousePos() const {
    glm::ivec2 pos;
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}

glm::ivec2 RenderWindow::GetMouseDelta() const {
    return GetCenter() - GetMousePos();
    //glm::ivec2 pos;
    //SDL_GetRelativeMouseState(&pos.x, &pos.y);
    //return pos;
}

float RenderWindow::GetAspectRatio() const {
    return static_cast<float>(GetSize().x) / static_cast<float>(GetSize().y);
}

bool RenderWindow::IsKeyDown(KeyCode key) const {
    return SDL_GetKeyboardState(nullptr)[gKeyCodes[static_cast<uint>(key)]];
}

bool RenderWindow::IsMouseButtonDown(MouseButton button) const {
    return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(gMouseButtons[static_cast<uint>(button)])) == SDL_BUTTON(gMouseButtons[static_cast<uint>(button)]);
}

bool RenderWindow::IsMouseVisible() const {
    return SDL_ShowCursor(-1);
}

}