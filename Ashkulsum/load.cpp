#include "stdafx.h"
#include "load.h"

std::vector<glm::vec3> LoadVertices (std::ifstream &stream)
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

std::vector<glm::vec2> LoadTexCoords (std::ifstream &stream)
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

Attributes ComputeCoords (int const& primitive, VertexAttributes const& vAttrib,  std::ifstream &stream)
{
	if (stream.is_open ())
	{
		Attributes attrib;

		std::string line, id;

		stream.clear ();
		stream.seekg(0, stream.beg);

		if (GeometryNode::TRIANGLEMESH == primitive)
		{
			std::vector<glm::vec3> vertices = LoadVertices (stream);
			std::vector<glm::vec2> texCoords = LoadTexCoords (stream);

			std::vector<ListAtt> newBuf;
			
			size_t verSize = vertices.size ();
			size_t texSize = texCoords.size ();

			size_t mSize = std::max (verSize, texSize);

			int* buffer = new int [mSize*mSize];

			for (unsigned int i = 0; i < mSize; i++)
			{
				for (unsigned int j = 0; j < mSize; j++)
				{
					buffer[i*mSize + j] = -1;
				}
			}

			std::vector <unsigned int> indices;
			char sl; // For the slashes between elements
			unsigned int i1, i2;	
			unsigned int indexCounter = 0;

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
						int s = buffer[i1*mSize + i2];
						
						if (s >= 0)
						{
							indices.push_back (s);
						}
						else
						{
							buffer[i1*mSize + i2] = indexCounter;
							ListAtt member;
							member.m_ListVertex = i1;
							member.m_ListTex = i2;
							newBuf.push_back (member);
							indices.push_back (indexCounter);
							indexCounter++;
						}
					}
				}
			}
			std::vector<ListAtt>::iterator it;
			
			for (it = newBuf.begin (); it!= newBuf.end (); it++)
			{
				attrib.m_Vertices.push_back (vertices[it->m_ListVertex]);
				attrib.m_TexCoords.push_back (texCoords[it->m_ListTex]);
			}
			attrib.m_Indices = indices;

			delete [] buffer;
		}	
		else
		{	
			std::vector<glm::vec3> vertices = LoadVertices (stream);
			std::vector <unsigned int> indices;
			unsigned int i1, i2;

			stream.clear ();
			stream.seekg(0, stream.beg);

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
		}

	return attrib;
	}
	else
		throw std::invalid_argument ("Error while opening the file! File not found");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<GeometryNode> LoadMesh (std::string const& name)
{
	PathEnvironment pathEnvironment;
	std::string pathDir = pathEnvironment.GetExeDir ();
	std::string pathName = pathDir + name;

	std::ifstream stream (pathName, std::ios::in);

	VertexAttributes vAttrib;
	vAttrib.Bind (VA_POSITION, DP_R32G32B32_FLOAT, 0);
	vAttrib.Bind (VA_TEXCOORD, DP_R32G32_FLOAT, 0);
	vAttrib.Bind (VA_NORMAL, DP_R32G32B32_FLOAT, 0);

	Attributes attrib = ComputeCoords (GeometryNode::TRIANGLEMESH, vAttrib, stream);
	int numVert = attrib.m_Vertices.size ();
	std::shared_ptr<VertexBuffer> vBuffer = std::make_shared<VertexBuffer> (vAttrib, numVert, true);
	
	struct Vertex
	{
		glm::vec3 m_Vertex;
		glm::vec2 m_Texture;
		glm::vec3 m_Normal;
	};

	Vertex* vertex = vBuffer->Get<Vertex> (); 

	int numAttrib = vAttrib.GetNumAttrib ();
	for (int i = 0; i < numVert; i++)
	{
		vertex[i].m_Vertex = attrib.m_Vertices[i];
		vertex[i].m_Texture = attrib.m_TexCoords[i];
	}
	
	int numIndices = attrib.m_Indices.size ();
	std::shared_ptr<IndexBuffer> iBuffer = std::make_shared<IndexBuffer> (P_TRIANGLES, numIndices, sizeof (unsigned int), true);

	unsigned int* indices = iBuffer->Get<unsigned int> ();

	for (int i = 0; i < numIndices; i++)
	{
		indices[i] = attrib.m_Indices[i];
	}

	std::shared_ptr<GeometryNode> mesh = std::make_shared<GeometryNode> ();
	mesh->SetVertexBuffer (vBuffer);
	mesh->SetIndexBuffer (iBuffer);
	mesh->UpdateModelNormals ();
	return mesh;
}

