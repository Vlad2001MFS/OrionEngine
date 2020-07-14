#include "FloatRect.h"

namespace oe {

FloatRect::FloatRect() : pos(0, 0), size(0, 0) { }

FloatRect::FloatRect(const float x, const float y, const float w, const float h) : pos(x, y), size(w, h) { }

FloatRect::FloatRect(const glm::vec2 & pos, const glm::vec2 & size) : pos(pos), size(size) { }

bool FloatRect::Intersect(const FloatRect & rect) {
    return ((this->pos.x + this->size.x) > rect.pos.x && (this->pos.x + this->size.x) < (rect.pos.x + rect.size.x)) &&
        (this->pos.y + this->size.y) > rect.pos.y && (this->pos.y + this->size.y) < (rect.pos.y + rect.size.y);
}

bool operator==(const FloatRect & lhs, const FloatRect & rhs) {
    return lhs.pos == rhs.pos && lhs.size == rhs.size;
}

bool operator!=(const FloatRect & lhs, const FloatRect & rhs) {
    return lhs.pos != rhs.pos && lhs.size != rhs.size;
}

}
