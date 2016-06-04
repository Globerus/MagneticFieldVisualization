#ifndef OGL_PROGRAM_H
#define OGL_PROGRAM_H

#include "oglInclude.h"
#include "program.h"
#include "oglReflection.h"

class OGLProgram : public Program
{
public:
	virtual ~OGLProgram();
	//OGLProgram (GLuint programHandle, GLuint vShaderHandle, GLuint fShaderHandle);
	OGLProgram (GLuint programHandle);

	GLuint GetProgramHandle () const;
	GLuint GetVertexShaderHandle () const;
	GLuint GetFragmentShaderHandle () const;

	OGLReflection const& GetReflector () const;

protected:
	GLuint m_ProgHandle;
	GLuint m_VSHandle;
	GLuint m_FSHandle;
	OGLReflection m_Reflector;

};
#endif