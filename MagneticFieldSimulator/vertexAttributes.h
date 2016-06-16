#ifndef VERTEX_ATTRIBUTES_H
#define VERTEX_ATTRIBUTES_H

#include "dataAttributes.h"
#include "glm\glm.hpp"

enum VAType
{
	VA_NO_TYPE,
	VA_POSITION,
	VA_TEXCOORD,
	VA_NORMAL,
	VA_INSTANCING,
};

enum VAConstant
{
	VA_MAX_NUMBER = 16,
	VA_MAX_TEXCOORDS = 8,
};

class VertexAttributes 
{
public:
	VertexAttributes ();

	bool Bind (VAType vaType, ContainerType containerType, int counter);
	size_t GetVertexSize () const;
	unsigned int GetNumAttrib () const;
	size_t GetOffset (int index) const;
	ContainerType GetContainerType (int index) const;

	int GetIndex (VAType vaType, int counter);

protected:
	class Attributes 
	{
	public:
		Attributes ();

		VAType m_VAType;
		int m_Counter;
		ContainerType m_ContainerType;
		size_t m_Offset;
	};

protected:
	unsigned int m_NumAttributes;
	size_t m_VertexSize;
	Attributes m_Attributes [VA_MAX_NUMBER];
};
#endif