#include "stdafx.h"
#include "Utils.h"

std::string Utils::ws2s(const std::wstring& wstr)
{
    int size_needed = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), 0, 0, 0, 0); 
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), &strTo[0], size_needed, 0, 0); 
    return strTo;
}
std::wstring Utils::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

std::string Utils::GetFullDirPath (std::string fileName)
{
	TCHAR dest[MAX_PATH];
	size_t destSize = MAX_PATH;
	char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
	DWORD length = GetModuleFileName( NULL, dest, destSize );	
	std::string dest2 = ws2s (dest);
	_splitpath_s (dest2.c_str(), drive, dir, fname, ext);
	std::string path = drive;
	return path + dir + fileName;
}

double Utils::GenerateRandomDouble (double min, double max)
{
	double random = ((double) rand()) / (double) RAND_MAX;
	double diff = max - min;
	double r = random * diff;
	return r + min;
}

std::string Utils::GetExtension (std::string file)
{
	if (!file.empty ())
		return boost::filesystem::extension (fileName);

	return std::string.empty ();
}