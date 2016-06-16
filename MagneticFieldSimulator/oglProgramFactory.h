#ifndef OGL_PROGRAM_FACTORY_H
#define OGL_PROGRAM_FACTORY_H

#include "oglInclude.h"
#include <string>
#include "programFactory.h"
#include "oglProgram.h"
#include "oglProgramManager.h"

class OGLProgramFactory : public ProgramFactory
{
public:
	~OGLProgramFactory ();
	OGLProgramFactory ();

private:
	virtual std::shared_ptr<Program> CreateSources (std::string const& vsName, std::string const& vsSource,
													std::string const& fsName, std::string const& fsSource);
	
	GLuint Compile (GLenum type, std::string source);
	bool Link (GLuint program);

};
#endif