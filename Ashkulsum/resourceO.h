#ifndef RESOURCE_O_H
#define RESOURCE_O_H

#include "drawObject.h"

class Resource : public DrawObject
{
public:
	virtual ~Resource ();

	enum Usage
	{
		STATIC,
		DYNAMIC_UPDATE
	};

	unsigned int const& GetNumBytes () const;
	unsigned int const& GetElementSize () const;
	unsigned int const& GetNumElements () const;
	unsigned int const& GetNumActiveElements () const; // For texts

	void SetNumActiveElements (unsigned int numActiveElements);

	void SetUsage (Usage usage);
	Usage GetUsage () const;

	void CreateStorage ();
	char const* GetData () const;
	char* GetData ();

	template <typename T> T const* Get () const;
	template <typename T> T* Get ();

protected:
	Resource (unsigned int numElements, size_t elementSize, bool createStorage);

	unsigned int m_NumBytes;
	unsigned int m_ElementSize;
	unsigned int m_NumElements;
	unsigned int m_NumActiveElements;

	Usage m_Usage;
	std::vector<char> m_Storage;
	char* m_Data;
};

template <typename T>
T const* Resource::Get () const
{
	return reinterpret_cast<T const*> (m_Data);
}

template <typename T>
T* Resource::Get ()
{
	return reinterpret_cast<T*> (m_Data);
}

#endif