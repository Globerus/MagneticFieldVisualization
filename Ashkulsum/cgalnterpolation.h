#ifndef CGAL_INTERPOLATION_H
#define CGAL_INTERPOLATION_H

#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\interpolation_functions.h>
#include <CGAL\natural_neighbor_coordinates_3.h>
#include <CGAL\Delaunay_triangulation_3.h>
#include <CGAL\Triangulation_face_base_with_info_2.h>
#include <boost\thread\thread.hpp>
#include <vector>
#include <map>
#include <glm\glm.hpp>
#include <boost\make_shared.hpp>
#include <boost\shared_ptr.hpp>

class CgalInterp
{
public:
	struct Compare
	{
		bool operator()(const glm::vec3 v1, const glm::vec3 v2)
		{
			if(v1.x < v2.x) return true;
			else if(v1.x == v2.x) 
			{
				if(v1.y < v2.y) return true;
				else if(v1.y == v2.y) 
					if(v1.z < v2.z) return true;	
			}
			return false;
		}
	};

	typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
	typedef K::FT	Coord_type;
	typedef CGAL::Delaunay_triangulation_3<K, CGAL::Fast_location> Delaunay_triangulation3;
	
	typedef K::Point_3	Point3;
	typedef Delaunay_triangulation3::Vertex_handle Vertex_handle;
	typedef std::map<Point3, Coord_type, K::Less_xyz_3> PointMap;
	typedef std::vector<std::pair< Point3, Coord_type >> PointVector;
	typedef std::vector<std::pair< Vertex_handle, Coord_type >> VHandleVector;
	typedef CGAL::Data_access<std::map<Point3, Coord_type, K::Less_xyz_3>>	value_access_t;
	typedef std::map<glm::vec3, double, Compare> VecMap;

	typedef boost::shared_ptr<CgalInterp> SharedPtr;
	typedef boost::shared_ptr<PointMap> PointMapPtr;
	typedef boost::shared_ptr<Delaunay_triangulation3> DelaunayPtr;
	typedef boost::shared_ptr<PointVector> PVecPtr;

	void InterpolatePoint (glm::vec3 vertex);

	PointMapPtr ConvertVecToPoint3 (std::vector<glm::vec3> vertices, std::vector<short> interpValues);
	PointVector ConvertVertexHandleToPoint3 (VHandleVector vHandleVector);

	DelaunayPtr CreateDelaunayTriangle (std::vector<glm::vec3> vertices);
	PointMapPtr InitPointMap (std::vector<glm::vec3> vertices, std::vector<short> interpValues);

	PointMapPtr GetPointMap ();
	DelaunayPtr GetDelaunayTriangle ();

private:
	DelaunayPtr m_DelaunayTr;
	PointMapPtr m_PointMap;
	VecMap m_VecMap;
	boost::mutex m_Mutex;

};


#endif