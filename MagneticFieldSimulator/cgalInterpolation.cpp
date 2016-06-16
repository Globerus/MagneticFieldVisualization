#include "stdafx.h"
#include "cgalnterpolation.h"

void CgalInterp::InterpolatePoint (glm::vec3 vertex)
{
	Coord_type norm;
	VHandleVector vHandleVector;
	PointVector pointVector;

	boost::unique_lock <boost::mutex> uniqueLock (this->m_Mutex);
	PointMapPtr pointMap = this->GetPointMap ();
	DelaunayPtr delaunayPtr = this->GetDelaunayTriangle ();	
	uniqueLock.unlock ();

	Point3 cgalPoint (vertex.x, vertex.y, vertex.z);
	CGAL::sibson_natural_neighbor_coordinates_3 (*delaunayPtr.get(), cgalPoint, std::back_inserter(vHandleVector), norm);
	if (norm > 0)
	{
		pointVector = ConvertVertexHandleToPoint3(vHandleVector);
		Coord_type interpolationResult = CGAL::linear_interpolation (pointVector.begin(), pointVector.end(), norm, value_access_t(*pointMap.get()));
		double value =  CGAL::to_double (interpolationResult);

		uniqueLock.lock ();
		this->m_VecMap[vertex] = value;
		uniqueLock.unlock ();
	}
}

CgalInterp::PointMapPtr CgalInterp::InitPointMap (std::vector<glm::vec3> vertices, std::vector<short> interpValues)
{
	PointMap tempMap;
	if (vertices.size () == interpValues.size ())
	{
		for (unsigned int i = 0; i < vertices.size (); i++)
		{
			short interpVal = interpValues.at (i);
			glm::vec3 vertex = vertices.at (i);
			Point3 cgalPoint (vertex.x, vertex.y, vertex.z);
			tempMap[cgalPoint] = interpVal;
		}
	}
	PointMapPtr pointMap = boost::make_shared<PointMap> (tempMap);

	this->m_PointMap = pointMap;
	
	return pointMap;
}

CgalInterp::DelaunayPtr CgalInterp::CreateDelaunayTriangle (std::vector<glm::vec3> vertices)
{
	Delaunay_triangulation3 delaunay_tr;
	for (unsigned int i =0; i < vertices.size (); i++)
	{
		glm::vec3 vertex = vertices.at (i);
		Point3 cgalPoint (vertex.x, vertex.y, vertex.z);
		delaunay_tr.insert (cgalPoint);
	}
	DelaunayPtr delaunayPtr = boost::make_shared<Delaunay_triangulation3> (delaunay_tr);
	

	this->m_DelaunayTr = delaunayPtr;
	
	return delaunayPtr;
}

CgalInterp::PointMapPtr CgalInterp::ConvertVecToPoint3 (std::vector<glm::vec3> vertices, std::vector<short> interpValues)
{
	PointMap pointMap;
	if (vertices.size () == interpValues.size ())
	{
		for (unsigned int i = 0; i < vertices.size (); i++)
		{
			glm::vec3 vertex (vertices.at (i));
			short interpValue = interpValues.at (i);
			Point3 cgalPoint (vertex.x, vertex.y, vertex.z);
			pointMap[cgalPoint] = interpValue;
		}
	}
	else
		throw std::invalid_argument ("Error while generating points!");
	
	return boost::make_shared<PointMap> (pointMap);
}

CgalInterp::PointVector  CgalInterp::ConvertVertexHandleToPoint3 (CgalInterp::VHandleVector vHandleVector)
{
	PointVector pointVector;	

	for (unsigned int i = 0; i<vHandleVector.size (); i++)
	{
		std::pair< Vertex_handle, Coord_type > vHandlePair = vHandleVector.at(i);
		Vertex_handle vHandle= vHandlePair.first;
		Point3 point = vHandle->point();
		std::pair<Point3, Coord_type> pointPair = std::make_pair (point, vHandlePair.second);
		pointVector.push_back(pointPair);
	}

	return pointVector;
}

CgalInterp::PointMapPtr CgalInterp::GetPointMap ()
{
	return this->m_PointMap;
}

CgalInterp::DelaunayPtr CgalInterp::GetDelaunayTriangle ()
{
	return this->m_DelaunayTr;
}









