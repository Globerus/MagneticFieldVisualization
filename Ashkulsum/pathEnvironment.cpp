#include "stdafx.h"
#include "pathEnvironment.h"

PathEnvironment::~PathEnvironment ()
{

}

PathEnvironment::PathEnvironment ()
{

}

std::string PathEnvironment::ws2s(const std::wstring& wstr)
{
    int size_needed = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), 0, 0, 0, 0); 
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), &strTo[0], size_needed, 0, 0); 
    return strTo;
}

std::string PathEnvironment::GetExeDir ()
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
	return path + dir;
}