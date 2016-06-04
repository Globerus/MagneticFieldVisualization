#include "stdafx.h"
#include "objFileParser.h"

ObjFileParser::Attributes ObjFileParser::ComputeCoords (std::ifstream &stream)
{
	if (stream.is_open ())
	{
		Attributes attrib;

		int type = LoadPrimitivesType (stream);

		std::string line, id;

		stream.clear ();
		stream.seekg(0, stream.beg);

		if (Triangle == type)
		{
			std::vector<glm::vec3> vertices = LoadVertices (stream);
			std::vector<glm::vec2> texCoords = LoadTexCoords (stream);
			std::list <ListAtt> unweldBuf = GenUnweldList (stream);

			std::vector <short> indices;
			char sl; // For the slashes between elements
			unsigned short i1, i2;	
			short indexCounter = unweldBuf.size ();

			while (std::getline (stream, line))
			{
				std::istringstream sstream (line);
				sstream >> id;
				if (id == "f")
				{
					while (sstream >> i1 >> sl >> i2)
					{
						i1--; i2--;
						glm::vec3 vertex = vertices.at (i1); 
						glm::vec2 tex = texCoords.at (i2);

						std::list <ListAtt>::iterator it;
						it = std::find_if (unweldBuf.begin (), unweldBuf.end (), FindByVertexAndTex (vertex, tex));
						
						if ( it != unweldBuf.end ())
						{
							indices.push_back ((*it).m_Index);
						}
						else
						{
							++indexCounter;
							ListAtt member;
							member.m_ListVertex = vertex;
							member.m_ListTex = tex;
							member.m_Index = indexCounter;
							unweldBuf.push_back (member);
							indices.push_back (indexCounter);	
						}
					}
				}
			}
			std::list<ListAtt>::iterator it;
			
			for (it = unweldBuf.begin (); it!= unweldBuf.end (); it++)
			{
				attrib.m_Vertices.push_back ((*it).m_ListVertex);
				attrib.m_TexCoords.push_back ((*it).m_ListTex);
			}
			attrib.m_Indices = indices;
			attrib.m_PrimitiveType = type;
		}
		else
		{	
			std::vector<glm::vec3> vertices = LoadVertices (stream);
			std::vector <short> indices;
			unsigned short i1, i2;
			while (std::getline (stream, line))
			{
				std::istringstream sstream (line);
				sstream >> id;
				if (id == "l")
				{
					sstream >> i1 >> i2;
					i1--; i2--;
					indices.push_back (i1);
					indices.push_back (i2);
				}
			}	
			attrib.m_Indices = indices;
			attrib.m_Vertices = vertices;
			attrib.m_PrimitiveType = type;
		}

		return attrib;
	}
	else
		throw std::invalid_argument ("Error while opening the file! File not found");
}

std::vector<glm::vec3> ObjFileParser::LoadVertices (std::ifstream &stream)
{
	std::vector <glm::vec3> vertices;
	std::string id, line;

	stream.clear ();
	stream.seekg(0, stream.beg);

	while (std::getline (stream, line))
	{
		std::istringstream sstream (line);
		sstream >> id;
		if (id == "v")
		{
				glm::vec3 row;
				sstream >> row.x >> row.y >> row.z;
				vertices.push_back (row);
		}
	}

	return vertices;
}

std::vector<glm::vec2> ObjFileParser::LoadTexCoords (std::ifstream &stream)
{
	std::vector <glm::vec2> texCoords;
	std::string id, line;

	stream.clear ();
	stream.seekg(0, stream.beg);

	while (std::getline (stream, line))
	{
		std::istringstream sstream (line);
		sstream >> id;
		if (id == "vt")
		{
				glm::vec2 texCoordIn; 
				sstream >> texCoordIn.x >> texCoordIn.y;	
				texCoordIn.y = 1.0f - texCoordIn.y;
				texCoords.push_back (texCoordIn);
		}
	}
	return texCoords;
}

int ObjFileParser::LoadPrimitivesType (std::ifstream &stream)
{
	int type;
	std::string line, id;
	
	stream.clear ();
	stream.seekg(0, stream.beg);

	while (std::getline (stream, line))
	{
		std::istringstream sstream;
		stream >> id;
		if	(id == "l")
		{
			type = Line;
			break;
		}
		else if (id == "f")
		{
			type = Triangle;
			break;
		}
	}
	return type;
}

std::list<ObjFileParser::ListAtt> ObjFileParser::GenUnweldList (std::ifstream &stream)
{
	std::list<ListAtt> unweldBuf;

	std::string line, id;
	char sl; // For the slashes between elements
	unsigned short i1, i2;
	std::vector<glm::vec3> vertices = LoadVertices (stream);
	std::vector<glm::vec2> texCoords = LoadTexCoords (stream);
	short unweldBufCounter = 0;

	stream.clear ();
	stream.seekg(0, stream.beg);
	
	while (std::getline (stream, line))
	{
		std::istringstream sstream (line);
		sstream >> id;
		if (id == "f")
		{
			while (sstream >> i1 >> sl >> i2)
			{
				i1--; i2--;
				glm::vec3 vertex = vertices.at (i1); 
				glm::vec2 tex = texCoords.at (i2);
					
				std::list <ListAtt>::iterator it;
				it = std::find_if (unweldBuf.begin (), unweldBuf.end (), FindByVertex (vertex));

				if (it == unweldBuf.end ())
				{
					ListAtt listAtt;
					listAtt.m_ListVertex = vertex;
		 			listAtt.m_ListTex = tex;
					listAtt.m_Index = unweldBufCounter;

					unweldBuf.push_back (listAtt);
					unweldBufCounter++;
				}
			}
		}
	}
	return unweldBuf;
}