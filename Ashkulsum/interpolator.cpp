#include "stdafx.h"
#include "interpolator.h"

boost::mutex mutex_;
int counter;

Interpolator::Interpolator (){}
Interpolator::~Interpolator (){}

void Interpolator::SetDelaunay ( Delaunay_triangulation3 delaunay_tr)
{
	this->delaunay_tr = delaunay_tr;
}

void Interpolator::SetCgalInitialDataSet (std::map<Point3, Coord_type, K::Less_xyz_3> cgalInitialDataSet)
{
	this->cgalInitialDataSet = cgalInitialDataSet;
}

void Interpolator::SetOpenglInitialDataSet (std::vector <std::pair <glm::vec3, double>> openglInitialDataSet)
{
	this->openglInitialDataSet = openglInitialDataSet;
}

void Interpolator::SetOpenglAdditionalCoordinateSet (std::vector <glm::vec3> openglAdditionalCoordinateSet)
{
	this->openglAdditionalCoordinateSet = openglAdditionalCoordinateSet;
}

void Interpolator::SetOpenglAdditionalValueSet (std::vector <glm::vec4> openglAdditionalValueSet)
{
	this->openglAdditionalValueSet = openglAdditionalValueSet;
}

Delaunay_triangulation3 Interpolator::GetDelaunay ()
{
	return this->delaunay_tr;
}

std::map<Point3, Coord_type, K::Less_xyz_3> Interpolator::GetCgalInitialDataSet ()
{
	return this->cgalInitialDataSet;
}

std::vector <std::pair <glm::vec3, double>> Interpolator::GetOpenglInitialDataSet ()
{
	return this->openglInitialDataSet;
}

std::vector <glm::vec3> Interpolator::GetOpenglAdditionalCoordinateSet ()
{
	return this->openglAdditionalCoordinateSet;
}

std::vector <glm::vec4> Interpolator::GetOpenglAdditionalValueSet ()
{
	return this->openglAdditionalValueSet;
}

std::vector <std::pair< Point3, Coord_type >>  Interpolator::ConvertVertexHandleToPoint3 (std::vector <std::pair< Vertex_handle, Coord_type >> coordsVertex)
{
	std::vector< std::pair< Point3, Coord_type > > coordsPoint;		
	for (unsigned int i = 0; i<coordsVertex.size (); i++)
	{
		std::pair< Vertex_handle, Coord_type > A = coordsVertex.at(i);
		Vertex_handle vertex = A.first;
		Point3 poind = vertex->point();
		std::pair<Point3, Coord_type> Pair = std::make_pair (poind, A.second);
		coordsPoint.push_back(Pair);
	}
	return coordsPoint;

}

glm::vec4 Interpolator::DecodeColour (double value)
{
	double red = 1.0;
	double green = 1.0;
	double blue = 1.0;

	if (value >= 0 && value < 2.5)
	{
		red = 0.0;
		green = (1/2.5)*value;
		blue = 1.0;
	}
	else if (value >= 2.5 && value < 5)
	{
		red = 0.0;
		green = 1.0;
		blue = 1 - (1/2.5)*(value - 2.5);
	}
	else if (value >= 5 && value < 7.5)
	{
		red = (1/2.5) * (value - 5);
		green = 1.0;
		blue = 0.0;
	}
	else if (value >= 7.5 && value <=10)
	{
		red = 1.0;
		green = 1 - (1/2.5) * (value - 7.5);
		blue = 0.0;
	}
	return glm::vec4 (red, green, blue, 1.0);
}	

double Interpolator::GenerateRandomDouble (double min, double max)
{
	double random = ((double) rand()) / (double) RAND_MAX;
	double diff = max - min;
	double r = random * diff;
	return r + min;
}
void  Interpolator::Interpolate ( int i, std::vector <glm::vec3> openglAdditionalCoordinateSet)
{
	Delaunay_triangulation3 Delaunay_tr = GetDelaunay ();
	std::map<Point3, Coord_type, K::Less_xyz_3> cgalInitialDataSet = GetCgalInitialDataSet ();
	

	glm::vec3 coordinate = openglAdditionalCoordinateSet.at (i);
	Point3 cgalPoint (coordinate.x, coordinate.y, coordinate.z);
	typedef CGAL::Data_access<std::map<Point3, Coord_type, K::Less_xyz_3>>	value_access_t;
	Coord_type norm;

	std::vector< std::pair< Vertex_handle, Coord_type > > coordsVertex;
	CGAL::sibson_natural_neighbor_coordinates_3 (Delaunay_tr, cgalPoint, std::back_inserter(coordsVertex), norm);
	std::vector< std::pair< Point3, Coord_type > > coordsPoint = ConvertVertexHandleToPoint3(coordsVertex);
	Coord_type interpolationResult = CGAL::linear_interpolation (coordsPoint.begin(), coordsPoint.end(), norm, value_access_t(cgalInitialDataSet));
	double double_result = CGAL::to_double (interpolationResult);
	glm::vec4 colour = DecodeColour (double_result);
	boost::unique_lock <boost::mutex> lock (mutex_);
	std::vector <glm::vec4> openglAdditionalValueSet = GetOpenglAdditionalValueSet ();
	openglAdditionalValueSet.at (i) = colour;
	SetOpenglAdditionalValueSet (openglAdditionalValueSet);	
	lock.unlock();
	++counter;
	std::vector <glm::vec4>().swap (openglAdditionalValueSet);
	std::vector <std::pair< Point3, Coord_type > >().swap (coordsPoint);
	std::map<Point3, Coord_type, K::Less_xyz_3>().swap (cgalInitialDataSet);
}

