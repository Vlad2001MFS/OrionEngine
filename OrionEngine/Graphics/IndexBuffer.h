#pragma once
#include "../Core/Common.h"

namespace oe {

class IndexBuffer {
public:
	IndexBuffer(const void *data, uint size, bool isDynamic);
	~IndexBuffer();

    void Update(const void *data, uint offset, uint size);

    void SetData(const void *data);

    uint GetHandle() const;
    uint GetSize() const;
    bool IsDynamic() const;

private:
    uint mBuffer;
    uint mSize;
    bool mIsDynamic;
};

}