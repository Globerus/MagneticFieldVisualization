#ifndef LOAD_H
#define LOAD_H

#include "geometryNode.h"
#include "oglProgramFactory.h"
#include "pathEnvironment.h"
#include "visualEffect.h"
#include "cgalInterpolationSimulator.h"
#include "bezierCurve.h"
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <array>
#include "maths.h"

struct Attributes 
{
	std::vector <unsigned int> m_Indices;
	std::vector <glm::vec3> m_Vertices;
	std::vector <glm::vec2> m_TexCoords;
};

struct ListAtt 
{
	unsigned int m_ListVertex;
	unsigned int m_ListTex;
};

std::vector<glm::vec3> LoadVertices (std::ifstream &stream);
std::vector<glm::vec2> LoadTexCoords (std::ifstream &stream);
Attributes ComputeCoords (int const& primitive, VertexAttributes const& vAttrib, std::ifstream &stream);
std::shared_ptr<GeometryNode> LoadMesh (std::string const& name);
std::shared_ptr<GeometryNode> LoadLine (std::string const& name);
std::shared_ptr<GeometryNode> LoadVolumetricLine (std::vector<glm::vec3> points, int numSegments);
std::shared_ptr<GeometryNode> LoadParticles (int interpolatedPoints);

#endif