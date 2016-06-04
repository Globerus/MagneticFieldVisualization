#include "stdafx.h"
/*#include "loader2.h"

Primitives LoadDrawPrimitive (const std::string shaderPath)
{	
	std::string line;
	const char * strShaderPath = shaderPath.c_str();
	std::ifstream fileStream (strShaderPath, std::ios::in);
	getline (fileStream, line);
	if	(line == "line")
		return Line;
	else
		return Triangle;
}

static std::vector <glm::vec3> LoadObjectVertices (const std::string Path)
{
	std::string line;
	const char * strPath = Path.c_str();
	std::ifstream fileStream (strPath, std::ios::in);
	std::vector <glm::vec3> vertices;

	while (!fileStream.eof())
	{
		getline (fileStream, line);
		if	(!line.empty () && (line.substr (0, 2) == "v "))
		{
				std::istringstream s(line.substr(2));
				glm::vec3 v; s >> v.x >> v.y >> v.z;
				vertices.push_back (v);
		}
	}
	fileStream.close ();
	return vertices;
	std::vector <glm::vec3>().swap (vertices);
}

static std::vector <glm::vec2> LoadObjectTexCoords (const std::string Path)
{
	std::string line;
	const char * strPath = Path.c_str();
	std::ifstream fileStream (strPath, std::ios::in);
	std::vector <glm::vec2> texCoords;
	while (!fileStream.eof())
	{
		getline (fileStream, line);
		if	(!line.empty () && (line.substr (0, 2) == "vt"))
		{
				std::istringstream s(line.substr(2));
				glm::vec2 t; s >> t.x >> t.y;
				t.y = 1.0f - t.y;
				texCoords.push_back (t);
		}
	}
	fileStream.close ();
	return texCoords;
	std::vector <glm::vec2>().swap (texCoords);
}

std::pair <std::vector <GLshort>, std::vector <GLshort>> LoadObjectIndices (Primitives prim, const std::string Path)
{	
	if (Triangle == prim)
	{
	std::vector <GLshort> indicesVertices;
	std::vector <GLshort> indicesTexCoords;
	std::string ident = "f ";
	std::string line;
	const char * strPath = Path.c_str();
	std::ifstream fileStream (strPath, std::ios::in);
	while (!fileStream.eof())
	{
		getline (fileStream, line);
		if	(!line.empty () && (line.substr (0, 2) == ident))
			{
				std::istringstream s(line.substr(2));
				char tmp; // For the slashes between elements
                unsigned short a,b,c, d,e,f;
                s >> a >> tmp >> d;
                s >> b >> tmp >> e;
                s >> c >> tmp >> f;
                a--; b--; c--; d--; e--; f--;
				indicesVertices.push_back (a); indicesVertices.push_back (b); indicesVertices.push_back (c);
				indicesTexCoords.push_back (d); indicesTexCoords.push_back (e); indicesTexCoords.push_back (f);
			}
	}
	fileStream.close ();
	std::pair <std::vector <GLshort>, std::vector <GLshort>> pair = std::make_pair(indicesVertices, indicesTexCoords);
	return pair;
	std::vector <GLshort>().swap (indicesVertices);
	std::vector <GLshort>().swap (indicesTexCoords);
	}
	else
	{
		std::vector <GLshort> indicesVertices;
		std::string ident = "l ";
		std::string line;
		const char * strPath = Path.c_str();
		std::ifstream fileStream (strPath, std::ios::in);
		while (!fileStream.eof())
		{
			getline (fileStream, line);
			if	(!line.empty () && (line.substr (0, 2) == ident))
			{
				std::istringstream s(line.substr(2));
				GLushort a,b;
				s >> a >> b;
				a--; b--;
				indicesVertices.push_back (a); indicesVertices.push_back (b);
			}
		}	
		fileStream.close ();
		std::pair <std::vector <GLshort>, std::vector <GLshort>> pair = std::make_pair(indicesVertices, 0);
		return pair;
		std::vector <GLshort>().swap (indicesVertices);
	}
}

std::vector <glm::vec4>  LoadObjectColours (const std::string Path)
{
	// OBJ does not support colours
	std::vector <glm::vec4> vec;
	return vec;
}


std::vector <glm::vec3> GenerateFaceNormals (Primitives prim, std::vector <glm::vec3> vertices, std::vector <GLshort> indicesVertices)
{
	if (Triangle == prim)
	{
		std::vector <glm::vec3> faceNormals;		
		if (!vertices.empty () && !indicesVertices.empty ())
		{
			faceNormals.resize(vertices.size(), glm::vec3(0.0f));
			std::vector<GLshort> nb_seen;
			nb_seen.resize(vertices.size(), 0);
			for (unsigned int i = 0; i < indicesVertices.size(); i+=3) 
			{
				GLushort ia = indicesVertices[i];
				GLushort ib = indicesVertices[i+1];
				GLushort ic = indicesVertices[i+2];
				glm::vec3 cross = glm::cross(glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
									 glm::vec3(vertices[ic]) - glm::vec3(vertices[ia]));
				glm::vec3 normal = glm::normalize(cross);
				int v[3]; v[0] = ia; v[1] = ib; v[2] = ic;
				for (int j = 0; j < 3; j++) 
				{
					GLushort cur_v = v[j];
					nb_seen[cur_v]++;
					if (nb_seen[cur_v] == 1) 
					{
						faceNormals[cur_v] = normal;
					} else 
					{
					// average
						faceNormals[cur_v].x = faceNormals[cur_v].x * (1.0f - 1.0f/nb_seen[cur_v]) + normal.x * 1.0f/nb_seen[cur_v];
						faceNormals[cur_v].y = faceNormals[cur_v].y * (1.0f - 1.0f/nb_seen[cur_v]) + normal.y * 1.0f/nb_seen[cur_v];
						faceNormals[cur_v].z = faceNormals[cur_v].z * (1.0f - 1.0f/nb_seen[cur_v]) + normal.z * 1.0f/nb_seen[cur_v];		
						faceNormals[cur_v] = glm::normalize(faceNormals[cur_v]);
					}
				}
			}
			return faceNormals;
			std::vector <glm::vec3>().swap (faceNormals);
			std::vector <glm::vec3>().swap (vertices);
			std::vector <GLshort>().swap (indicesVertices);
		} 
	}
}
std::vector <glm::vec3> GenerateVertexNormals (std::vector <glm::vec3> faceNormals, std::vector <GLshort> indicesVertices)
{
	std::vector <glm::vec3> vertexNormals;
	if (!faceNormals.empty())
	{
		for( unsigned int v=0; v<indicesVertices.size(); v+=3 )
		{
			// For each vertex of the triangle
			for ( unsigned int i=0; i<3; i+=1 )
			{
				unsigned int vertexIndex = indicesVertices[v+i];
				glm::vec3 normal = faceNormals[ vertexIndex ];
				vertexNormals.push_back(normal);
			}
		}
		return vertexNormals;
		std::vector <glm::vec3>().swap (faceNormals);
		std::vector <glm::vec3>().swap (vertexNormals);
		std::vector <GLshort>().swap (indicesVertices);
	}
}

std::vector <glm::vec3> ReformatVertices (Primitives prim, std::vector <glm::vec3> vertices, std::vector <GLshort> indicesVertices)
{
	unsigned int indices;
	if (Triangle == prim)
		indices = 3;
	else
		indices = 2;

	std::vector <glm::vec3> reformatedVertices;
	if (!vertices.empty () && !indicesVertices.empty ())
	{
		for( unsigned int v=0; v<indicesVertices.size(); v+=indices )
		{
			// For each vertex of the triangle
			for ( unsigned int i=0; i<indices; i+=1 )
			{
				unsigned int vertexIndex = indicesVertices[v+i];
				glm::vec3 vertex = vertices[ vertexIndex ];
				reformatedVertices.push_back(vertex);
			}
		}
		return reformatedVertices;
		std::vector <glm::vec3>().swap (vertices);
		std::vector <glm::vec3>().swap (reformatedVertices);
		std::vector <GLshort>().swap (indicesVertices);
	}
}

std::vector <glm::vec2> ReformatTexCoords (Primitives prim, std::vector <glm::vec2> texCoords, std::vector <GLshort> indicesTexCoords)
{
	unsigned int indices;
	if (Triangle == prim)
		indices = 3;
	else
		indices = 2;

	std::vector <glm::vec2> reformatedTexCoords;
	if (!texCoords.empty() && !indicesTexCoords.empty())
	{
		for( unsigned int t=0; t<indicesTexCoords.size(); t+=indices )
		{
			// For each vertex of the triangle
			for ( unsigned int i=0; i<indices; i+=1 )
			{
				unsigned int texCoordIndex = indicesTexCoords[t+i];
				glm::vec2 texCoord = texCoords[ texCoordIndex ];
				reformatedTexCoords.push_back(texCoord);
			}
		}
		return reformatedTexCoords;
		std::vector <glm::vec2>().swap (texCoords);
		std::vector <glm::vec2>().swap (reformatedTexCoords);
		std::vector <GLshort>().swap (indicesTexCoords);
	}
}
std::vector <glm::vec4> ReformatColours (Primitives prim, std::vector <glm::vec4> colours, std::vector <GLshort> indicesColours)
{
	unsigned int indices;
	if (Triangle == prim)
		indices = 3;
	else
		indices = 2;

	std::vector <glm::vec4> reformatedColours;	
	if (!colours.empty() && !indicesColours.empty())
	{
		for( unsigned int c=0; c<indicesColours.size(); c+=indices )
		{
			// For each colour of the triangle
			for ( unsigned int i=0; i<indices; i+=1 )
			{
				unsigned int colourIndex = indicesColours[c+i];
				glm::vec4 colour = colours[ colourIndex ];
				reformatedColours.push_back(colour);
			}
		}
		return reformatedColours;
		std::vector <glm::vec4>().swap (colours);
		std::vector <glm::vec4>().swap (reformatedColours);
		std::vector <GLshort>().swap (indicesColours);
	}
}
static void LoadObjectFile (MeshObject* mesh, MaterialObject* material, const std::string Path)
{
	std::string strFilename = LOCAL_OBJECT_DIR + Path;
	Primitives prim = LoadDrawPrimitive (strFilename);	
	std::vector <glm::vec3> vertices = ReformatVertices (prim, LoadObjectVertices (strFilename), LoadObjectIndices (prim, strFilename).first);
	std::vector <glm::vec3> faceNormals = GenerateFaceNormals (prim, LoadObjectVertices (strFilename), LoadObjectIndices (prim, strFilename).first);
	std::vector <glm::vec3> vertexNormals = GenerateVertexNormals (faceNormals, LoadObjectIndices (prim, strFilename).first);
	std::vector <glm::vec2> texCoords = ReformatTexCoords (prim, LoadObjectTexCoords (strFilename), LoadObjectIndices (prim, strFilename).second);
	std::vector <GLshort> indicesColours (0);
	std::vector <glm::vec4> colours = ReformatColours (prim, LoadObjectColours (strFilename), indicesColours);
	mesh->InitializeBuffers (vertices, vertexNormals, texCoords, colours);
}*/
