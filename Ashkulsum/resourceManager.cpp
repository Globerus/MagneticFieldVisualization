#include "stdafx.h"
#include "ResourceManager.h"
ResourceManager::SharedPtr ResourceManager::s_Instance (nullptr);

ResourceManager::SharedPtr ResourceManager::GetInstance ()
{
	if (s_Instance == nullptr)
	{
		s_Instance.reset (new ResourceManager ());
	}
	return s_Instance;
}
/*
ResourceManager& ResourceManager::GetInstance ()
{
	static ResourceManager s_Instance;
	return s_Instance;
}

boost::any ResourceManager::GetResource (const char* inFileName)
{
	boost::any resource;
	bool loaded = FindResource (inFileName, resource);

	if (!loaded)
	{
		FileStream::FileStreamPtr fileStream (new FileStream);
		fileStream->LoadFileStream (inFileName);
		
		std::string ext = fileStream->GetExtension ();
		if (ext == ".obj")
			resource = LoadResource <ResourceMesh> (fileStream);
		else if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
				resource = LoadResource <ResourceImage> (fileStream);
		else if (ext == ".dds" || ext == ".bmp")
				resource = LoadResource <ResourceImage> (fileStream);
		else if (ext == ".ipc")
				resource = LoadResource <ResourcePoint> (fileStream);
			else if (ext == ".lp")
				resource = LoadResource <ResourceLight> (fileStream);
			else if (ext == ".mtrl")
				resource = LoadResource <ResourceMaterial> (fileStream);
		m_ResourceMap[inFileName] = resource;
	}
	return resource;
}

bool ResourceManager::FindResource (const char* inFileName, boost::any &resource)
{
	bool result = false;
	ResourceMap::iterator iter = m_ResourceMap.find (inFileName);
	if (iter != m_ResourceMap.end ())
	{
		resource = iter->second;
		result = true;
	}
	return result;
}*/