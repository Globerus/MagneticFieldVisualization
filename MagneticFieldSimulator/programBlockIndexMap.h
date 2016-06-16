#ifndef PROGRAM_BLOCK_INDEX_MAP_H
#define PROGRAM_BLOCK_INDEX_MAP_H

#include <vector>
#include "oglInclude.h"

class ProgramBlockIndexMap 
{
public:
	~ProgramBlockIndexMap ();
	ProgramBlockIndexMap ();

	struct ProgramIndex 
	{
		int numUses;
		GLuint program;
		GLuint blockIndex;
	};

	int AskConnectionUnit (GLuint program, GLuint blockIndex);
	int GetUnit (GLuint Program, GLuint blockIndex);
	void ReleaseUnit (int unit);
private:
	std::vector<ProgramIndex> m_ProgramIndexMap;

};
#endif