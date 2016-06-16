#include "stdafx.h"
#include "rasterizerState.h"

RasterizerState::RasterizerState ()
	:	m_FillMode (FILL_SOLID),
		m_CullMode (CULL_BACK),
		m_FrontCCW (true),
		m_EnableDepthClip (true),
		m_EnableScissors (false)
{
	m_Type = DP_RASTERIZER_STATE;
}