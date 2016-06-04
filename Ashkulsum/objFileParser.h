#ifndef OBJ_FILE_PARSER_H
#define OBJ_FILE_PARSER_H

#include <vector>
#include "glm\glm.hpp"
#include <fstream>
#include <sstream>
#include <list>
#include "primitive.h"
#include <algorithm>

class ObjFileParser 
{
public:
	struct Attributes 
	{
		int m_PrimitiveType;
		std::vector <short> m_Indices;
		std::vector <glm::vec3> m_Vertices;
		std::vector <glm::vec2> m_TexCoords;
	};

	struct ListAtt 
	{
		glm::vec3 m_ListVertex;
		glm::vec2 m_ListTex;
		short m_Index;
	};

	struct FindByVertex
	{
		const glm::vec3 vertex;
		FindByVertex (const glm::vec3& vertex) : vertex (vertex) {}

		bool operator() (const ListAtt& list) const 
		{
			return list.m_ListVertex == vertex;
		}
	};

	struct FindByVertexAndTex
	{
		const glm::vec3 vertex;
		const glm::vec2 tex;
		FindByVertexAndTex (const glm::vec3& vertex, const glm::vec2& tex) : vertex (vertex), tex (tex) {}

		bool operator() (const ListAtt& list) const 
		{
			return (list.m_ListVertex == vertex && list.m_ListTex == tex);
		}
	};

	static int LoadPrimitivesType (std::ifstream &stream);
	static std::vector<glm::vec3> LoadVertices (std::ifstream &stream);
	static std::vector<glm::vec2> LoadTexCoords (std::ifstream &stream);
	static std::list<ListAtt> GenUnweldList (std::ifstream &stream);
	static Attributes ComputeCoords (std::ifstream &stream);
};
#endif