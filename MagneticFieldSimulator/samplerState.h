#ifndef SAMPLER_STATE_H
#define SAMPLER_STATE_H
#include "drawingState.h"

class SamplerState : public DrawingState
{
public:
	enum Filter
	{
		MIN_N_MAG_N_MIP_N,
		MIN_N_MAG_N_MIP_L,
		MIN_N_MAG_L_MIP_N,
		MIN_N_MAG_L_MIP_L,
		MIN_L_MAG_N_MIP_N,
		MIN_L_MAG_N_MIP_L,
		MIN_L_MAG_L_MIP_N,
		MIN_L_MAG_L_MIP_L,
		MIN_L_MAG_L,
		MIN_N_MAG_L,
		MIN_L_MAG_N,
		MIN_N_MAG_N,
	};

	enum BoundaryMode
	{
		WRAP,
		MIRROR,
		CLAMP,
		BORDER,
		MIRROR_ONCE

	};

	enum Comparison
	{
		NEVER,
        LESS,
        EQUAL,
        LESS_EQUAL,
        GREATER,
        NOT_EQUAL,
        GREATER_EQUAL,
        ALWAYS
	};

	SamplerState ();

	Filter m_Filter;
	BoundaryMode m_Mode[3];
	glm::vec4 m_BorderColor;
	Comparison m_Comparison;

	static int const shaderLookUp = 2;
};
#endif