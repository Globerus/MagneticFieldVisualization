#include "stdafx.h"
#include "cgalInterpolationSimulator.h"


CGALInterpolationSimulator::CGALInterpolationSimulator ()
	:	m_MaxMagFieldForce (0),
		m_NumPoints (0),
		m_NumSegments (0),
		m_InterpolationDone (true)
{
	InsertCoordinatesAndValues ("data\\coordinates\\coordinates.txt");
	
	for (int i =0; i < m_NumPoints; i++)
	{
		glm::vec3 point (m_Initialization3DPointList[3*i], m_Initialization3DPointList[3*i+1], m_Initialization3DPointList[3*i+2]);
		Point3D cgalPoint (point.x, point.y, point.z);
		m_DelaunayTriangulation3D.insert (cgalPoint);
	}
	m_InterpolatedGLMPointMagForceVector.resize (m_NumPoints);
}

void CGALInterpolationSimulator::InsertCoordinatesAndValues (std::string name)
{
	PathEnvironment pathEnvironment;
	std::string pathDir = pathEnvironment.GetExeDir ();
	std::string pathName = pathDir + name;

	std::ifstream stream (pathName, std::ios::in);

	std::string line;

	stream.clear ();
	stream.seekg(0, stream.beg);
	int row = 0;
	std::vector<glm::vec3> coords;
	std::vector<double> values;

	while (std::getline (stream, line))
	{
		std::istringstream sstream (line);
		std::string id;

		sstream >> id;

		if (id == "r")
		{
			sstream >> m_NumPoints;
		}
		else if (id == "s")
		{
			sstream >> m_NumSegments;
		}
		else if (id == "m")
		{
			sstream >> m_MaxMagFieldForce;
		}
		else
		{
			glm::vec3 point;
			point.x = std::stof (id.c_str());
			sstream >> point.y >> point.z;

			coords.push_back (point);

			float num;
			while (sstream>>num)
			{
				values.push_back (num);
			}
		}
	}

	m_Initialization3DPointList = new float [m_NumPoints * 3];
	m_InitializationMagForceList = new double [m_NumPoints * m_NumSegments];

	for (int i = 0; i < m_NumPoints; i++)
	{
		auto point = coords[i];
		m_Initialization3DPointList[i * 3] = point.x;
		m_Initialization3DPointList[i * 3 + 1] = point.y;
		m_Initialization3DPointList[i * 3 + 2] = point.z;
	}

	for (int i = 0; i < m_NumPoints; i++)
	{	
		for (int j = 0; j < m_NumSegments; j++)
		{
			auto value = values[i * m_NumSegments + j];
			m_InitializationMagForceList[i * m_NumSegments + j] = value;
		}
	}
}

void CGALInterpolationSimulator::InitializeMagForceValues (int segmentSet)
{
	for (int i =0; i < m_NumPoints; i++)
	{
		glm::vec3 point (m_Initialization3DPointList[3*i], m_Initialization3DPointList[3*i+1], m_Initialization3DPointList[3*i+2]);
		Point3D cgalPoint (point.x, point.y, point.z);
		m_Initial3DPointMagForceMap[cgalPoint] = m_InitializationMagForceList[i*m_NumSegments + segmentSet];
	}
};

void CGALInterpolationSimulator::InterpolateMagForce (int segmentSet, glm::vec3 point)
{
	CoordType norm;
	VertexHandleVector vertexHandleVector;
	Point3DVector point3DVector;

	Point3D cgalPoint (point.x, point.y, point.z);

	m_LastVisitedCell = m_DelaunayTriangulation3D.locate (cgalPoint, m_LastVisitedCell);
	try
	{
		CGAL::sibson_natural_neighbor_coordinates_3 (m_DelaunayTriangulation3D, cgalPoint, std::back_inserter(vertexHandleVector), norm, m_LastVisitedCell);
	
		for (unsigned int i = 0; i < vertexHandleVector.size (); i++)
		{
			Point3D cgalP = vertexHandleVector[i].first->point();
			point3DVector.push_back (std::make_pair (cgalP, vertexHandleVector[i].second));
		}

		CoordType interpolationResult = CGAL::linear_interpolation (point3DVector.begin(), point3DVector.end(), norm, ValueAccess(m_Initial3DPointMagForceMap));

		m_InterpolatedGLMPointMagForceVector[segmentSet].push_back (glm::vec4 ( point, CGAL::to_double (interpolationResult)/ m_MaxMagFieldForce));
	}
	catch (const std::exception & e)
	{
		(void)e;
		m_InterpolatedGLMPointMagForceVector[segmentSet].push_back (glm::vec4 ( point, 0.0f));
		return;
	}
}

CGALInterpolationSimulator::GLMPointMap CGALInterpolationSimulator::GetInterpolatedGLMPointMagForceMap () const
{
	return m_InterpolatedGLMPointMagForceMap;
}

std::vector<std::vector<glm::vec4>> CGALInterpolationSimulator::GetInterpolatedGLMPointMagForceVector () const
{
	return m_InterpolatedGLMPointMagForceVector;
}

void CGALInterpolationSimulator::SetInterpolatedGLMPointMagForceVector (std::vector<std::vector<glm::vec4>> data)
{
	m_InterpolatedGLMPointMagForceVector = data;
}

CGALInterpolationSimulator::Point3DMap CGALInterpolationSimulator::GetInitial3DPointMagForceMap () const
{
	return m_Initial3DPointMagForceMap;
}

void CGALInterpolationSimulator::SetInitial3DPointMagForceMap (Point3DMap pointMap)
{
	m_Initial3DPointMagForceMap = pointMap;
}

void CGALInterpolationSimulator::SetInterpolationDone (bool status)
{
	m_InterpolationDone = status;
}

bool CGALInterpolationSimulator::GetInterpolationDone () const
{
	return m_InterpolationDone;
}

int CGALInterpolationSimulator::GetNumPoints () const
{
	return m_NumPoints;
}

int CGALInterpolationSimulator::GetNumSegments () const
{
	return m_NumSegments;
}

