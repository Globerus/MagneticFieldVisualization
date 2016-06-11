#ifndef PROGRAM_FACTORY_H
#define PROGRAM_FACTORY_H

#include "program.h"
#include <string>
#include <sstream>
#include <fstream>
class ProgramFactory
{
public:
	~ProgramFactory ();
	ProgramFactory ();

	std::shared_ptr<Program> CreateFromFiles (std::string const& vsFile, std::string const& fsFile);
	std::shared_ptr<Program> CreateFromSources (std::string const& vsName, std::string const& vsSource,
													std::string const& fsName, std::string const& fsSource);

	std::string GetStringFromFile (std::string const& sFilename);

protected:
	virtual std::shared_ptr<Program> CreateSources (std::string const& vsName, std::string const& vsSource,
													std::string const& fsName, std::string const& fsSource) = 0;
};
#endif