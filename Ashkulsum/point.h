#ifndef POINT_H
#define POINT_H

#include "resourceBase.h"
#include "multiThreading.h"
#include "utils.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <boost\shared_ptr.hpp>
#include <boost\make_shared.hpp>
#include <boost\filesystem.hpp>
#include <glm\glm.hpp>

class Point : ResourceBase
{
public:
	Point (std::string fileName);
	~Point () {};

	typedef boost::shared_ptr<Point> SharedPtr;

	void SetSupportedExtensions ();

	void LoadPoints (std::string fileName, std::vector<glm::vec3> &vertices, std::vector<short> &interpValues, short &numPoints);
	void GeneratePoints ();
	void ProcessPoints ();

	void SetFileVertices (std::vector<glm::vec3> vertices);
	void SetFileInterpValues (std::vector<short> interpValues);
	void SetRuntimeVertices (std::vector<glm::vec3> vertices);
	void SetNumPoints (short numPoints);
	void SetCgalPtr (CgalInterp::SharedPtr cgal);

	std::vector<glm::vec3> GetFileVertices ();
	std::vector<short> GetFileInterpValues ();
	std::vector<glm::vec3> GetRuntimeVertices ();
	short GetNumPoints ();
	CgalInterp::SharedPtr GetCgalPtr ();

	
private:
	CgalInterp::SharedPtr m_CgalPtr;
	std::vector<glm::vec3> m_FileVertices, m_RuntimeVertices;
	std::vector<short> m_FileInterpValues;
	short m_NumPoints;

};
#endif