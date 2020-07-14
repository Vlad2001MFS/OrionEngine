#pragma once
#include "glm/glm.hpp"

namespace oe {

struct IntRect {
    IntRect();
    IntRect(const int x, const int y, const int w, const int h);
    IntRect(const glm::ivec2 &pos, const glm::ivec2 &size);

    friend bool operator==(const IntRect &lhs, const IntRect &rhs);
    friend bool operator!=(const IntRect &lhs, const IntRect &rhs);

    bool Intersect(const IntRect &rect);

    glm::ivec2 pos, size;
};

}

