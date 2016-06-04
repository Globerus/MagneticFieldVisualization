#ifndef LOADER
#define LOADER
#include "SOIL.h"
#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\interpolation_functions.h>
#include <CGAL\natural_neighbor_coordinates_3.h>
#include <CGAL\Delaunay_triangulation_3.h>
#include <fstream>
#include <glload\gl_3_3.h>
#include <glload\gl_load.hpp>
#include <glutil\glutil.h>
#include <GL\freeglut.h>
#include <boost\asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost\lockfree\queue.hpp>
#include <boost\lockfree\stack.hpp>
#include "primitive.h"
//#include "resourceManager.h"

//enum Primitives {Points, Line, Triangle, Triangle_strip, Triangle_fan};

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::FT	Coord_type;
typedef CGAL::Delaunay_triangulation_3<K, CGAL::Fast_location> Delaunay_triangulation3;
typedef K::Point_3	Point3;
typedef Delaunay_triangulation3::Vertex_handle Vertex_handle;

//extern std::string LOCAL_SHADER_DIR;
extern std::string LOCAL_OBJECT_DIR;
extern std::string LOCAL_COORDINATE_DIR;
extern std::string LOCAL_TEXTURE_DIR;

extern int number_of_points;

extern void PrintLoadingText (const std::string text, GLuint text2DTexture, int texNum);
extern GLuint textTextureAtlas;
extern int loadingText_x;
extern int loadingText_y;
extern int loadingText_size;

class Loader 
{
public:

	Loader ();
	~Loader ();

	void LoadObjectVertices (const std::string path);
	void LoadObjectTexCoords (const std::string path);
	void LoadObjectIndices (const std::string path);
	void LoadObjectColours (const std::string path);

	void LoadObjectFile (const std::string path);
	void ProcessObject (const std::string path);

	
	

	void ProcessDrawPrimitive (const std::string path);

	void ActivateTexture (GLenum enumerator);
	void LoadTexture(const std::string path, GLenum enumerator);
	
	void ProcessVertices ();
	void ProcessTexCoords ();
	void ProcessColours ();

	void ProcessFaceNormals ();
	void ProcessVertexNormals ();

	void InitializeVertexBuffer ();
	void GenerateBuffers ();
	void Render ();

	// GET METHODS

	//interpolation
	

	//coordinates
	std::vector <glm::vec3> GetVertices ();
	std::vector <glm::vec2> GetTexCoords ();
	std::vector <glm::vec4> GetColours ();

	std::vector <GLshort> GetIndicesVertices ();
	std::vector <GLshort> GetIndicesTexCoords ();
	std::vector <GLshort> GetIndicesColours ();

	std::vector <glm::vec3> GetProcessedVertices();
	std::vector <glm::vec2> GetProcessedTexCoords();
	std::vector <glm::vec4> GetProcessedColours();

	std::vector <glm::vec3> GetFaceNormals();
	std::vector <glm::vec3> GetVertexNormals();	

	//buffers
	GLuint GetVertexBufferObject();
	GLuint GetColourBufferObject();
	GLuint GetNormalBufferObject();
	GLuint GetTextureBufferObject();
	GLuint GetShadowTextureObject();

	//array
	GLuint GetVao();

	Primitives GetDrawPrimitive();

	int GetTextureNum ();
	GLuint GetTexture ();

	std::string GetName ();

	// SET METHODS
	//interpolation
	

	//coordinates
	void SetVertices (std::vector <glm::vec3> vertices);
	void SetTexCoords (std::vector <glm::vec2> texCoords);
	void SetColours (std::vector <glm::vec4> colours);

	void SetIndicesVertices (std::vector <GLshort> indicesVertices);
	void SetIndicesTexCoords (std::vector <GLshort> indicesTexCoords);
	void SetIndicesColours (std::vector <GLshort> indicesColours);

	void SetProcessedVertices (std::vector <glm::vec3> processedVertices);
	void SetProcessedTexCoords (std::vector <glm::vec2> processedTexCoords);
	void SetProcessedColours (std::vector <glm::vec4> processedColours);

	void SetFaceNormals (std::vector <glm::vec3> faceNormals);
	void SetVertexNormals (std::vector <glm::vec3> vertexNormals);

	//buffers
	void SetVertexBufferObject (GLuint vertexBufferObject);
	void SetColourBufferObject (GLuint colourBufferObject);
	void SetNormalBufferObject (GLuint normalBufferObject);
	void SetTextureBufferObject (GLuint textureBufferObject);
	void SetShadowTextureObject (GLuint shadowBufferObject);

	//arrays
	void SetVao (GLuint vao);

	void SetDrawPrimitive (Primitives drawPrimitive);

	void SetTextureNum (int textureNum);
	void SetTexture (GLuint texture);

	void SetName (std::string name);

private:
	//interpolation

	//coordinates
	std::vector <glm::vec3> vertices;
	std::vector <glm::vec2> texCoords;
	std::vector <glm::vec4> colours;
	std::vector <GLshort> indicesVertices, indicesTexCoords, indicesColours;
	
	std::vector <glm::vec3> processedVertices;
	std::vector <glm::vec2> processedTexCoords;
	std::vector <glm::vec4> processedColours;
	std::vector <glm::vec3> faceNormals, vertexNormals;

	//buffers and arrays
	GLuint vao;
	GLuint vertexBufferObject, colourBufferObject, normalBufferObject, shadowTextureObject, textureBufferObject;

	Primitives drawPrimitive;

	// Texture
	int textureNum;
	GLuint texture;

	std::string name;
};
#endif