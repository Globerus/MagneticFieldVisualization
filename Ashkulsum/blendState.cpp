#include "stdafx.h"
#include "blendState.h"

BlendState::BlendState ()
	:	m_EnableAlphaToCoverage (false),
		m_EnableIndependentBlend (false),
		m_BlendColor (glm::vec4 (0.0f)),
		m_SampleMask (0xFFFFFFFFu)
{
	m_Type = DP_BLEND_STATE;

	for (int i = 0; i < NUM_TARGETS; i++)
	{
		Target& target = m_Target[i];
		target.enable = false;
		target.srcColor = MODE_ONE;
		target.dstColor = MODE_ZERO;
		target.opColor = OP_ADD;
		target.srcAlpha = MODE_ONE;
		target.dstAlpha = MODE_ZERO;
		target.opAlpha = OP_ADD;
		target.mask = COLOR_ENABLE_ALL;
	}
}