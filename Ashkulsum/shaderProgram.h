#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <map>
#include <glload\gl_3_3.h>
#include <glload\gl_load.hpp>
#include <glutil\glutil.h>

class ShaderProgram
{

private:
	typedef std::map <std::string, GLint> UniformMap;

public:
	typedef boost::shared_ptr<ShaderProgram> SharedPtr;

	ShaderProgram (){};
	~ShaderProgram (){};
	
	//Getters and Setters
	GLuint GetVertexShader ();
	GLuint GetFragmentShader ();
	GLuint GetShaderProgram ();
	
	void SetVertexShader (GLuint vShader);
	void SetFragmentShader (GLuint fShader);
	void SetShaderProgram (GLuint sProgram);

	//Get the Uniform Location
	GLint GetUniformIndex (const char* unifName);

private:
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	GLuint m_ShaderProgram;

	UniformMap m_UniformMap;
};
#endif