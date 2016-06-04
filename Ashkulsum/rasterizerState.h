#ifndef RASTERIZER_STATE_H
#define RASTERIZER_STATE_H

#include "drawingState.h"

class RasterizerState : public DrawingState
{
public:
	enum FillMode
	{
		FILL_SOLID,
		FILL_WIREFRAME
	};

	enum CullMode
	{
		CULL_NONE,
		CULL_FRONT,
		CULL_BACK
	};

	RasterizerState ();

	FillMode m_FillMode;
	CullMode m_CullMode;
	bool m_FrontCCW;
	bool m_EnableDepthClip;
	bool m_EnableScissors;

};
#endif