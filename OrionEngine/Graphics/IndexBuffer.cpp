#include "IndexBuffer.h"
#include "glew.h"
#include <memory.h>

namespace oe {
	
IndexBuffer::IndexBuffer(const void * data, uint size, bool isDynamic) : mBuffer(0), mSize(size), mIsDynamic(isDynamic) {
    glGenBuffers(1, &mBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &mBuffer);
}

void IndexBuffer::Update(const void * data, uint offset, uint size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

void IndexBuffer::SetData(const void * data) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
    memcpy(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY), data, mSize);
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

uint IndexBuffer::GetHandle() const {
    return mBuffer;
}

uint IndexBuffer::GetSize() const {
    return mSize;
}

bool IndexBuffer::IsDynamic() const {
    return mIsDynamic;
}

}