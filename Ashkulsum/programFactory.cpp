#include "stdafx.h"
#include "programFactory.h"

ProgramFactory::~ProgramFactory ()
{
	
}

ProgramFactory::ProgramFactory ()
{
	
}

std::shared_ptr<Program> ProgramFactory::CreateFromSources (std::string const& vsName, std::string const& vsSource,
																	std::string const& fsName, std::string const& fsSource)
{
	return CreateSources (vsName, vsSource, fsName, fsSource);
}

std::shared_ptr<Program> ProgramFactory::CreateFromFiles (std::string const& vsFilename, std::string const& fsFilename)
{
	if (vsFilename == "" || fsFilename == "")
	{
		fprintf (stderr, "The createFromFIles method in ProgramFactory failed, because the input arguments are not correct.\n");
		return nullptr;
	}

	std::string vsSource = GetStringFromFile (vsFilename);

	if (vsSource == "")
	{
		fprintf (stderr, "The createFromFIles method in ProgramFactory failed, because the vertex shader source is empty.\n");
		return nullptr;
	}

	std::string fsSource = GetStringFromFile (fsFilename);

	if (fsSource == "")
	{
		fprintf (stderr, "The createFromFIles method in ProgramFactory failed, because the fragment shader source is empty.\n");
		return nullptr;
	}

	return CreateSources (vsFilename, vsSource, fsFilename, fsSource);
}
/*
std::shared_ptr<Program> ProgramFactory::CreateSources (std::string const& vsName, std::string const& vsSource,
													std::string const& fsName, std::string const& fsSource)
{
	std::shared_ptr<VertexShader> vShader;
	std::shared_ptr<FragmentShader> fShader;

	if (vsSource != "" && fsSource != "")
	{
		return nullptr;
	}
	
	vShader.reset (new VertexShader (vsName, vsSource));
	
	fShader.reset (new FragmentShader (fsName, fsSource));
	
	std::shared_ptr<Program> program = std::make_shared<Program> ();

	program->SetVertexShader (vShader);
	program->SetFragmentShader (fShader);
	
	std::string progName = vsName + fsName;
	program->SetProgramName (progName);

	return program;
}*/

std::string ProgramFactory::GetStringFromFile (std::string const& sFilename)
{
	std::string source = "";
	std::ifstream stream (sFilename);
	std::stringstream shaderData;
	shaderData << stream.rdbuf();  //Loads the entire string into a string stream.
	stream.close();
	source = shaderData.str();
/*const std::string &shaderString = shaderData.str();
	if (stream)
	{
		std::string line;
		while (getline (stream, line))
		{
			if (line != "")
				source += line + "\\n ";
		}
	}
	*/
	return source;
}