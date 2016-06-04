#ifndef OGL_PROGRAM_MANAGER_H
#define OGL_PROGRAM_MANAGER_H

#include "customMap.h"
#include "oglProgram.h"

class OGLProgramManager 
{
public:
	~OGLProgramManager () {};
	OGLProgramManager () {};

	//static void Bind (std::string const sName, std::shared_ptr<OGLProgram> oglProgram);
	static void Bind (std::string const sName, std::shared_ptr<GLuint> pHandle);

	static bool Unbind (std::string const sName);
	static void UnbindAll ();

	//static std::shared_ptr<OGLProgram> Get (std::string const sName);
	static std::shared_ptr<GLuint> Get (std::string const sName);
	
private:
	//class ProgramMap : public CustomMap<std::string const, std::shared_ptr<OGLProgram>>
	class ProgramMap : public CustomMap<std::string const, std::shared_ptr<GLuint>>
	{
	public:
		~ProgramMap ();
		ProgramMap ();
	};

	static ProgramMap m_ProgramMap;
};
#endif