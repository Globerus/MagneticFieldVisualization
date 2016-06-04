#include "stdafx.h"
#include "mesh.h"
Mesh::Mesh (std::string fileName)
{
	Primitives type;
	std::vector<glm::vec3> vertices, faceNormals, vertexNormals;
	std::vector<glm::vec2> texCoords;
	std::vector<short> indicesVertices, indicesTexCoords;

	this->SetSupportedExtensions ();
	LoadFile (fileName, type, vertices, texCoords, indicesVertices, indicesTexCoords, faceNormals, vertexNormals);

	this->SetPrimitives (type);
	this->SetVertices (vertices);
	this->SetTexCoords (texCoords);
	this->SetIndicesVertices (indicesVertices);
	this->SetIndicesTexCoords (indicesTexCoords);
	this->SetFaceNormals (faceNormals);
	this->SetVertexNormals (vertexNormals);
}



void Mesh::LoadFile (std::string fileName, Primitives &type, std::vector <glm::vec3> &vertices, std::vector <glm::vec2> &texCoords, std::vector <short> &indicesVertices, std::vector <short> &indicesTexCoords, std::vector <glm::vec3> &faceNormals, std::vector <glm::vec3> &vertexNormals)
{
	std::string extension = boost::filesystem::extension (fileName);
	
	if (this->IsFileSupported (extension))
	{
		std::string fullDirPath = Utils::GetFullDirPath (fileName);
		std::ifstream stream (fullDirPath, std::ios::in);

		if (stream.is_open ())
		{
			type = LoadPrimitivesType (stream);
			vertices = LoadVertices (stream);
			texCoords = LoadTexCoords (stream);
			LoadIndices (type, stream, indicesVertices, indicesTexCoords);

			faceNormals = GenerateFaceNormals (type, vertices, indicesVertices);
			vertexNormals = GenerateVertexNormals (type, faceNormals, indicesVertices);

			vertices = ProcessVertices (type, vertices, indicesVertices);
			texCoords = ProcessTexCoords (type, texCoords, indicesTexCoords);
		}
		else
			throw std::invalid_argument ("Error while opening the file! File not found");
	}
	else
		throw std::invalid_argument ("Error while opening the file! Unsupported format");
}
Primitives Mesh::LoadPrimitivesType (std::ifstream &stream)
{
	Primitives type;
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

std::vector <glm::vec3> Mesh::LoadVertices (std::ifstream &stream)
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

std::vector <glm::vec2> Mesh::LoadTexCoords (std::ifstream &stream)
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

void Mesh::LoadIndices (Primitives type, std::ifstream &stream, std::vector <short> &indicesVertices, std::vector <short> &indicesTexCoords)
{
	std::string line, id;

	stream.clear ();
	stream.seekg(0, stream.beg);

	if (Triangle == type)
	{
		char sl1, sl2, sl3; // For the slashes between elements
		unsigned short i1, i2, i3, i4, i5, i6;
		while (std::getline (stream, line))
		{
			std::istringstream sstream (line);
			sstream >> id;
			if (id == "f")
				{
					sstream >> i1 >> sl1 >> i2 >> i3 >> sl2 >> i4 >> i5 >> sl3 >> i6;
					i1--; i2--; i3--; i4--; i5--; i6--;
					indicesVertices.push_back (i1); indicesVertices.push_back (i3); indicesVertices.push_back (i5);
					indicesTexCoords.push_back (i2); indicesTexCoords.push_back (i4); indicesTexCoords.push_back (i6);
				}
		}
	}
	else
	{	
		unsigned short i1, i2;
		while (std::getline (stream, line))
		{
			std::istringstream sstream (line);
			sstream >> id;
			if (id == "l")
			{
				sstream >> i1 >> i2;
				i1--; i2--;
				indicesVertices.push_back (i1); indicesVertices.push_back (i2);
			}
		}	
	}
}

std::vector <glm::vec3> Mesh::ProcessVertices (Primitives type, std::vector <glm::vec3> vertices, std::vector <short> indicesVertices)
{
	std::vector <glm::vec3> processedVertices;
	
	if (!vertices.empty () && !indicesVertices.empty ())
	{
		unsigned int indices;
		if (Triangle == type)
			indices = 3;
		else
			indices = 2;

		for( unsigned int v=0; v<indicesVertices.size(); v+=indices )
		{
			// For each vertex of the triangle
			for ( unsigned int i=0; i<indices; i+=1 )
			{
				unsigned int vertexIndex = indicesVertices[v+i];
				glm::vec3 vertex = vertices[ vertexIndex ];
				processedVertices.push_back(vertex);
			}
		}
	}
	else
	{
		throw std::invalid_argument ("Error while processing the vertices for");
	}

	return processedVertices;
}

std::vector <glm::vec2> Mesh::ProcessTexCoords (Primitives type, std::vector <glm::vec2> texCoords, std::vector <short> indicesTexCoords)
{
	std::vector <glm::vec2> processedTexCoords;
	if (type == Triangle)
	{
		if (!texCoords.empty() && !indicesTexCoords.empty())
		{
			unsigned int indices;
			if (Triangle == type)
				indices = 3;
			else
				indices = 2;
	
			for( unsigned int t=0; t<indicesTexCoords.size(); t+=indices )
			{
				// For each vertex of the triangle
				for ( unsigned int i=0; i<indices; i+=1 )
				{
					unsigned int texCoordIndex = indicesTexCoords[t+i];
					glm::vec2 texCoord = texCoords[ texCoordIndex ];
					processedTexCoords.push_back(texCoord);
				}
			}
		}
		else
			throw std::invalid_argument ("Error while processing the texture coordinates for");
	
	}
	return processedTexCoords;
}

std::vector <glm::vec3> Mesh::GenerateFaceNormals (Primitives type, std::vector <glm::vec3> vertices, std::vector <short> indicesVertices)
{
	std::vector <glm::vec3> processedFaceNormals;

	if (Triangle == type)
	{
		if (!vertices.empty () && !indicesVertices.empty ())
		{
			processedFaceNormals.resize(vertices.size(), glm::vec3(0.0f));
			std::vector<short> nb_seen;
			nb_seen.resize(vertices.size(), 0);
			for (unsigned int i = 0; i < indicesVertices.size(); i+=3) 
			{
				unsigned short ia = indicesVertices[i];
				unsigned short ib = indicesVertices[i+1];
				unsigned short ic = indicesVertices[i+2];
				glm::vec3 cross = glm::cross(glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
									 glm::vec3(vertices[ic]) - glm::vec3(vertices[ia]));
				glm::vec3 normal = glm::normalize(cross);
				int v[3]; v[0] = ia; v[1] = ib; v[2] = ic;
				for (int j = 0; j < 3; j++) 
				{
					unsigned short cur_v = v[j];
					nb_seen[cur_v]++;
					if (nb_seen[cur_v] == 1) 
					{
						processedFaceNormals[cur_v] = normal;
					} else 
					{
					// average
						processedFaceNormals[cur_v].x = processedFaceNormals[cur_v].x * (1.0f - 1.0f/nb_seen[cur_v]) + normal.x * 1.0f/nb_seen[cur_v];
						processedFaceNormals[cur_v].y = processedFaceNormals[cur_v].y * (1.0f - 1.0f/nb_seen[cur_v]) + normal.y * 1.0f/nb_seen[cur_v];
						processedFaceNormals[cur_v].z = processedFaceNormals[cur_v].z * (1.0f - 1.0f/nb_seen[cur_v]) + normal.z * 1.0f/nb_seen[cur_v];		
						processedFaceNormals[cur_v] = glm::normalize(processedFaceNormals[cur_v]);
					}
				}
			}
		} 
		else
		{
			throw std::invalid_argument ("Error while generating the face normals for");
		}
	}

	return processedFaceNormals;
}

std::vector <glm::vec3> Mesh::GenerateVertexNormals (Primitives type, std::vector <glm::vec3> faceNormals, std::vector <short> indicesVertices)
{
	std::vector <glm::vec3> processedVertexNormals;

	if (type == Triangle)
	{
		if (!faceNormals.empty())
		{
			for( unsigned int v=0; v<indicesVertices.size(); v+=3 )
			{
				// For each vertex of the triangle
				for ( unsigned int i=0; i<3; i+=1 )
				{
					unsigned int vertexIndex = indicesVertices[v+i];
					glm::vec3 normal = faceNormals[ vertexIndex ];
					processedVertexNormals.push_back(normal);
				}
			}
		}
		else
			throw std::invalid_argument ("Error while generating the vertex normals for");
	}
	return processedVertexNormals;
}


Primitives Mesh::GetPrimitives ()
{
	return this->m_Primitives;
}

std::vector <glm::vec3> Mesh::GetVertices ()
{
	return this->m_Vertices;
}

std::vector <glm::vec3> Mesh::GetVertexNormals ()
{
	return this->m_VertexNormals;
}

std::vector <glm::vec3> Mesh::GetFaceNormals ()
{
	return this->m_FaceNormals;
}

std::vector <glm::vec2> Mesh::GetTexCoords ()
{
	return this->m_TexCoords;
}

std::vector <short> Mesh::GetIndicesVertices ()
{
	return this->m_IndicesVertices;
}

std::vector <short> Mesh::GetIndicesTexCoords ()
{
	return this->m_IndicesTexCoords;
}




void Mesh::SetPrimitives (Primitives primitives)
{
	this->m_Primitives = primitives;
}

void Mesh::SetVertices (std::vector <glm::vec3> vertices)
{
	this->m_Vertices = vertices;
}

void Mesh::SetVertexNormals (std::vector <glm::vec3> vertexNormals)
{
	this->m_VertexNormals = vertexNormals;
}

void Mesh::SetFaceNormals (std::vector <glm::vec3> faceNormals)
{
	this->m_FaceNormals = faceNormals;
}

void Mesh::SetTexCoords (std::vector <glm::vec2> texCoords)
{
	this->m_TexCoords = texCoords;
}

void Mesh::SetIndicesVertices (std::vector <short> indicesVertices)
{
	this->m_IndicesVertices = indicesVertices;
}

void Mesh::SetIndicesTexCoords (std::vector <short> indicesTexCoords)
{
	this->m_IndicesTexCoords = indicesTexCoords;
}


/*GLuint Mesh::GetVao ()
{
	return this->m_Vao;
}

GLuint Mesh::GetVertexBufferObject ()
{
	return this->m_VertexBufferObject;
}

GLuint Mesh::GetNormalBufferObject ()
{
	return this->m_NormalBufferObject;
}

GLuint Mesh::GetTextureBufferObject ()
{
	return this->m_TextureBufferObject;
}

Primitives Mesh::GetPrimitives ()
{
	return this->m_Primitives;
}

void Mesh::SetVao (GLuint vao)
{
	this->m_Vao = vao;
}

void Mesh::SetVertexBufferObject (GLuint vertexBufferObject)
{
	this->m_VertexBufferObject = vertexBufferObject;
}

void Mesh::SetNormalBufferObject (GLuint normalBufferObject)
{
	this->m_NormalBufferObject = normalBufferObject;
}

void Mesh::SetTextureBufferObject (GLuint textureBufferObject)
{
	this->m_TextureBufferObject = textureBufferObject;
}

void Mesh::SetPrimitives (Primitives primitives)
{
	this->m_Primitives = primitives;			
}
void Mesh::InitializeMesh ()
{
	if (!this->vertices.empty())
	{
		//GLuint vertexBufferObject = GetVertexBufferObject();
		glGenBuffers(1, &this->vertexBufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size ()*sizeof (glm::vec3), &this->vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//SetVertexBufferObject (vertexBufferObject);
	}
	if (!this->vertexNormals.empty())
	{
		//GLuint normalBufferObject = GetNormalBufferObject();
		glGenBuffers(1, &this->normalBufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, this->normalBufferObject);
		glBufferData(GL_ARRAY_BUFFER, this->vertexNormals.size ()*sizeof (glm::vec3), &this->vertexNormals[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//SetNormalBufferObject (normalBufferObject);
	}
	if (!this->texCoords.empty())
	{
		//GLuint textureBufferObject = GetTextureBufferObject();
		glGenBuffers(1, &this->textureBufferObject);

		glBindBuffer(GL_ARRAY_BUFFER, this->textureBufferObject);
		glBufferData(GL_ARRAY_BUFFER, this->texCoords.size ()*sizeof (glm::vec2), &this->texCoords[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//SetTextureBufferObject (textureBufferObject);
	}
	/*if (!colours.empty ())
	{
		GLuint colourBufferObject = GetColourBufferObject();
		glGenBuffers(1, &colourBufferObject);
	
		glBindBuffer (GL_ARRAY_BUFFER, colourBufferObject);	
		glBufferData(GL_ARRAY_BUFFER, colours.size ()*sizeof (glm::vec4), &colours[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		SetColourBufferObject (colourBufferObject);	
	}
}*/