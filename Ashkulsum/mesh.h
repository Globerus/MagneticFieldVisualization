#ifndef MESH_H
#define MESH_H

#include "resourceBase.h"
#include "primitive.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <boost\filesystem.hpp>
#include "boost\shared_ptr.hpp"
#include <vector>
#include <glm\glm.hpp>

class Mesh : public ResourceBase
{
public:
	Mesh (std::string fileName);
	~Mesh () {};

	typedef boost::shared_ptr <Mesh> SharedPtr;

	void SetSupportedExtensions ();

	void LoadFile (std::string fileName, Primitives &type, std::vector <glm::vec3> &vertices, std::vector <glm::vec2> &texCoords, std::vector <short> &indicesVertices, std::vector <short> &indicesTexCoords, std::vector <glm::vec3> &faceNormals, std::vector <glm::vec3> &vertexNormals);

	Primitives LoadPrimitivesType (std::ifstream &stream);
	std::vector <glm::vec3> LoadVertices (std::ifstream &stream);
	std::vector <glm::vec2> LoadTexCoords (std::ifstream &stream);
	void LoadIndices (Primitives type, std::ifstream &stream, std::vector <short> &indicesVertices, std::vector <short> &indicesTexCoords);

	std::vector <glm::vec3> ProcessVertices (Primitives type, std::vector <glm::vec3> vertices, std::vector <short> indicesVertices);
	std::vector <glm::vec2> ProcessTexCoords (Primitives type, std::vector <glm::vec2> texCoords, std::vector <short> indicesTexCoords);
	std::vector <glm::vec3> GenerateFaceNormals (Primitives type, std::vector <glm::vec3> vertices, std::vector <short> indicesVertices);
	std::vector <glm::vec3> GenerateVertexNormals (Primitives type, std::vector <glm::vec3> faceNormals, std::vector <short> indicesVertices);

	// Getters and Setters
	Primitives GetPrimitives ();
	std::vector <glm::vec3> GetVertices ();
	std::vector <glm::vec3> GetVertexNormals ();
	std::vector <glm::vec3> GetFaceNormals ();
	std::vector <glm::vec2> GetTexCoords ();
	std::vector <short> GetIndicesVertices ();
	std::vector <short> GetIndicesTexCoords ();

	void SetPrimitives (Primitives Primitives);
	void SetVertices (std::vector <glm::vec3> vertices);
	void SetVertexNormals (std::vector <glm::vec3> vertexNormals);
	void SetFaceNormals (std::vector <glm::vec3> faceNormals);
	void SetTexCoords (std::vector <glm::vec2> texCoords);
	void SetIndicesVertices (std::vector <short> indicesVertices);
	void SetIndicesTexCoords (std::vector <short> indicesTexCoords);

private:
	Primitives m_Primitives;
	std::vector <glm::vec3> m_Vertices, m_VertexNormals, m_FaceNormals;
	std::vector <glm::vec2> m_TexCoords;
	std::vector <short> m_IndicesVertices, m_IndicesTexCoords;
};
#endif