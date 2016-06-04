#include "stdafx.h"
#include "resource.h"
/*
void ResourceData::IncCounter ()
{
	this->m_Counter += 1;
}

void ResourceData::DecCounter ()
{
	if (this->m_Counter > 0)
		this->m_Counter -= 1;
}

int ResourceData::GetCounter ()
{
	return this->m_Counter;
}


void ResourceTree::Add (std::string fileName, ResourceData::RsrcDataPtr rsrcData)
{
	ResourceMap::iterator it;
	it = m_ResourceMap.find (fileName);

	if (it == m_ResourceMap.end ())
	{
		m_ResourceMap[fileName] = rsrcData;
	}
	else
		throw std::invalid_argument ("Error: There is another resource already loaded with name:");
}

void ResourceTree::Remove (std::string fileName)
{
	std::map<std::string, ResourceData::RsrcDataPtr>::iterator it;
	it = m_ResourceMap.find (fileName);

	if (it != m_ResourceMap.end ())
	{
		it->second.reset ();
		m_ResourceMap.erase (it);
	}
	else
		throw std::invalid_argument ("Error: There is no resource to be deleted with name:");
}

ResourceData::RsrcDataPtr ResourceTree::Find (std::string fileName)
{
	ResourceData::RsrcDataPtr rsrcData (nullptr);

	std::map<std::string, ResourceData::RsrcDataPtr>::iterator it;
	it = m_ResourceMap.find (fileName);

	if (it != m_ResourceMap.end ())
	{
		rsrcData = it->second;
	}

	return rsrcData;
}


/*ResourceImage::ResourceImage (FileStream::FileStreamPtr fileStream)
{
	this->SetImageData (fileStream->GetImageData ());
	this->SetImageWidth (fileStream->GetImageWidth ());
	this->SetImageHeight (fileStream->GetImageHeight ());
}

unsigned char* ResourceImage::GetImageData ()
{
	return this->m_ImageData;
}

int ResourceImage::GetImageWidth ()
{
	return this->m_ImageWidth;
}

int ResourceImage::GetImageHeight ()
{
	return this->m_ImageHeight;
}


void ResourceImage::SetImageData (unsigned char* imageData)
{
	this->m_ImageData = imageData;
}

void ResourceImage::SetImageWidth (int width)
{
	this->m_ImageWidth = width;
}

void ResourceImage::SetImageHeight (int height)
{
	this->m_ImageHeight = height;
}



ResourceFont::ResourceFont (FileStream::FileStreamPtr fileStream)
{
	this->SetImageData (fileStream->GetImageData ());
	this->SetImageWidth (fileStream->GetImageWidth ());
	this->SetImageHeight (fileStream->GetImageHeight ());
}

ResourceLight::ResourceLight (FileStream::FileStreamPtr fileStream)
{
	glm::vec4 lightIntensity;
	glm::vec3 lightPosition;
	double lightAttenuation;

	LoadLightParam (fileStream->GetStream (), lightIntensity, lightPosition, lightAttenuation);
	
	this->SetLightItensity (lightIntensity);
	this->SetLightPosition (lightPosition);
	this->SetLightAttenuation (lightAttenuation);
}

void ResourceLight::LoadLightParam (FileStream::FStreamPtr stream, glm::vec4 &lightIntensity, glm::vec3 &lightPosition, double &lightAttenuation)
{
	std::string line, id;
	stream->clear ();
	stream->seekg(0, stream->beg);

	while (std::getline (*stream, line))
		{
			std::istringstream sstream (line);
			sstream >> id;
			if (id == "li")
			{
				double x, y, z, a;
				sstream >> x >> y >> z >> a;
				lightIntensity = glm::vec4 (x, y, z, a);
			}
			else if (id == "lp")
			{
				double x, y, z;
				sstream >> x >> y >> z;
				lightPosition = glm::vec3 (x, y, z);
			}
			else if (id == "la")
			{
				double x;
				sstream >> x;
				lightAttenuation = x;
			}
		}
}

glm::vec4 ResourceLight::GetLightIntensity ()
{
	return this->m_LightIntensity;
}

glm::vec3 ResourceLight::GetLightPosition ()
{
	return this->m_LightPosition;
}

double ResourceLight::GetLightAttenuation ()
{
	return this->m_LightAttenuation;
}


void ResourceLight::SetLightItensity (glm::vec4 lightIntensity)
{
	this->m_LightIntensity = lightIntensity;
}

void ResourceLight::SetLightPosition (glm::vec3 lightPosition)
{
	this->m_LightPosition = lightPosition;
}

void ResourceLight::SetLightAttenuation (double lightAttenuation)
{
	this->m_LightAttenuation = lightAttenuation;
}


ResourceMaterial::ResourceMaterial (FileStream::FileStreamPtr fileStream)
{
	glm::vec4 ambientIntensity;
	double shinninessFactor;

	LoadMaterialParam (fileStream->GetStream (), ambientIntensity, shinninessFactor);

	this->SetAmbientIntensity (ambientIntensity);
	this->SetShinninessFactor (shinninessFactor);
}

void ResourceMaterial::LoadMaterialParam (FileStream::FStreamPtr stream, glm::vec4 &ambientIntensity, double &shinninessFactor)
{
	std::string line, id;
	stream->clear ();
	stream->seekg(0, stream->beg);

	while (std::getline (*stream, line))
		{
			std::istringstream sstream (line);
			sstream >> id;
			if (id == "ai")
			{
				double x, y, z, a;
				sstream >> x >> y >> z >> a;
				ambientIntensity = glm::vec4 (x, y, z, a);
			}
			else if (id == "sf")
			{
				double x;
				sstream >>x;
				shinninessFactor = x;
			}
		}
}

glm::vec4 ResourceMaterial::GetAmbientIntensity ()
{
	return this->m_AmbientIntensity;
}

double ResourceMaterial::GetShinninessFactor ()
{
	return this->m_ShinninessFactor;
}

void ResourceMaterial::SetAmbientIntensity (glm::vec4 ambientIntensity)
{
	this->m_AmbientIntensity = ambientIntensity;
}

void ResourceMaterial::SetShinninessFactor (double shinninessFactor)
{
	this->m_ShinninessFactor = shinninessFactor;
}



ResourcePoint::ResourcePoint (FileStream::FileStreamPtr fileStream)
{
	std::vector <glm::vec3> vertices;
	std::vector <short> interpValues;

	LoadDataIPC (fileStream->GetStream (), vertices, interpValues);

	this->SetVertices (vertices);
	this->SetInterpValues (interpValues);
}

void ResourcePoint::LoadDataIPC (FileStream::FStreamPtr stream, std::vector <glm::vec3> &vertices, std::vector <short> &interpValues)
{
	short v1, v2, v3, interpVal;

	stream->clear ();
	stream->seekg(0, stream->beg);

	while (*stream >> v1 >> v2 >> v3 >> interpVal)
	{
		vertices.push_back (glm::vec3 (v1, v2, v3));
		interpValues.push_back (interpVal);
	}
}

std::vector <glm::vec3> ResourcePoint::GetVertices ()
{
	return this->m_Vertices;
}

std::vector <short> ResourcePoint::GetInterpValues ()
{
	return this->m_InterpValues;
}

void ResourcePoint::SetVertices (std::vector <glm::vec3> vertices)
{
	this->m_Vertices =vertices;
}

void ResourcePoint::SetInterpValues (std::vector <short> interpValues)
{
	this->m_InterpValues = interpValues;
}


ResourceMesh::ResourceMesh (FileStream::FileStreamPtr fileStream)
{
	FileStream::FStreamPtr stream = fileStream->GetStream ();

	Primitives type = LoadPrimitivesTypeOBJ (stream);
	std::vector <glm::vec3> importedVertices = LoadVerticesOBJ (stream);
	std::vector <glm::vec2> importedTexCoords = LoadTexCoordsOBJ (stream);
	std::vector <short> vIndices, tIndices;
	LoadIndicesOBJ (type, stream, vIndices, tIndices);

	this->SetPrimitives (type);
	this->SetVertices (importedVertices);
	this->SetTexCoords (importedTexCoords);
	this->SetIndicesVertices (vIndices);
	this->SetIndicesTexCoords (tIndices);
}

Primitives ResourceMesh::LoadPrimitivesTypeOBJ (FileStream::FStreamPtr stream)
{
	Primitives primitives;
	std::string line, id;
	
	stream->clear ();
	stream->seekg(0, stream->beg);

	while (std::getline (*stream, line))
	{
		std::istringstream sstream;
		*stream >> id;
		if	(id == "l")
		{
			primitives = Line;
			break;
		}
		else if (id == "f")
		{
			primitives = Triangle;
			break;
		}
	}
	return primitives;
}

std::vector <glm::vec3> ResourceMesh::LoadVerticesOBJ (FileStream::FStreamPtr stream)
{
	std::vector <glm::vec3> vertices;
	std::string id, line;

	stream->clear ();
	stream->seekg(0, stream->beg);

	while (std::getline (*stream, line))
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

std::vector <glm::vec2> ResourceMesh::LoadTexCoordsOBJ (FileStream::FStreamPtr stream)
{
	std::vector <glm::vec2> texCoords;
	std::string id, line;

	stream->clear ();
	stream->seekg(0, stream->beg);

	while (std::getline (*stream, line))
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

void ResourceMesh::LoadIndicesOBJ (Primitives type, FileStream::FStreamPtr stream, std::vector <short> &indicesVertices, std::vector <short> &indicesTexCoords)
{
	std::string line, id;

	stream->clear ();
	stream->seekg(0, stream->beg);

	if (Triangle == type)
	{
		char sl1, sl2, sl3; // For the slashes between elements
		unsigned short i1, i2, i3, i4, i5, i6;
		while (std::getline (*stream, line))
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
		while (std::getline (*stream, line))
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

Primitives ResourceMesh::GetPrimitives ()
{
	return this->m_Primitives;
}

std::vector <glm::vec2> ResourceMesh::GetTexCoords ()
{
	return this->m_TexCoords;
}

std::vector <short> ResourceMesh::GetIndicesVertices ()
{
	return this->m_IndicesVertices;
}

std::vector <short> ResourceMesh::GetIndicesTexCoords ()
{
	return this->m_IndicesTexCoords;
}



void ResourceMesh::SetPrimitives (Primitives primitives)
{
	this->m_Primitives = primitives;
}

void ResourceMesh::SetTexCoords (std::vector <glm::vec2> texCoords)
{
	this->m_TexCoords = texCoords;
}

void ResourceMesh::SetIndicesVertices (std::vector <short> indicesVertices)
{
	this->m_IndicesVertices = indicesVertices;
}

void ResourceMesh::SetIndicesTexCoords (std::vector <short> indicesTexCoords)
{
	this->m_IndicesTexCoords = indicesTexCoords;
}*/