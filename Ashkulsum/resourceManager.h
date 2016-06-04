#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "resource.h"
#include "utils.h"
#include <string>
#include <map>
#include <boost\make_shared.hpp>
#include <boost\shared_ptr.hpp>

class ResourceManager
{
private:
	template <typename T> 
	struct RsrcMap 
	{
		typedef  std::map <std::string, typename Resource<T>::SharedPtr> ResourceMap;

		static ResourceMap m_ResourceMap;
	};

public:
	typedef boost::shared_ptr <ResourceManager> SharedPtr;

	static ResourceManager::SharedPtr GetInstance ();
	//~ResourceManager () {UnloadAll<T> ();}

	template <typename T>
	typename Resource<T>::SharedPtr GetResource (std::string fileName);

	template <typename T>
	typename Resource<T>::SharedPtr Load (std::string fileName);

	void Unload (std::string fileName);

	template <typename T> void UnloadAll ();
	

private:
	static ResourceManager::SharedPtr s_Instance;

};

template <typename T>
typename ResourceManager::RsrcMap<T>::ResourceMap typename ResourceManager::RsrcMap<T>::m_ResourceMap;

template <typename T>
typename Resource<T>::SharedPtr ResourceManager::GetResource (std::string fileName)
{
	typename Resource<T>::SharedPtr rsrcPtr;
	
	try
	{
		typename RsrcMap<T>::ResourceMap::iterator it;
		it = typename RsrcMap<T>::m_ResourceMap.find (fileName);
	
		if (it == typename RsrcMap<T>::m_ResourceMap.end ())
		{	
			rsrcPtr = Load<T> (fileName);		
			typename RsrcMap<T>::m_ResourceMap[fileName] = rsrcPtr;
		}
		else
			rsrcPtr = it->second;

	}
	catch (std::exception& e)
	{
		std::cout << e.what () << ": " << fileName;
	}

	return rsrcPtr;
}

template <typename T>
typename Resource<T>::SharedPtr ResourceManager::Load (std::string fileName)
{
	typename Resource<T>::SharedPtr rsrc = boost::make_shared <Resource<T>> (fileName);
	if (!rsrc)
		throw std::invalid_argument ("Could not load the resource!");

	return rsrc;
}

template <typename T>
void ResourceManager::UnloadAll ()
{
	typename RsrcMap<T>::ResourceMap::iterator it;

	for (it = typename RsrcMap<T>::m_ResourceMap.begin (); it != typename RsrcMap<T>::m_ResourceMap.end (); it ++)
		it->second.reset ();
	
	typename RsrcMap<T>::m_ResourceMap.clear ();
}
/*template <typename T>
class ResourceManager
{
private:
	typedef std::map <std::string, typename Resource<T>::SharedPtr> ResourceMap;

public:
	typedef boost::shared_ptr <ResourceManager<T>> SharedPtr;

	ResourceManager () {};
	~ResourceManager () {UnloadAll ();}

	void Load (std::string fileName);

	void Unload (std::string fileName);

	void UnloadAll ();
	

private:
	ResourceMap m_ResourceMap;

};

template <typename T>
void ResourceManager<T>::Load (std::string fileName)
{
	try
	{
	ResourceMap::iterator it;

	it = m_ResourceMap.find (fileName);

	if (it == m_ResourceMap.end ())
	{
		Resource<T>::SharedPtr rsrc ( new Resource <T> (fileName));

		if (!rsrc)
			throw std::invalid_argument ("Could not load the resource!");

		m_ResourceMap[fileName] = rsrc;
	}
	else
		throw std::invalid_argument ("The resource is already loaded!");
	}
	catch (std::exception &e)
	{
		fprintf (stderr, "%s : %s\n", e.what (), fileName);
	}
}

template <typename Resource>
void ResourceManager<Resource>::UnloadAll ()
{
	ResourceMap::iterator it;

	for (it = m_ResourceMap.begin (); it != m_ResourceMap.end (); it ++)
		it->second.reset ();
	
	m_ResourceMap.clear ();
}*/
/*
class ResourceManager
{
private:
	typedef std::map <std::string, boost::any> ResourceMap;

public:
	~ResourceManager () {};
	static ResourceManager& GetInstance ();

	boost::any GetResource (const char* inFileName);
	bool FindResource (const char* inFileName, boost::any &resource);
	template <typename T> typename T::SharedPtr LoadResource (FileStream::FileStreamPtr fileStream);

private:
	ResourceMap m_ResourceMap;
	static ResourceManager& s_Instance;
};

template <typename T> typename T::SharedPtr ResourceManager::LoadResource (FileStream::FileStreamPtr fileStream)
{
	T::SharedPtr resource (new T (fileStream));
	return resource;
}*/
#endif