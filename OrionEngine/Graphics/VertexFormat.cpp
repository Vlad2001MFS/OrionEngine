#include "VertexFormat.h"
#include "../Core/Debug.h"
#include "glew.h"

namespace oe {

constexpr uint gVertexAttribSize[] = {
    1,
    2,
    3,
    4,
    1,
    2,
    3,
    4,
};

constexpr GLenum gVertexAttribType[] = {
    GL_INT,
    GL_INT,
    GL_INT,
    GL_INT,
    GL_FLOAT,
    GL_FLOAT,
    GL_FLOAT,
    GL_FLOAT,
};
	
VertexAttrib::VertexAttrib() 
    : slot(0), index(0), offset(0), type(AttribType::Int), normalized(false), slotInstanceDivisor(0) { }

VertexAttrib::VertexAttrib(uint slot, uint index, uint offset, AttribType type, bool normalized, uint slotInstanceDivisor)
    : slot(slot), index(index), offset(offset), type(type), normalized(normalized), slotInstanceDivisor(slotInstanceDivisor) { }

VertexFormat::VertexFormat(const std::vector<VertexAttrib>& attribs) : mVao(0), mAttribs(attribs) {
    if (attribs.empty()) {
        OE_LOG_ERROR("Can't define vertex format without vertex attribs");
    }
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);
    for (const auto &attrib : attribs) {
        glEnableVertexAttribArray(attrib.index);
        if (attrib.type >= AttribType::Int && attrib.type <= AttribType::Int4) {
            glVertexAttribIFormat(attrib.index, gVertexAttribSize[static_cast<uint>(attrib.type)], gVertexAttribType[static_cast<uint>(attrib.type)], 
                                  attrib.offset);
        }
        else {
            glVertexAttribFormat(attrib.index, gVertexAttribSize[static_cast<uint>(attrib.type)], gVertexAttribType[static_cast<uint>(attrib.type)],
                                 attrib.normalized, attrib.offset);
        }
        glVertexAttribBinding(attrib.index, attrib.slot);
        glVertexBindingDivisor(attrib.slot, attrib.slotInstanceDivisor);
    }
}

VertexFormat::~VertexFormat() {
    glDeleteVertexArrays(1, &mVao);
}

uint VertexFormat::GetHandle() const {
    return mVao;
}

const std::vector<VertexAttrib> & VertexFormat::GetAttribs() const {
    return mAttribs;
}


}