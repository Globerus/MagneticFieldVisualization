#include "stdafx.h"
#include "oglProgramFactory.h"

OGLProgramFactory::~OGLProgramFactory ()
{

}

OGLProgramFactory::OGLProgramFactory ()
{

}

std::shared_ptr<Program> OGLProgramFactory::CreateSources (std::string const& vsName, std::string const& vsSource,
													std::string const& fsName, std::string const& fsSource)
{
	std::shared_ptr<VertexShader> vShader;
	std::shared_ptr<FragmentShader> fShader;

	if (vsSource == "" && fsSource == "")
	{
		return nullptr;
	}
	
	std::string name = vsName + fsName;

	std::shared_ptr<GLuint> pHandle = OGLProgramManager::Get (name);
	
	if (pHandle.get() == 0)
	{
		GLuint fHandle = Compile (GL_FRAGMENT_SHADER, fsSource);
		GLuint vHandle = Compile (GL_VERTEX_SHADER, vsSource);

		pHandle = std::make_shared<GLuint> (glCreateProgram ());

		glAttachShader (*pHandle.get(), vHandle);
		glAttachShader (*pHandle.get(), fHandle);

		bool status = Link (*pHandle.get());

		glDetachShader (*pHandle.get(), vHandle);
		glDetachShader (*pHandle.get(), fHandle);

		if (!status)
		{
			glDeleteProgram (*pHandle.get());
			return nullptr;
		}
		OGLProgramManager::Bind (name, pHandle);
	}

	std::shared_ptr<OGLProgram> oglProgram = std::make_shared<OGLProgram> (*pHandle.get());
	OGLReflection const& reflector = oglProgram->GetReflector ();
		
	oglProgram->SetProgramName (name);
		
	oglProgram->SetVertexShader (std::make_shared<VertexShader> (reflector));
	oglProgram->SetFragmentShader (std::make_shared<FragmentShader> (reflector));

	return oglProgram;
}

GLuint OGLProgramFactory::Compile (GLenum type, std::string source)
{
	const char* cSource = source.c_str ();
	GLuint shader = glCreateShader (type);

	glShaderSource (shader, 1, &cSource, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv (shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint logLength;
		glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			GLchar* strLogInfo = new GLchar[logLength+1];
			glGetShaderInfoLog (shader, logLength, NULL, strLogInfo);

			fprintf(stderr, "Compile failure in shader:\n%s\n", strLogInfo);
			delete[] strLogInfo;
		}
		else
		{
			fprintf (stderr, "Invalid Log Length !\n");
		}

		glDeleteShader (shader);
		shader = 0;
	}

	return shader;
}

bool OGLProgramFactory::Link (GLuint program)
{
	glLinkProgram (program);

	GLint status;

	glGetProgramiv (program, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint logLength;
		glGetProgramiv (program, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			GLchar* strLogInfo = new GLchar[logLength+1];
			glGetProgramInfoLog (program, logLength, NULL, strLogInfo);

			fprintf(stderr, "Linking failure in program:\n%s\n", strLogInfo);
			delete[] strLogInfo;
		}
		else
		{
			fprintf (stderr, "Invalid Log Length !\n");
		}

		return false;
	}

	return true;
}