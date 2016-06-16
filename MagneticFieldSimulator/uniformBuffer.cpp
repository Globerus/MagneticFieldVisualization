#include "stdafx.h"
#include "uniformBuffer.h"

UniformBuffer::~UniformBuffer ()
{

}

UniformBuffer::UniformBuffer (size_t numBytes, bool dynamicUpdate)
	:	Buffer (1, GetRoundedBytes (numBytes), true)	
{
	m_Type = DP_UNIFORM_BUFFER;
	m_Usage = (dynamicUpdate ? DYNAMIC_UPDATE : STATIC);
	memset (m_Data, 0, m_NumBytes);
}

size_t UniformBuffer::GetRoundedBytes (size_t const numBytes) const
{
	if (numBytes > 0)
	{
		int remaining = numBytes % 16;

		if (remaining > 0)
		{
			return numBytes + 16 - remaining;
		}
		else
		{
			return numBytes;
		}
	}
	else
	{
		return 16;
	}
}

bool UniformBuffer::HasMember (std::string name)
{
	auto iter = std::find_if (m_VLayout.begin(), m_VLayout.end(),
        [&name](Layout const& item){ return name == item.m_Name; });
    return iter != m_VLayout.end();

}



std::vector<Layout> UniformBuffer::GetLayout () const 
{
	return m_VLayout;
}

void UniformBuffer::SetLayout (std::vector<Layout> layout)
{
	m_VLayout = layout;
}