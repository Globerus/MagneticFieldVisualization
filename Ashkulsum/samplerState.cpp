#include "stdafx.h"
#include "samplerState.h"

SamplerState::SamplerState ()
	:	m_Filter (MIN_N_MAG_N_MIP_N),
		m_BorderColor (glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
		m_Comparison (NEVER)
{
	m_Type = DP_SAMPLER_STATE;
	m_Mode[0] = CLAMP;
	m_Mode[1] = CLAMP;
	m_Mode[2] = CLAMP;
}