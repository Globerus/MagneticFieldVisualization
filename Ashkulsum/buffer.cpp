#include "stdafx.h"
#include "buffer.h"

/*Buffer::~Buffer () 
{

}
*/
Buffer::Buffer (unsigned int numElements, size_t elementSize, bool createStorage)
	:	Resource (numElements, elementSize, createStorage)
{
	m_Type = DP_BUFFER;
}