std::shared_ptr<GeometryNode> LoadLine (std::string const& name)
{
	PathEnvironment pathEnvironment;
	std::string pathDir = pathEnvironment.GetExeDir ();
	std::string pathName = pathDir + name;

	std::ifstream stream (pathName, std::ios::in);

	VertexAttributes vAttrib;
	vAttrib.Bind (VA_POSITION, DP_R32G32B32_FLOAT, 0);
	
	Attributes attrib = ComputeCoords (GeometryNode::POLYLINE, vAttrib, stream);
	int numVert = attrib.m_Vertices.size ();
	std::shared_ptr<VertexBuffer> vBuffer = std::make_shared<VertexBuffer> (vAttrib, numVert, true);
	int numAttrib = vAttrib.GetNumAttrib ();
	
	struct Vertex
	{
		glm::vec3 m_Vertex;
	};

	Vertex* vertex = vBuffer->Get<Vertex> (); 

	for (int i = 0; i < numVert; i++)
	{
		vertex[i].m_Vertex = attrib.m_Vertices[i];
	}
	
	int numIndices = attrib.m_Indices.size ();
	
	std::shared_ptr<IndexBuffer> iBuffer = std::make_shared<IndexBuffer> (P_LINES, numIndices, sizeof (unsigned int), true);

	unsigned int* indices = iBuffer->Get<unsigned int> ();

	for (int i = 0; i < numIndices; i++)
	{
		indices[i] = attrib.m_Indices[i];
	}

	std::shared_ptr<GeometryNode> line = std::make_shared<GeometryNode> ();
	line->SetVertexBuffer (vBuffer);
	line->SetIndexBuffer (iBuffer);

	return line;
}

std::shared_ptr<GeometryNode> LoadParticles (std::vector<glm::vec4> generatedPoints)
{
	int numVert = 6;
	glm::vec3 vertices[] = 
	{
		glm::vec3(-1.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, 1.0f, 0.0f),
	};

	glm::vec2 texcoords[] = 
	{
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
	};

	//std::shared_ptr<CGALInterpolationSimulator> cgalInterpolationSimulator = std::make_shared<CGALInterpolationSimulator> ();

	//std::vector<glm::vec4> pointVec = cgalInterpolationSimulator->GeneratePoints ();
	int numParticles = generatedPoints.size ();

	VertexAttributes vAttrib, instancedAttrib;
	vAttrib.Bind (VA_POSITION, DP_R32G32B32_FLOAT, 0);
	vAttrib.Bind (VA_TEXCOORD, DP_R32G32_FLOAT, 0);

	std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer> (vAttrib, numVert, true);
	
	struct Vertex 
	{
		glm::vec3 m_Position;
		glm::vec2 m_Texcoord;
	};

	Vertex* vertex = vertexBuffer->Get<Vertex> ();

	for (int i = 0; i < numVert; i++)
	{
		vertex[i].m_Position = vertices[i];
		vertex[i].m_Texcoord = texcoords[i];
	}

	struct InstancedVertex 
	{
		glm::vec2 m_TexCoord;
		glm::vec3 m_Instance;
	};

	instancedAttrib.Bind (VA_TEXCOORD, DP_R32G32_FLOAT, 0);
	instancedAttrib.Bind (VA_INSTANCING, DP_R32G32B32_FLOAT, 0);

	std::shared_ptr<VertexBuffer> instancedBuffer = std::make_shared<VertexBuffer> (instancedAttrib, numParticles, true);

	InstancedVertex* instance = instancedBuffer->Get<InstancedVertex> ();

	for (int i =0; i < numParticles; i++)
	{
		instance[i].m_Instance = glm::vec3 (generatedPoints[i]);
		instance[i].m_TexCoord = glm::vec2 (generatedPoints[i].w, 0.0f);
	}

	std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer> (P_TRIANGLES, numParticles);
	
	std::shared_ptr<GeometryNode> particles = std::make_shared<GeometryNode> ();
	particles->SetVertexBuffer (vertexBuffer);
	particles->SetInstancedBuffer (instancedBuffer);
	particles->SetIndexBuffer (indexBuffer);

	return particles;
}

