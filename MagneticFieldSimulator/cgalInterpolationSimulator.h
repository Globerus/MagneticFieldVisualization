#ifndef CGAL_INTERPOLATION_SIMULATOR_H
#define CGAL_INTERPOLATION_SIMULATOR_H

#include "include.h"
#include <functional>
#include "maths.h"
#include <fstream>
#include <sstream>
#include "pathEnvironment.h"
#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\interpolation_functions.h>
#include <CGAL\natural_neighbor_coordinates_3.h>
#include <CGAL\Delaunay_triangulation_3.h>

class CGALInterpolationSimulator 
{
public:

	struct Vec3ComparisonFunc
	{
		bool operator() (glm::vec3 const& vecA, glm::vec3 const& vecB)
		{
			return vecA.x < vecB.x && vecA.y < vecB.y && vecA.z < vecB.z;
		}
	};

	CGALInterpolationSimulator ();

	typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
	typedef Kernel::FT	CoordType;
	typedef CGAL::Delaunay_triangulation_3<Kernel, CGAL::Fast_location> DelaunayTriangulation3D;

	typedef Kernel::Point_3	Point3D;
	typedef DelaunayTriangulation3D::Vertex_handle VertexHandle;
	typedef std::map<Point3D, CoordType, Kernel::Less_xyz_3> Point3DMap;
	typedef std::map<glm::vec3, float, Vec3ComparisonFunc> GLMPointMap;
	typedef std::vector<std::pair< Point3D, CoordType >> Point3DVector;
	typedef std::vector<std::pair< VertexHandle, CoordType >> VertexHandleVector;
	typedef CGAL::Data_access<Point3DMap> ValueAccess;

	void InsertCoordinatesAndValues (std::string name);
	void InitializeMagForceValues (int segmentSet);
	void InterpolateMagForce (int segmentSet, glm::vec3 point);
	
	GLMPointMap GetInterpolatedGLMPointMagForceMap () const;
	std::vector<std::vector<glm::vec4>> GetInterpolatedGLMPointMagForceVector () const;
	void SetInterpolatedGLMPointMagForceVector (std::vector<std::vector<glm::vec4>> data);

	Point3DMap GetInitial3DPointMagForceMap () const;
	void SetInitial3DPointMagForceMap (Point3DMap pointMap);

	int GetNumSegments () const;
	int GetNumPoints () const;

	void SetInterpolationDone (bool status);
	bool GetInterpolationDone () const;

private:
	DelaunayTriangulation3D m_DelaunayTriangulation3D;
	DelaunayTriangulation3D::Cell_handle m_LastVisitedCell;

	Point3DMap m_Initial3DPointMagForceMap;
	GLMPointMap m_InterpolatedGLMPointMagForceMap;
	std::vector<std::vector<glm::vec4>> m_InterpolatedGLMPointMagForceVector;
	
	bool m_InterpolationDone;

	int m_NumPoints, m_NumSegments, m_MaxMagFieldForce;
	float* m_Initialization3DPointList;
	double* m_InitializationMagForceList;
};
#endif