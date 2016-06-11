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

protected:
	VertexAttributes m_VertexAttributes;
};
#endif