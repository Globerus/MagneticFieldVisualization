#ifndef DEPTH_STENCIL_STATE_H
#define DEPTH_STENCIL_STATE_H

#include "drawingState.h"

class DepthStencilState : public DrawingState 
{
public:
	enum WriteMask
	{
		MASK_ZERO,
		MASK_ALL
	};

	enum Comparison
	{
		LESS_EQUAL,
		ALWAYS
	};

	enum Operation
	{
		OP_KEEP
	};

	struct Face
	{
		Operation fail;
		Operation depthFail;
		Operation pass;
		Comparison comparison;
	};

	DepthStencilState ();

	bool m_DepthEnable;
	WriteMask m_WriteMask;
	Comparison m_Comparison;
	bool m_StencilEnable;
	unsigned char m_StencilReadMask;
	unsigned char m_StencilWriteMask;
	Face m_FrontFace;
	Face m_BackFace;
	unsigned int m_Reference;
};
#endif