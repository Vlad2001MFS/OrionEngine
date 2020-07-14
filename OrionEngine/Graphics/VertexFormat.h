#pragma once
#include "../Core/Common.h"
#include <vector>

namespace oe {

enum class AttribType {
    Int,
    Int2,
    Int3,
    Int4,
    Float,
    Float2,
    Float3,
    Float4
};

struct VertexAttrib {
    VertexAttrib();
    VertexAttrib(uint slot, uint index, uint offset, AttribType type, bool normalized, uint slotInstanceDivisor);

    uint slot, index, offset;
    AttribType type;
    bool normalized;
    uint slotInstanceDivisor;
};

class VertexFormat {
public:
    VertexFormat(const std::vector<VertexAttrib> &attribs);
	~VertexFormat();

    uint GetHandle() const;
    const std::vector<VertexAttrib> &GetAttribs() const;

private:
    uint mVao;
    std::vector<VertexAttrib> mAttribs;
};

}