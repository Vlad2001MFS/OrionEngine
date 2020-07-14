#pragma once
#include "glm/glm.hpp"

namespace oe {

struct FloatRect {
    FloatRect();
    FloatRect(const float x, const float y, const float w, const float h);
    FloatRect(const glm::vec2 &pos, const glm::vec2 &size);

    friend bool operator==(const FloatRect &lhs, const FloatRect &rhs);
    friend bool operator!=(const FloatRect &lhs, const FloatRect &rhs);

    bool Intersect(const FloatRect &rect);

    glm::vec2 pos, size;
};

}

