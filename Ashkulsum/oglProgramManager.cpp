#include "stdafx.h"
#include "oglProgramManager.h"

OGLProgramManager::ProgramMap OGLProgramManager::m_ProgramMap;

void OGLProgramManager::Bind (std::string const sName, std::shared_ptr<GLuint> oglProgram)
{
	if (oglProgram)
	{
		m_ProgramMap.Insert (sName, oglProgram);
	}
	else
		fprintf (stderr, "The bind method in the OGL Program Manager failed, becausee the input argument is not correct.\n");
}

bool OGLProgramManager::Unbind (std::string const sName)
{
	if (sName != "")
	{
		std::shared_ptr<GLuint> oglProgram = nullptr;
		if (m_ProgramMap.Remove (sName, oglProgram))
		{
			oglProgram.reset ();
		}

		return true;
	}
	else
	{
		fprintf (stderr, "The unbind method in the OGLProgramManager failed, because the search criteria is empty.\n");
		return false;
	}
}

void OGLProgramManager::UnbindAll ()
{
	if (m_ProgramMap.HasElements ())
	{
		std::vector<std::shared_ptr<GLuint>> vProgram;
		m_ProgramMap.GatherAll (vProgram);
		
		for (auto iter = vProgram.begin (); iter!= vProgram.end (); iter++)
		{
			iter->reset ();
		}
		
		m_ProgramMap.RemoveAll ();
	}
}

std::shared_ptr<GLuint> OGLProgramManager::Get (std::string const sName) 
{
	std::shared_ptr<GLuint> oglProgram (nullptr);
	
	m_ProgramMap.Get (sName, oglProgram);
	
	return oglProgram;
}

OGLProgramManager::ProgramMap::ProgramMap ()
{

}

OGLProgramManager::ProgramMap::~ProgramMap ()
{

}