#ifndef RESOURCE_H
#define RESOURCE_H

#include "point.h"
#include "material.h"
#include "texture.h"
#include "mesh.h"
#include "light.h"
#include "font.h"
#include <string>

template <typename T>
class Resource 
{
public:
	typedef boost::shared_ptr <Resource<T>> SharedPtr;

	Resource (std::string fileName);

	void SetPtr (typename T::SharedPtr rsrcPtr);
	typename T::SharedPtr GetPtr ();

private:
	typename T::SharedPtr m_RsrcPtr;
};

template <typename T> 
Resource<T>::Resource (std::string fileName)
{
	typename T::SharedPtr rsrc = boost::make_shared <T> (fileName);
	this->SetPtr (rsrc);
}

template <typename T>
void Resource<T>::SetPtr (typename T::SharedPtr rsrcPtr)
{
	this->m_RsrcPtr = rsrcPtr;
}

template <typename T>
typename T::SharedPtr Resource<T>::GetPtr ()
{
	return this->m_RsrcPtr;
}


/*class Resource 
{
public:
	virtual ~Resource () {};

	typedef boost::shared_ptr <Resource> SharedPtr;

private:

};

class ResourceImage : public Resource 
{
public:
	ResourceImage () {};
	ResourceImage (FileStream::FileStreamPtr fileStream);

	~ResourceImage () {};

	typedef boost::shared_ptr <ResourceImage> SharedPtr;

	int GetImageWidth ();
	int GetImageHeight ();
	unsigned char* GetImageData ();
	
	void SetImageWidth (int width);
	void SetImageHeight (int height);
	void SetImageData (unsigned char* imageData);

private:
	unsigned char* m_ImageData;
	int m_ImageWidth, m_ImageHeight;
};

class ResourceFont : public ResourceImage 
{
public:
	ResourceFont () {};
	ResourceFont (FileStream::FileStreamPtr fileStream);

	~ResourceFont () {};

	typedef boost::shared_ptr <ResourceFont> SharedPtr;

private:

};

class ResourceLight : public Resource 
{
public:
	ResourceLight () {};
	ResourceLight (FileStream::FileStreamPtr fileStream);

	~ResourceLight () {};

	typedef boost::shared_ptr <ResourceLight> SharedPtr;
	
	void LoadLightParam (FileStream::FStreamPtr stream, glm::vec4 &lightIntensity, glm::vec3 &lightPosition, double &lightAttenuation);

	void SetLightItensity (glm::vec4 lightIntensity);
	void SetLightPosition (glm::vec3 lightPosition);
	void SetLightAttenuation (double lightAttenuation);

	glm::vec4 GetLightIntensity ();
	glm::vec3 GetLightPosition ();
	double GetLightAttenuation ();

private:
	glm::vec4 m_LightIntensity;
	glm::vec3 m_LightPosition;
	double m_LightAttenuation;
};

class ResourceMaterial : public Resource 
{
public:
	ResourceMaterial () {};
	ResourceMaterial (FileStream::FileStreamPtr fileStream);

	~ResourceMaterial () {};

	typedef boost::shared_ptr <ResourceMaterial> SharedPtr;
	
	void LoadMaterialParam (FileStream::FStreamPtr stream, glm::vec4 &ambientIntensity, double &shinninessFactor);

	void SetAmbientIntensity (glm::vec4 ambientIntensity);
	void SetShinninessFactor (double shinninessFactor);

	glm::vec4 GetAmbientIntensity ();
	double GetShinninessFactor ();

private:
	glm::vec4 m_AmbientIntensity;
	double m_ShinninessFactor;

};

class ResourcePoint : public Resource 
{
public:
	ResourcePoint () {};
	ResourcePoint (FileStream::FileStreamPtr fileStream);

	~ResourcePoint () {};

	typedef boost::shared_ptr <ResourcePoint> SharedPtr;
	
	void LoadDataIPC (FileStream::FStreamPtr stream, std::vector <glm::vec3> &vertices, std::vector <short> &interpValues);

	void SetVertices (std::vector <glm::vec3> vertices);
	void SetInterpValues (std::vector <short> interpValues);

	std::vector <glm::vec3> GetVertices ();
	std::vector <short> GetInterpValues ();

private:
	std::vector <glm::vec3> m_Vertices;
	std::vector <short> m_InterpValues;

};

class ResourceMesh : public ResourcePoint 
{
public:
	ResourceMesh () {};
	ResourceMesh (FileStream::FileStreamPtr fileStream);

	~ResourceMesh () {};

	typedef boost::shared_ptr <ResourceMesh> SharedPtr;
	
	Primitives LoadPrimitivesTypeOBJ (FileStream::FStreamPtr stream);
	std::vector <glm::vec3> LoadVerticesOBJ (FileStream::FStreamPtr stream);
	std::vector <glm::vec2> LoadTexCoordsOBJ (FileStream::FStreamPtr stream);
	void LoadIndicesOBJ (Primitives type, FileStream::FStreamPtr stream, std::vector <short> &indicesVertices, std::vector <short> &indicesTexCoords);

	void SetPrimitives (Primitives Primitives);
	void SetTexCoords (std::vector <glm::vec2> texCoords);
	void SetIndicesVertices (std::vector <short> indicesVertices);
	void SetIndicesTexCoords (std::vector <short> indicesTexCoords);

	Primitives GetPrimitives ();
	std::vector <glm::vec2> GetTexCoords ();
	std::vector <short> GetIndicesVertices ();
	std::vector <short> GetIndicesTexCoords ();

private:
	Primitives m_Primitives;
	std::vector <glm::vec2> m_TexCoords;
	std::vector <short> m_IndicesVertices, m_IndicesTexCoords;

};*/
#endif

