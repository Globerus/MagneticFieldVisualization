#include "stdafx.h"
#include "depthStencilState.h"

DepthStencilState::DepthStencilState ()
	:	m_DepthEnable (true),
		m_WriteMask (MASK_ALL),
		m_Comparison (LESS_EQUAL),
		m_StencilEnable (false),
		m_StencilReadMask (0xFF),
		m_StencilWriteMask (0xFF),
		m_Reference (0)
{
	m_Type = DP_DEPTH_STENCIL_STATE;

	m_FrontFace.fail = OP_KEEP;
	m_FrontFace.depthFail = OP_KEEP;
	m_FrontFace.pass = OP_KEEP;
	m_FrontFace.comparison = ALWAYS;

	m_BackFace.fail = OP_KEEP;
	m_BackFace.depthFail = OP_KEEP;
	m_BackFace.pass = OP_KEEP;
	m_BackFace.comparison = ALWAYS;
}