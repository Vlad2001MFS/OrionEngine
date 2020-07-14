#include "IntRect.h"

namespace oe {

IntRect::IntRect() : pos(0, 0), size(0, 0) { }

IntRect::IntRect(const int x, const int y, const int w, const int h) : pos(x, y), size(w, h) { }

IntRect::IntRect(const glm::ivec2 & pos, const glm::ivec2 & size) : pos(pos), size(size) { }

bool IntRect::Intersect(const IntRect & rect) {
    return ((this->pos.x + this->size.x) > rect.pos.x && (this->pos.x + this->size.x) < (rect.pos.x + rect.size.x)) &&
        (this->pos.y + this->size.y) > rect.pos.y && (this->pos.y + this->size.y) < (rect.pos.y + rect.size.y);
}

bool operator==(const IntRect & lhs, const IntRect & rhs) {
    return lhs.pos == rhs.pos && lhs.size == rhs.size;
}

bool operator!=(const IntRect & lhs, const IntRect & rhs) {
    return lhs.pos != rhs.pos && lhs.size != rhs.size;
}

}