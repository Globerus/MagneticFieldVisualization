#include "stdafx.h"
#include "oglDepthStencilState.h"


OGLDepthStencilState::OGLDepthStencilState (std::shared_ptr<const DepthStencilState> depthStencilState)
	:	OGLDrawingState (depthStencilState)
{
	m_DepthEnable = (depthStencilState->m_DepthEnable ? GL_TRUE : GL_FALSE);
    m_WriteMask = m_sWriteMask[depthStencilState->m_WriteMask];
    m_Comparison = m_sComparison[depthStencilState->m_Comparison];
    m_StencilEnable = (depthStencilState->m_StencilEnable ? GL_TRUE : GL_FALSE);
    m_StencilReadMask = depthStencilState->m_StencilReadMask;
    m_StencilWriteMask = depthStencilState->m_StencilWriteMask;
    DepthStencilState::Face front = depthStencilState->m_FrontFace;
    m_FrontFace.onFail = m_sOperation[front.fail];
    m_FrontFace.onDepthFail = m_sOperation[front.depthFail];
    m_FrontFace.onDepthPass = m_sOperation[front.pass];
    m_FrontFace.comparison = m_sComparison[front.comparison];
    DepthStencilState::Face back = depthStencilState->m_BackFace;
    m_BackFace.onFail = m_sOperation[back.fail];
    m_BackFace.onDepthFail = m_sOperation[back.depthFail];
    m_BackFace.onDepthPass = m_sOperation[back.pass];
    m_BackFace.comparison = m_sComparison[back.comparison];
    m_Reference = depthStencilState->m_Reference;
}

std::shared_ptr<OGLDrawObject> OGLDepthStencilState::Create (std::shared_ptr<const DrawObject> dObject)
{
	if (dObject->GetType () == DP_DEPTH_STENCIL_STATE)
	{
		return std::make_shared<OGLDepthStencilState> (std::static_pointer_cast<const DepthStencilState> (dObject));
	}

	fprintf (stderr, "The create method of OGLDepthStencilState failed, because the type of the object is incorrect./n");
	return nullptr;
}

void OGLDepthStencilState::Enable ()
{
	if (m_DepthEnable)
	{
		glEnable (GL_DEPTH_TEST);
		glDepthFunc (m_Comparison);
	}
	else
	{
		glDisable (GL_DEPTH_TEST);
	}

	glDepthMask (m_WriteMask);

	if (m_StencilEnable)
	{
		glEnable(GL_STENCIL_TEST);

        glStencilFuncSeparate(GL_FRONT, m_FrontFace.comparison, m_Reference, m_StencilReadMask);
        glStencilMaskSeparate(GL_FRONT, m_StencilWriteMask);
        glStencilOpSeparate(GL_FRONT, m_FrontFace.onFail, m_FrontFace.onDepthFail, m_FrontFace.onDepthPass);
        glStencilFuncSeparate(GL_BACK, m_BackFace.comparison, m_Reference, m_StencilReadMask);
        glStencilMaskSeparate(GL_BACK, m_StencilWriteMask);
        glStencilOpSeparate(GL_BACK, m_BackFace.onFail, m_BackFace.onDepthFail, m_BackFace.onDepthPass);
	}
	else
	{
		glDisable (GL_STENCIL_TEST);
	}
}

GLboolean const OGLDepthStencilState::m_sWriteMask [] = 
{
	GL_FALSE,
	GL_TRUE
};

GLenum const OGLDepthStencilState::m_sComparison [] = 
{
	GL_LEQUAL,
	GL_ALWAYS
};

GLenum const OGLDepthStencilState::m_sOperation [] = 
{
	GL_KEEP
};