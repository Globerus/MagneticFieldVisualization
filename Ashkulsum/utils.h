#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <time.h>
#include <Windows.h>
#include <boost\filesystem.hpp>

class Utils 
{
public:
	static std::string ws2s(const std::wstring& wstr);
	static std::wstring s2ws(const std::string& s);
	static std::string GetFullDirPath (std::string fileName);
	static double GenerateRandomDouble (double min, double max);
	static std::string GetExtension (std::string file);

};

#endif