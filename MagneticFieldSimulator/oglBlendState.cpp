#include "stdafx.h"
#include "oglBlendState.h"

OGLBlendState::OGLBlendState (std::shared_ptr<const BlendState> blendState)
	:	OGLDrawingState (blendState)
{
	m_EnableAlphaToCoverage = blendState->m_EnableAlphaToCoverage;
	m_EnableIndependentBlend = blendState->m_EnableIndependentBlend;

	for (int i = 0; i < BlendState::NUM_TARGETS; i++)
	{
		auto bS = blendState->m_Target[i];
		Target& target = m_Target[i];
		target.enable =  (bS.enable ? GL_TRUE : GL_FALSE);
		target.srcColor = m_sMode[bS.srcColor];
		target.dstColor = m_sMode[bS.dstColor];
		target.opColor = m_sOperation[bS.opColor];
		target.srcAlpha = m_sMode[bS.srcAlpha];
		target.dstAlpha = m_sMode[bS.dstAlpha];
		target.opAlpha = m_sOperation[bS.opAlpha];
		target.rMask = (bS.mask & 1 ? GL_TRUE : GL_FALSE);
		target.gMask = (bS.mask & 2 ? GL_TRUE : GL_FALSE);
		target.bMask = (bS.mask & 4 ? GL_TRUE : GL_FALSE);
		target.aMask = (bS.mask & 8 ? GL_TRUE : GL_FALSE);
	}
	m_BlendColor = blendState->m_BlendColor;
	m_SampleMask = blendState->m_SampleMask;
}

std::shared_ptr<OGLDrawObject> OGLBlendState::Create (std::shared_ptr<const DrawObject> dObject)
{
	if (dObject->GetType ()== DP_BLEND_STATE)
	{
		return std::make_shared<OGLBlendState> (std::static_pointer_cast<const BlendState> (dObject));
	}

	fprintf (stderr, "The create method of OGLBlendState failed, because the type of the object is incorrect./n");
	return nullptr;
}

void OGLBlendState::Enable ()
{
	if (m_EnableAlphaToCoverage)
		glEnable (GL_SAMPLE_COVERAGE);
	else
		glDisable (GL_SAMPLE_COVERAGE);

	if (m_EnableIndependentBlend)
	{
		for (int i = 0; i < BlendState::NUM_TARGETS; i++)
		{
			Target& target = m_Target[i];
			if (target.enable)
			{
				glEnable (GL_BLEND);
				glBlendFuncSeparate (target.srcColor, target.dstColor, target.srcAlpha, target.dstAlpha);
				glBlendEquationSeparate (target.opColor, target.opAlpha);
			}
			else
			{
				glDisable (GL_BLEND);
			}
			glColorMaski (i, target.rMask, target.gMask, target.bMask, target.aMask);
			glSampleMaski (i, m_SampleMask);
		}
	}
	else
	{
		Target& target = m_Target[0];
			if (target.enable)
			{
				glEnable (GL_BLEND);
				glBlendFuncSeparate (target.srcColor, target.dstColor, target.srcAlpha, target.dstAlpha);
				glBlendEquationSeparate (target.opColor, target.opAlpha);
			}
			else
			{
				glDisable (GL_BLEND);
			}
			glColorMask (target.rMask, target.gMask, target.bMask, target.aMask);
			glSampleMaski (0, m_SampleMask);
	}

	glBlendColor (m_BlendColor.x, m_BlendColor.y, m_BlendColor.z, m_BlendColor.w);
}

GLenum const OGLBlendState::m_sMode [] = 
{
	GL_ZERO,
	GL_ONE,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA,
};

GLenum const OGLBlendState::m_sOperation [] = 
{
	GL_FUNC_ADD
};