#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

#include "buffer.h"
#include "layout.h"
#include <vector>
#include <glm\glm.hpp>
#include <algorithm>

class UniformBuffer : public Buffer
{
public:
	~UniformBuffer ();
	UniformBuffer (size_t numBytes, bool dynamicUpdate);

	bool HasMember (std::string name);
	template<typename T>
	bool SetMember (std::string const& name, T const& value);

	std::vector<Layout> GetLayout () const;
	void SetLayout (std::vector<Layout> layout);

	static int const shaderLookUp = 0;

protected:
	size_t GetRoundedBytes (size_t const numBytes) const;
	std::vector<Layout> m_VLayout;
};
template<typename T>
bool UniformBuffer::SetMember (std::string const& name, T const& value)
{
	auto iter = std::find_if (m_VLayout.begin (), m_VLayout.end (), [&name](Layout const& item){ return name == item.m_Name; });

	if (iter == m_VLayout.end ())
	{
		fprintf (stderr, "The setMember method in UniformBuffer failed, because member was not found.\n");
		return false;
	}

	T* target = reinterpret_cast<T *> (m_Data + iter->m_Offset);
	*target = value;

	return true;
}
#endif