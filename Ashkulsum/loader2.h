#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include "meshObject.h"
#include "materialObject.h"

enum Primitives {Points, Line, Triangle, Triangle_strip, Triangle_fan};

extern std::string LOCAL_OBJECT_DIR;
extern std::string LOCAL_COORDINATE_DIR;
extern std::string LOCAL_TEXTURE_DIR;

static void LoadObjectFile (MeshObject* mesh, MaterialObject* material, const std::string Path);
static Primitives LoadDrawPrimitive (const std::string shaderPath);
static std::vector <glm::vec3> LoadObjectVertices (const std::string Path);
static std::pair <std::vector <GLshort>, std::vector <GLshort>> LoadObjectIndices (Primitives prim, const std::string Path);
static std::vector <glm::vec2> LoadObjectTexCoords (const std::string Path);
static std::vector <glm::vec4> LoadObjectColours (const std::string Path);
std::vector <glm::vec3> GenerateFaceNormals (Primitives prim, std::vector <glm::vec3> vertices, std::vector <GLshort> indicesVertices);
std::vector <glm::vec3> GenerateVertexNormals (std::vector <glm::vec3> faceNormals, std::vector <GLshort> indicesVertices);
std::vector <glm::vec3> ReformatVertices (Primitives prim, std::vector <glm::vec3> vertices, std::vector <GLshort> indicesVertices);
std::vector <glm::vec2> ReformatTexCoords (Primitives prim, std::vector <glm::vec2> texCoords, std::vector <GLshort> indicesTexCoords);
std::vector <glm::vec4> ReformatColours (Primitives prim, std::vector <glm::vec4> colours, std::vector <GLshort> indicesColours);