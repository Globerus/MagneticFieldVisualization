#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "include.h"
#include "buffer.h"
#include "glm\glm.hpp"
#include "vertexAttributes.h"
#include <set>

class VertexBuffer : public Buffer
{
public:
	VertexBuffer (VertexAttributes const& vAttrib, unsigned int numVertices, bool createStorage = true);
	~VertexBuffer () {};

	VertexAttributes const& GetVertexAttrib () const;
	
	char* GetAttribData (VAType vaType, int counter, std::set<ContainerType> setTypes);
	/*template <typename T>
	void SetVertexData (size_t stride, size_t offset, T const& value);
	template <typename T>
	std::vector<T> GetVertexData (VAType vaType);
	*/
protected:
	VertexAttributes m_VertexAttributes;
};
/*
template <typename T>
void VertexBuffer::SetVertexData (size_t stride, size_t offset, T const& value)
{
		
		T* target = reinterpret_cast<T*> (m_Data + stride + offset);
		*target = value;
}

template <typename T>
std::vector<T> VertexBuffer::GetVertexData (VAType vaType)
{
	int numVertices = GetNumElements ();
	VertexAttributes vAttrib = GetVertexAttrib ();
	size_t vSize = vAttrib.GetVertexSize ();
	size_t vOffset = vAttrib.GetAttributeOffset (vaType);
	
	std::vector<T> vector;

	for (int i = 0; i < numVertices; i++)
	{
		T* target = reinterpret_cast<T*> (m_Data + (i * vSize) + vOffset);
		vector.push_back (*target);
	}

	return vector;
}*/
#endif