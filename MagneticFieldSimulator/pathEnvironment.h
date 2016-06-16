#ifndef PATH_ENVIRONMENT_H
#define PATH_ENVIRONMENT_H

#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <list>

class PathEnvironment
{
public:
	~PathEnvironment ();
	PathEnvironment ();

	std::string ws2s(const std::wstring& wstr);
	std::string GetExeDir ();

};
#endif