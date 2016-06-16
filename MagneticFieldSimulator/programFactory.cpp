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

std::string ProgramFactory::GetStringFromFile (std::string const& sFilename)
{
	std::string source = "";
	std::ifstream stream (sFilename);
	std::stringstream shaderData;
	shaderData << stream.rdbuf();  //Loads the entire string into a string stream.
	stream.close();
	source = shaderData.str();

	return source;
}