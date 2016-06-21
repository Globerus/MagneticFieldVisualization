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
#include "naturalNeighbourInterpolation.h"

class InterpolationSimulator 
{
public:

	enum EngineType 
	{
		CGAL,
		Embedded,
	};

	InterpolationSimulator ();

	typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
	typedef Kernel::FT	CoordType;
	typedef CGAL::Delaunay_triangulation_3<Kernel, CGAL::Fast_location> DelaunayTriangulation3D;

	typedef Kernel::Point_3	Point3D;
	typedef DelaunayTriangulation3D::Vertex_handle VertexHandle;
	typedef std::map<Point3D, CoordType, Kernel::Less_xyz_3> Point3DMap;
	
	typedef std::vector<std::pair< Point3D, CoordType >> Point3DVector;
	typedef std::vector<std::pair< VertexHandle, CoordType >> VertexHandleVector;
	typedef CGAL::Data_access<Point3DMap> ValueAccess;

	void InsertCoordinatesAndValues (std::string name);
	void InitializeMagForceValuesCGAL (int segmentSet);
	void InterpolateMagForceCGAL (int segmentSet, glm::vec3 point);
	void InitDelaunayTriangulationCGAL ();
	
	void InterpolateMagForceEmbedded (int segmentSet, glm::vec3 point);
	void InitDelaunayTriangulationEmbedded (int segmentSet);
	void DeleteDelaunayTriangulationEmbedded ();

	std::vector<std::vector<glm::vec4>> GetInterpolatedGLMPointMagForceVector () const;
	void SetInterpolatedGLMPointMagForceVector (std::vector<std::vector<glm::vec4>> data);

	Point3DMap GetInitial3DPointMagForceMap () const;
	void SetInitial3DPointMagForceMap (Point3DMap pointMap);

	int GetNumSegments () const;
	int GetNumPoints () const;

	bool IsCGALEngine () const;

	void SetInterpolationDone (bool status);
	bool GetInterpolationDone () const;
	
private:
	DelaunayTriangulation3D m_DelaunayTriangulation3D;
	DelaunayTriangulation3D::Cell_handle m_LastVisitedCell;
	Point3DMap m_Initial3DPointMagForceMap;

	DelaunayTriangulation* m_DelaunayTriangulationEmbedded;

	std::vector<std::vector<glm::vec4>> m_InterpolatedGLMPointMagForceVector;
	

	bool m_InterpolationDone;
	EngineType m_InterpolationEngine;

	int m_NumPoints, m_NumSegments, m_MaxMagFieldForce;
	float* m_Initialization3DPointList;
	double* m_InitializationMagForceList;
};
#endif