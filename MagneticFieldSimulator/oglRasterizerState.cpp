#include "stdafx.h"
#include "oglRasterizerState.h"

OGLRasterizerState::OGLRasterizerState (std::shared_ptr<const RasterizerState> rasterizerState)
	:	OGLDrawingState (rasterizerState)
{
	m_FillMode = m_sFillMode[rasterizerState->m_FillMode];
	m_CullFace = m_sCullFace[rasterizerState->m_CullMode];
	m_FrontFace = (rasterizerState->m_FrontCCW ? GL_CCW : GL_CW);
	m_EnableScissor = (rasterizerState->m_EnableScissors ? GL_TRUE : GL_FALSE);
}

std::shared_ptr<OGLDrawObject> OGLRasterizerState::Create(std::shared_ptr<const DrawObject> dObject)
{
    if (dObject->GetType() == DP_RASTERIZER_STATE)
    {
		return std::make_shared<OGLRasterizerState>(std::static_pointer_cast<const RasterizerState>(dObject));
    }

    fprintf (stderr, "The create method of OGLRasterizerState failed, because the type of the object is incorrect./n");
	return nullptr;
}

void OGLRasterizerState::Enable()
{
    glPolygonMode(GL_FRONT_AND_BACK, m_FillMode);

    if (m_CullFace != 0)
    {
        glEnable(GL_CULL_FACE);
        glFrontFace(m_FrontFace);
        glCullFace(m_CullFace);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
    
}

GLenum const OGLRasterizerState::m_sFillMode [] = 
{
	GL_FILL,
	GL_LINE
};

GLenum const OGLRasterizerState::m_sCullFace [] = 
{
	0,
	GL_FRONT,
	GL_BACK
};