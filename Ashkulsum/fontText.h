#ifndef FONTTEXT
#define FONTTEXT

#include <vector>
#include <glload\gl_3_3.h>
#include <glload\gl_load.hpp>
#include <glutil\glutil.h>

// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);
std::vector <glm::vec3> GetVerticesText2D(const char * text, int x, int y, int size);
std::vector <glm::vec2> GetTexturesText2D(const char * text);

#endif