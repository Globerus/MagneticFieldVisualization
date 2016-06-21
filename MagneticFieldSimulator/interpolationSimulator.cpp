#include "stdafx.h"
#include "interpolationSimulator.h"


InterpolationSimulator::InterpolationSimulator ()
	:	m_MaxMagFieldForce (0),
		m_NumPoints (0),
		m_NumSegments (0),
		m_InterpolationDone (true),
		m_InterpolationEngine (InterpolationSimulator::Embedded)

{
	InsertCoordinatesAndValues ("data\\coordinates\\coordinates.txt");
	m_InterpolatedGLMPointMagForceVector.resize (m_NumPoints);
}

void InterpolationSimulator::InsertCoordinatesAndValues (std::string name)
{
	PathEnvironment pathEnvironment;
	std::string pathDir = pathEnvironment.GetExeDir ();
	std::string pathName = pathDir + name;

	try
	{
		std::ifstream stream (pathName, std::ios::in);

		std::string line;

		stream.clear ();
		stream.seekg(0, stream.beg);

		std::vector<glm::vec3> coords;
		std::vector<double> values;

		while (std::getline (stream, line))
		{
			std::istringstream sstream (line);
			std::string id;

			sstream >> id;

			if (id == "e")
			{	
				std::string typeEngine;
				sstream >> typeEngine;
				m_InterpolationEngine = typeEngine == "Embedded" ? InterpolationSimulator::Embedded : InterpolationSimulator::CGAL;
			}
			else if (id == "r")
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
	catch (const std::exception & e)
	{
		(void)e;
		fprintf (stderr, "The data in the coordinates file is not correct. \n");
	}
}

void InterpolationSimulator::InitializeMagForceValuesCGAL (int segmentSet)
{
	for (int i =0; i < m_NumPoints; i++)
	{
		glm::vec3 point (m_Initialization3DPointList[3*i], m_Initialization3DPointList[3*i+1], m_Initialization3DPointList[3*i+2]);
		Point3D cgalPoint (point.x, point.y, point.z);
		m_Initial3DPointMagForceMap[cgalPoint] = m_InitializationMagForceList[i*m_NumSegments + segmentSet];
		}
};

void InterpolationSimulator::InitDelaunayTriangulationCGAL ()
{
	for (int i =0; i < m_NumPoints; i++)
		{
			glm::vec3 point (m_Initialization3DPointList[3*i], m_Initialization3DPointList[3*i+1], m_Initialization3DPointList[3*i+2]);
			Point3D cgalPoint (point.x, point.y, point.z);
			m_DelaunayTriangulation3D.insert (cgalPoint);
		} 
}

void InterpolationSimulator::InitDelaunayTriangulationEmbedded (int segmentSet)
{
	std::vector<glm::vec3> points;
	std::vector<float> values;

	for (int i =0; i < m_NumPoints; i++)
	{
		glm::vec3 point (m_Initialization3DPointList[3*i], m_Initialization3DPointList[3*i+1], m_Initialization3DPointList[3*i+2]);
		float value (m_InitializationMagForceList[i*m_NumSegments + segmentSet]);
		points.push_back (point);
		values.push_back (value);
	} 
	auto pointSet = ReformatPoints (points, values, m_NumPoints);
	m_DelaunayTriangulationEmbedded = NewDelaunayTriangulation ();
	BuildDelaunayTriangulation (pointSet, m_NumPoints, m_DelaunayTriangulationEmbedded);
}

void InterpolationSimulator::DeleteDelaunayTriangulationEmbedded ()
{
	FreeDelaunayTriangulation (m_DelaunayTriangulationEmbedded);
}

void InterpolationSimulator::InterpolateMagForceCGAL (int segmentSet, glm::vec3 point)
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

void InterpolationSimulator::InterpolateMagForceEmbedded (int segmentSet, glm::vec3 point)
{
	try
	{
		auto interpolationResult = NaturalNeighbourInterpolation (point, m_DelaunayTriangulationEmbedded);
		m_InterpolatedGLMPointMagForceVector[segmentSet].push_back (glm::vec4 ( point, interpolationResult/ m_MaxMagFieldForce));
	}
	catch (const std::exception & e)
	{
		(void)e;
		m_InterpolatedGLMPointMagForceVector[segmentSet].push_back (glm::vec4 ( point, 0.0f));
		return;
	}
}

std::vector<std::vector<glm::vec4>> InterpolationSimulator::GetInterpolatedGLMPointMagForceVector () const
{
	return m_InterpolatedGLMPointMagForceVector;
}

void InterpolationSimulator::SetInterpolatedGLMPointMagForceVector (std::vector<std::vector<glm::vec4>> data)
{
	m_InterpolatedGLMPointMagForceVector = data;
}

InterpolationSimulator::Point3DMap InterpolationSimulator::GetInitial3DPointMagForceMap () const
{
	return m_Initial3DPointMagForceMap;
}

void InterpolationSimulator::SetInitial3DPointMagForceMap (Point3DMap pointMap)
{
	m_Initial3DPointMagForceMap = pointMap;
}

void InterpolationSimulator::SetInterpolationDone (bool status)
{
	m_InterpolationDone = status;
}

bool InterpolationSimulator::GetInterpolationDone () const
{
	return m_InterpolationDone;
}

int InterpolationSimulator::GetNumPoints () const
{
	return m_NumPoints;
}

int InterpolationSimulator::GetNumSegments () const
{
	return m_NumSegments;
}

bool InterpolationSimulator::IsCGALEngine () const
{
	return m_InterpolationEngine == CGAL;
}
