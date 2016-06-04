#ifndef BUFFER_H
#define BUFFER_H

#include "resourceO.h"
#include <functional>
class Buffer : public Resource
{

protected:
	Buffer (unsigned int numElements, size_t elementSize, bool createStorage);
};

typedef std::function<void(std::shared_ptr<Buffer> const&)> BufferUpdater;
#endif