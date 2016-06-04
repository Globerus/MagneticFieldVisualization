#ifndef CGAL_INTERPOLATION_SIMULATOR_H
#define CGAL_INTERPOLATION_SIMULATOR_H

#include "include.h"
#include <functional>
#include "maths.h"
#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\interpolation_functions.h>
#include <CGAL\surface_neighbor_coordinates_3.h>
#include <CGAL\natural_neighbor_coordinates_3.h>
#include <CGAL\Delaunay_triangulation_3.h>
#include <CGAL/Cartesian_d.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/point_generators_d.h>
#include <boost\asio.hpp>
#include <boost/thread.hpp>

class CGALInterpolationSimulator 
{
public:
	CGALInterpolationSimulator ();

	typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
	typedef Kernel::FT	CoordType;
	typedef CGAL::Delaunay_triangulation_3<Kernel, CGAL::Fast_location> DelaunayTriangulation3D;

	typedef Kernel::Point_3	Point3D;
	typedef DelaunayTriangulation3D::Vertex_handle VertexHandle;
	typedef std::map<Point3D, CoordType, Kernel::Less_xyz_3> Point3DMap;
	typedef std::map<Point3D, glm::vec3, Kernel::Less_xyz_3> Vec3DMap;
	typedef std::vector<std::pair< Point3D, CoordType >> Point3DVector;
	typedef std::vector<std::pair< VertexHandle, CoordType >> VertexHandleVector;
	typedef CGAL::Data_access<Point3DMap> ValueAccess;

	typedef CGAL::Cartesian_d<double> Kd;
	typedef Kd::Point_d Point;

	enum 
	{
		NUM_GENERATED_POINTS = 0,
		NUM_INITIALIZATION_POINTS = 1030//845
	};

	void InitThreadPool ();

	std::vector<glm::vec4> GeneratePoints ();
	std::vector<glm::vec3> GenerateStreamLine (int numSegments, float dt, glm::vec3 point);

	void InterpolateMagForce (glm::vec3 & point);
	glm::vec3 InterpolateDirVec (glm::vec3 & point);

	glm::vec3 WeightedVectorLinearInterpolation (Point3D cgalPoint, VertexHandleVector vector, CoordType norm);	
	glm::vec3 RungeKutta4 (float dt, glm::vec3 & point);

	std::vector<glm::vec4> m_Interpolated3DPointMagForceVector;
private:
	DelaunayTriangulation3D m_DelaunayTriangulation3D;

	Point3DMap m_Initial3DPointMagForceMap;
	

	//Point3DMap m_Initial3DPointDirVecMap;
	std::map<Point3D, glm::vec2> m_Initial3DPointDirVecMap;
	std::map<int, glm::vec3> m_StreamLineVertices;

	static int const m_NumPoints = NUM_INITIALIZATION_POINTS + NUM_GENERATED_POINTS;
	
	float m_Radius;
	float m_MaxMagFieldForce;

	boost::mutex m_Mutex;
	boost::asio::io_service m_IOService;
	boost::asio::io_service::work m_Work;
	boost::thread_group m_Pool;

	static float const m_Initialization3DPointList[];
	static double const m_InitializationMagForceList[];
	static float const m_InitializationDirVecList[];
};
#endif