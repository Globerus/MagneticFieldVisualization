#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "buffer.h"
#include "indexAttributes.h"

class IndexBuffer : public Buffer
{
public:
	IndexBuffer (PType pType, unsigned int numPrimitives, size_t indexSize, bool createStorage = true);
	IndexBuffer (PType pType, unsigned int numPrimitives);
	~IndexBuffer () {};

	int GetPrimitiveType () const;
	unsigned int GetNumPrimitives () const;
	unsigned int GetNumActivePrimitives () const;

	void SetNumActivePrimitives (unsigned int numActivePrimitives);

	template <typename T>
	void SetIndexData (size_t stride, T const& value);
	template <typename T>
	std::vector<T> GetIndexData (size_t stride);

	bool IsIndexed () const;

protected:
	PType m_PrimitiveType;
	unsigned int m_NumPrimitives;
	unsigned int m_NumActivePrimitives;
};

template <typename T>
void IndexBuffer::SetIndexData (size_t stride, T const& value)
{	
		T* target = reinterpret_cast<T*> (m_Data + stride);
		*target = value;
}

template <typename T>
std::vector<T> IndexBuffer::GetIndexData (size_t stride)
{
	int numIndices = GetNumElements ();

	std::vector<T> vector;

	for (int i = 0; i < numIndices; i++)
	{
		T* target = reinterpret_cast<T*> (m_Data + (i * stride));
		vector.push_back (*target);
	}

	return vector;
}
#endif