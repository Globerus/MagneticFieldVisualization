#include "stdafx.h"
#include "oglSamplerState.h"

OGLSamplerState::OGLSamplerState (std::shared_ptr<const SamplerState> samplerState)
	:	OGLDrawingState (samplerState)
{
	glGenSamplers (1, &m_OGLObject);

	glSamplerParameteri (m_OGLObject, GL_TEXTURE_WRAP_S, m_TableMode[samplerState->m_Mode[0]]);
	glSamplerParameteri (m_OGLObject, GL_TEXTURE_WRAP_T, m_TableMode[samplerState->m_Mode[1]]);
	glSamplerParameteri (m_OGLObject, GL_TEXTURE_WRAP_R, m_TableMode[samplerState->m_Mode[2]]);

	float borderColor[] =	{	
								samplerState->m_BorderColor[0],
								samplerState->m_BorderColor[1],
								samplerState->m_BorderColor[2],
								samplerState->m_BorderColor[3]
							};

	glSamplerParameterfv(m_OGLObject, GL_TEXTURE_BORDER_COLOR, borderColor); 

	switch (samplerState->m_Filter)
	{
		case SamplerState::MIN_N_MAG_N_MIP_N:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case SamplerState::MIN_N_MAG_N_MIP_L:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case SamplerState::MIN_N_MAG_L_MIP_N:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case SamplerState::MIN_N_MAG_L_MIP_L:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case SamplerState::MIN_L_MAG_N_MIP_N:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case SamplerState::MIN_L_MAG_N_MIP_L:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case SamplerState::MIN_L_MAG_L_MIP_N:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case SamplerState::MIN_L_MAG_L_MIP_L:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case SamplerState::MIN_L_MAG_L:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case SamplerState::MIN_L_MAG_N:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case SamplerState::MIN_N_MAG_L:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case SamplerState::MIN_N_MAG_N:
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		default :
			fprintf (stderr, "The filter of the Sampler is not found.\n");
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MIN_FILTER, 0);
			glSamplerParameteri (m_OGLObject, GL_TEXTURE_MAG_FILTER, 0);
			break;
	}
}

std::shared_ptr<OGLDrawObject> OGLSamplerState::Create (std::shared_ptr<const DrawObject> drawObject)
{
	if (drawObject->GetType () == DP_SAMPLER_STATE)
	{
		return std::make_shared<OGLSamplerState> (std::static_pointer_cast<SamplerState const> (drawObject));
	}

	return nullptr;
}

GLint const OGLSamplerState::m_TableMode[] =
{
	GL_REPEAT,
	GL_MIRRORED_REPEAT,
	GL_CLAMP_TO_EDGE,
	GL_CLAMP_TO_BORDER,
	GL_MIRRORED_REPEAT
};

GLint const OGLSamplerState::m_TableCompare[] =
{
	GL_NEVER,
    GL_LESS,
    GL_EQUAL,
    GL_LEQUAL,
    GL_GREATER,
    GL_NOTEQUAL,
    GL_GEQUAL,
    GL_ALWAYS
};