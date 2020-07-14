#include "ConstantBuffer.h"
#include "glew.h"
#include <memory.h>

namespace oe {
	
ConstantBuffer::ConstantBuffer(const void * data, uint size, bool isDynamic) : mBuffer(0), mSize(size), mIsDynamic(isDynamic) {
    glGenBuffers(1, &mBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, mBuffer);
    glBufferData(GL_UNIFORM_BUFFER, size, data, isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

ConstantBuffer::~ConstantBuffer() {
    glDeleteBuffers(1, &mBuffer);
}

void ConstantBuffer::Update(const void * data, uint offset, uint size) {
    glBindBuffer(GL_UNIFORM_BUFFER, mBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}

void ConstantBuffer::SetData(const void * data) {
    glBindBuffer(GL_UNIFORM_BUFFER, mBuffer);
    glBufferData(GL_UNIFORM_BUFFER, mSize, data, mIsDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    //memcpy(glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY), data, mSize);
    //glUnmapBuffer(GL_UNIFORM_BUFFER);

}

uint ConstantBuffer::GetHandle() const {
    return mBuffer;
}

uint ConstantBuffer::GetSize() const {
    return mSize;
}

bool ConstantBuffer::IsDynamic() const {
    return mIsDynamic;
}

}