void Interpolator::Push_job (boost::asio::io_service *io_service_, int i, std::vector <glm::vec3> openglAdditionalCoordinateSet)
{				
	io_service_->post (boost::bind (&Interpolator::Interpolate, this, i, openglAdditionalCoordinateSet));	
}

void Interpolator::GeneratePoints ()
{
	std::vector <glm::vec3> openglAdditionalCoordinateSet = GetOpenglAdditionalCoordinateSet ();
	srand((unsigned int) time(NULL));
	for (signed int i =0; i< number_of_points; i++)
	{
		double x = GenerateRandomDouble (0.0, 20.0);
		double y = GenerateRandomDouble (-20.0, 20.0);
		double z = GenerateRandomDouble (-20.0, 20.0);
		openglAdditionalCoordinateSet.push_back (glm::vec3(x, y, z));
	}
	SetOpenglAdditionalCoordinateSet (openglAdditionalCoordinateSet);
	std::vector <glm::vec3>().swap (openglAdditionalCoordinateSet);
}
void Interpolator::LoadPoints (const std::string Path)
{
	std::string strFilename = LOCAL_COORDINATE_DIR + Path;
	std::fstream iFile(strFilename, std::ios::in);

	Delaunay_triangulation3 delaunay_tr = GetDelaunay ();
	std::map<Point3, Coord_type, K::Less_xyz_3> cgalInitialDataSet = GetCgalInitialDataSet ();
	std::vector <std::pair <glm::vec3, double>> openglInitialDataSet = GetOpenglInitialDataSet ();

	Point3 p;
	Coord_type v;
	while ( iFile >> p >>v )
	{
		delaunay_tr.insert(p);
		cgalInitialDataSet.insert(std::make_pair(p, v));
		openglInitialDataSet.push_back (std::make_pair (glm::vec3 (CGAL::to_double (p.x()), CGAL::to_double (p.y()), CGAL::to_double (p.z())), CGAL::to_double (v)));
	}
	SetDelaunay (delaunay_tr);
	SetCgalInitialDataSet (cgalInitialDataSet);
	SetOpenglInitialDataSet (openglInitialDataSet);

	std::map<Point3, Coord_type, K::Less_xyz_3> ().swap (cgalInitialDataSet);
	std::vector <std::pair <glm::vec3, double>>().swap (openglInitialDataSet);
}
void Interpolator::InterpolateByThread ()
{
	boost::asio::io_service io_service_;
	boost::asio::io_service::work work_ (io_service_);
	boost::thread_group thread_group;
	
	std::string name = GetName ();
	counter = 0;
	std::vector <glm::vec3> openglAdditionalCoordinateSet = GetOpenglAdditionalCoordinateSet ();
	std::vector <glm::vec4> openglAdditionalValueSet = GetOpenglAdditionalValueSet ();
	openglAdditionalValueSet.resize (openglAdditionalCoordinateSet.size(), glm::vec4 (0));
	SetOpenglAdditionalValueSet (openglAdditionalValueSet);
	for (unsigned int r= 0; r<boost::thread::hardware_concurrency(); r++)
	{
		thread_group.create_thread (boost::bind (&boost::asio::io_service::run, &io_service_));
	}
	for (signed int i =0; i< number_of_points; i++)
	{
		Push_job (&io_service_, i, openglAdditionalCoordinateSet);
		double prcntg = ((double)counter/number_of_points)*100;
		if (!((int)prcntg % 5))
		{
		std::string text = "Interpolating " + name + " : " + std::to_string ((_ULonglong)prcntg) + " %";
		PrintLoadingText (text, textTextureAtlas, 3);
		}
	}
	do
	{
		double prcntg = ((double)counter/number_of_points)*100;
		if (!((int)prcntg % 5))
		{
		std::string text = "Interpolating " + name + " : " + std::to_string ((_ULonglong)prcntg) + " %";
		PrintLoadingText (text, textTextureAtlas, 3);	
		}
	}while (counter < number_of_points);

	io_service_.stop ();
	thread_group.join_all ();

	std::vector <glm::vec3>().swap (openglAdditionalCoordinateSet);
	std::vector <glm::vec4>().swap (openglAdditionalValueSet);
}



void Interpolator::ProcessPoints (const std::string path)
{
	Interpolator* self = this;
	self->LoadPoints (path);
	self->GeneratePoints ();
	self->InterpolateByThread ();
	self->SetDrawPrimitive (Points);
	std::vector <glm::vec3> coordinateSet = GetOpenglAdditionalCoordinateSet ();
	std::vector <glm::vec4> valueSet = GetOpenglAdditionalValueSet ();
	self->SetProcessedVertices (coordinateSet);
	self->SetProcessedColours (valueSet);
	self->GenerateBuffers ();

	std::vector <glm::vec3>().swap (coordinateSet);
	std::vector <glm::vec4>().swap (valueSet);
}