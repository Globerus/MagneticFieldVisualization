#include "loader.h"

class Interpolator : public Loader
{
public:
	Interpolator ();
	~Interpolator ();

	void LoadPoints (const std::string path);
	void GeneratePoints ();
	void InterpolateByThread ();
	void Push_job (boost::asio::io_service *io_service_, int i, std::vector <glm::vec3> openglAdditionalCoordinateSet);
	std::vector <std::pair< Point3, Coord_type >> ConvertVertexHandleToPoint3 (std::vector <std::pair< Vertex_handle, Coord_type >> coordsVertex);
	void Interpolate ( int i, std::vector <glm::vec3> openglAdditionalCoordinateSet);
	glm::vec4 DecodeColour (double value);
	void ProcessPoints (const std::string path);
	double GenerateRandomDouble (double min, double max);

	void SetDelaunay ( Delaunay_triangulation3 delaunay_tr);
	void SetCgalInitialDataSet (std::map<Point3, Coord_type, K::Less_xyz_3> cgalInitialDataSet);
	void SetOpenglInitialDataSet (std::vector <std::pair <glm::vec3, double>> openglInitialDataSet);
	void SetOpenglAdditionalCoordinateSet (std::vector <glm::vec3> openglAdditionalCoordinateSet);
	void SetOpenglAdditionalValueSet (std::vector <glm::vec4> openglAdditionalValueSet);

	Delaunay_triangulation3 GetDelaunay ();
	std::map<Point3, Coord_type, K::Less_xyz_3> GetCgalInitialDataSet ();
	std::vector <std::pair <glm::vec3, double>> GetOpenglInitialDataSet ();
	std::vector <glm::vec3> GetOpenglAdditionalCoordinateSet ();
	std::vector <glm::vec4> GetOpenglAdditionalValueSet ();
private:
	Delaunay_triangulation3 delaunay_tr;
	std::map<Point3, Coord_type, K::Less_xyz_3> cgalInitialDataSet;
	std::vector <std::pair <glm::vec3, double>> openglInitialDataSet;
	std::vector <glm::vec3> openglAdditionalCoordinateSet;
	std::vector <glm::vec4> openglAdditionalValueSet;
	
};