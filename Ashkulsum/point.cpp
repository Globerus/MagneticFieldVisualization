#include "stdafx.h"
#include "point.h"

Point::Point (std::string fileName)
{
	CgalInterp::SharedPtr cgal = boost::make_shared<CgalInterp> ();

	std::vector<glm::vec3> vertices;
	std::vector<short> interpValues;
	short numPoints;

	this->SetSupportedExtensions ();
	LoadPoints (fileName, vertices, interpValues, numPoints);

	this->SetNumPoints (numPoints);
	this->SetFileVertices (vertices);
	this->SetFileInterpValues (interpValues);
}

void Point::SetSupportedExtensions ()
{
	std::string supportedExtensions[] = {".ipc"};
	std::vector <std::string> supExt (begin(supportedExtensions), end (supportedExtensions));

	this->m_SupportedExtensions = supExt;
}

void Point::LoadPoints (std::string fileName, std::vector<glm::vec3> &vertices, std::vector<short> &interpValues, short &numPoints)
{
	std::string extension = boost::filesystem::extension (fileName);

	if (this->IsFileSupported (extension))
	{
		std::string fullDirPath = Utils::GetFullDirPath (fileName);

		std::ifstream stream (fullDirPath, std::ios::in);
		if (stream.is_open ())
		{
			short v1, v2, v3, interpVal;
			std::string line;
			stream.clear ();
			stream.seekg(0, stream.beg);
			while (std::getline (stream, line))
			{
				std::istringstream sstream (line);

				if (sstream >> v1 >> v2 >> v3 >> interpVal)
				{
					vertices.push_back (glm::vec3 (v1, v2, v3));
					interpValues.push_back (interpVal);				
				}
				else
				{
					sstream.clear ();
					std::string dummy;
					sstream >> dummy >> numPoints;
				}
			}
		}
		else
			throw std::invalid_argument ("Error while opening the file! File not found");

		stream.close ();
	}
	else
		throw std::invalid_argument ("Error while opening the file! Unsupported format");
}

void Point::GeneratePoints ()
{
	short numPoints = this->GetNumPoints ();

	std::vector<glm::vec3> newVertices;
	srand((unsigned int) time(NULL));
	for (signed int i =0; i< numPoints; i++)
	{
		double x = Utils::GenerateRandomDouble (0.0, 20.0);
		double y = Utils::GenerateRandomDouble (-20.0, 20.0);
		double z = Utils::GenerateRandomDouble (-20.0, 20.0);
		newVertices.push_back (glm::vec3(x, y, z));
	}
	
	SetRuntimeVertices (newVertices);
}
void Point::ProcessPoints ()
{
	boost::asio::io_service io_service_;
	boost::thread_group thread_group;

	CgalInterp::SharedPtr cgal = boost::make_shared <CgalInterp> ();
	SetCgalPtr (cgal);
	cgal->InitPointMap (GetFileVertices (), GetFileInterpValues ());
	cgal->CreateDelaunayTriangle (GetFileVertices ());
	MultiThread::ProcessFunction (&CgalInterp::InterpolatePoint, cgal, GetRuntimeVertices ());
}

void Point::SetFileVertices (std::vector<glm::vec3> vertices)
{
	this->m_FileVertices = vertices;
}

void Point::SetFileInterpValues (std::vector<short> interpValues)
{
	this->m_FileInterpValues = interpValues;
}

void Point::SetRuntimeVertices (std::vector<glm::vec3> vertices)
{
	this->m_RuntimeVertices = vertices;
}


void Point::SetNumPoints (short numPoints)
{
	this->m_NumPoints = numPoints;
}

void Point::SetCgalPtr (CgalInterp::SharedPtr cgal)
{
	this->m_CgalPtr = cgal;
}



std::vector<glm::vec3> Point::GetFileVertices ()
{
	return this->m_FileVertices;
}

std::vector<short> Point::GetFileInterpValues ()
{
	return this->m_FileInterpValues;
}

std::vector<glm::vec3> Point::GetRuntimeVertices ()
{
	return this->m_RuntimeVertices;
}

short Point::GetNumPoints ()
{
	return this->m_NumPoints;
}

CgalInterp::SharedPtr Point::GetCgalPtr ()
{
	return this->m_CgalPtr;
}