std::shared_ptr<GeometryNode> LoadVolumetricLine (std::vector<glm::vec3> curvePoints, int numSegments)
{
	
	//BezierCurve bezierCurve (points);


	//std::vector<glm::vec3> curvePoints = bezierCurve.GenerateBezierCurveLineCoords (numSegments);

	int numVertices = curvePoints.size () * 4;
	float thickness = 0.2f;

	struct Vertex 
	{
		glm::vec3 m_Position1;
		glm::vec3 m_Position2;
		glm::vec4 m_TexOffset;
		glm::vec3 m_Thickness;
	};

	VertexAttributes vAttrib;

	vAttrib.Bind (VA_POSITION, DP_R32G32B32_FLOAT, 0);
	vAttrib.Bind (VA_TEXCOORD, DP_R32G32B32_FLOAT, 0);
	vAttrib.Bind (VA_TEXCOORD, DP_R32G32B32A32_FLOAT, 1);
	vAttrib.Bind (VA_TEXCOORD, DP_R32G32B32_FLOAT, 2);

	std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer> (vAttrib, numVertices, true);

	Vertex* vertData = vertexBuffer->Get<Vertex> ();

	for (unsigned int i = 0; i < curvePoints.size() - 1; i++)
	{
		glm::vec3 v0 = curvePoints[i];
		glm::vec3 v1 = curvePoints[i+1];

		vertData[i*4 +0].m_Position1 = v0;
		vertData[i*4 +0].m_Position2 = v1;
		vertData[i*4 +0].m_TexOffset = glm::vec4 (thickness, thickness, 0.0f, 0.0f);
		vertData[i*4 +0].m_Thickness = glm::vec3 (-thickness, 0.0f, thickness*0.5f);

		vertData[i*4 +1].m_Position1 = v1;
		vertData[i*4 +1].m_Position2 = v0;
		vertData[i*4 +1].m_TexOffset = glm::vec4 (thickness, thickness, 0.25f, 0.0f);
		vertData[i*4 +1].m_Thickness = glm::vec3 (thickness, 0.0f, thickness*0.5f);

		vertData[i*4 +2].m_Position1 = v1;
		vertData[i*4 +2].m_Position2 = v0;
		vertData[i*4 +2].m_TexOffset = glm::vec4 (thickness, thickness, 0.25f, 0.25f);
		vertData[i*4 +2].m_Thickness = glm::vec3 (-thickness, 0.0f, thickness*0.5f);

		vertData[i*4 +3].m_Position1 = v0;
		vertData[i*4 +3].m_Position2 = v1; 
		vertData[i*4 +3].m_TexOffset = glm::vec4 (thickness, thickness, 0.0f, 0.25f);
		vertData[i*4 +3].m_Thickness = glm::vec3 (thickness, 0.0f, thickness*0.5f);
			
	}
	
	int numIndices = curvePoints.size () * 6;
	std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer> (P_TRIANGLES, numIndices, sizeof (unsigned int), true);

	unsigned int* indexData = indexBuffer->Get<unsigned int> ();
	int j = 0;
	for (int i = 0; i < numIndices; i+=6, j+=4)
	{
		indexData[i+0] = 0 +j;
		indexData[i+1] = 3 +j;
		indexData[i+2] = 1 +j;
	
		indexData[i+3] = 3 +j;
		indexData[i+4] = 2 +j;
		indexData[i+5] = 1 +j;
	}
	std::shared_ptr<GeometryNode> line = std::make_shared<GeometryNode> ();
	line->SetVertexBuffer (vertexBuffer);
	line->SetIndexBuffer (indexBuffer);

	return line;
}

