#ifndef BLEND_STATE_H
#define BLEND_STATE_H

#include "drawingState.h"

class BlendState : public DrawingState
{
public:

	enum Mode
	{
		MODE_ZERO,
		MODE_ONE,
		MODE_SRC_ALPHA,
		MODE_INV_SRC_ALPHA,
		MODE_DEST_ALPHA,
		MODE_INV_DEST_ALPHA,
	};

	enum Operation
	{
		OP_ADD
	};

	enum Color
	{
		COLOR_ENABLE_RED = 1,
		COLOR_ENABLE_GREEN = 2,
		COLOR_ENABLE_BLUE = 4,
		COLOR_ENABLE_ALPHA = 8,
		COLOR_ENABLE_ALL = 15
	};


	enum 
	{
		NUM_TARGETS = 8
	};

	struct Target
	{
		bool enable;
		Mode srcColor;
		Mode dstColor;
		Operation opColor;
		Mode srcAlpha;
		Mode dstAlpha;
		Operation opAlpha;
		unsigned char mask;
	};

	BlendState ();

	bool m_EnableAlphaToCoverage;
	bool m_EnableIndependentBlend;
	Target m_Target[NUM_TARGETS];
	glm::vec4 m_BlendColor;
	unsigned int m_SampleMask;
};
#endif