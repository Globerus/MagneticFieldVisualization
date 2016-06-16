#include "stdafx.h"
#include "programBlockIndexMap.h"

ProgramBlockIndexMap::ProgramBlockIndexMap ()
{

}

ProgramBlockIndexMap::~ProgramBlockIndexMap ()
{

}

int ProgramBlockIndexMap::AskConnectionUnit (GLuint program, GLuint blockIndex)
{
	int availableUnit = -1;
	for (unsigned int i = 0; i < m_ProgramIndexMap.size (); i++)
	{
		auto& unit = m_ProgramIndexMap[i];

		if (unit.program == program && unit.blockIndex == blockIndex)
		{
			++unit.numUses;
			return i;
		}

		if (0 == unit.numUses)
		{
			availableUnit = i;
		}
	}

	if (availableUnit == -1)
	{
		availableUnit = m_ProgramIndexMap.size ();

		ProgramIndex progIndex;
		progIndex.numUses = 0;
		progIndex.blockIndex = 0;
		progIndex.program = 0;

		m_ProgramIndexMap.push_back (progIndex);
	}

	auto & unit = m_ProgramIndexMap[availableUnit];
	unit.numUses = 1;
	unit.program = program;
	unit.blockIndex = blockIndex;

	return availableUnit;
}

int ProgramBlockIndexMap::GetUnit (GLuint program, GLuint blockIndex)
{
	for (unsigned int i = 0; i < m_ProgramIndexMap.size (); i++)
	{
		auto& unit = m_ProgramIndexMap[i];

		if (unit.program == program && unit.blockIndex == blockIndex)
		{
			return i;
		}
	}
	return -1;
}

void ProgramBlockIndexMap::ReleaseUnit (int index)
{
	if (index > 0 && index < (int)m_ProgramIndexMap.size())
	{
		auto & unit = m_ProgramIndexMap[index];
		
		if (unit.numUses > 0)
		{
			--unit.numUses;
		}
	}
}