#include "VertexBuffer.h"
#include "glew.h"
#include <memory.h>

namespace oe {
	
VertexBuffer::VertexBuffer(const void * data, uint size, bool isDynamic) 
    : mBuffer(0), mSize(size), mIsDynamic(isDynamic) {
    glGenBuffers(1, &mBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() { 
    glDeleteBuffers(1, &mBuffer);
}

void VertexBuffer::Update(const void * data, uint offset, uint size) {
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::SetData(const void * data) { 
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
    memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), data, mSize);
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

uint VertexBuffer::GetHandle() const {
    return mBuffer;
}

uint VertexBuffer::GetSize() const {
    return mSize;
}

bool VertexBuffer::IsDynamic() const {
    return mIsDynamic;
}

}