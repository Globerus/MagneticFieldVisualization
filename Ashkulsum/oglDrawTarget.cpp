#include "stdafx.h"
#include "oglDrawTarget.h"

OGLDrawTarget::OGLDrawTarget (std::shared_ptr<const DrawTarget> drawTarget, std::vector<std::shared_ptr<OGLTextureRT>> rtTextures, std::shared_ptr<OGLTextureDS> dsTexture)
	:	m_DSTexture (dsTexture),
		m_RTTextures (rtTextures),
		m_Target (std::const_pointer_cast<DrawTarget> (drawTarget)),
		m_Framebuffer (0)
{
	glGenFramebuffers (1, &m_Framebuffer);
}

std::shared_ptr<OGLDrawTarget> OGLDrawTarget::Create (std::shared_ptr<const DrawTarget> drawTarget, std::vector<std::shared_ptr<OGLDrawObject>>& rtTextures, std::shared_ptr<OGLDrawObject> dsTexture)
{
	std::vector<std::shared_ptr<OGLTextureRT>> dRTTextures (rtTextures.size());
	for (size_t i = 0; i < rtTextures.size(); i++)
	{
		dRTTextures[i] = std::static_pointer_cast<OGLTextureRT> (rtTextures[i]);
	}

	std::shared_ptr<OGLTextureDS> dDSTexture = std::static_pointer_cast<OGLTextureDS> (dsTexture);

	return std::make_shared<OGLDrawTarget> (drawTarget, dRTTextures, dDSTexture);
}

void OGLDrawTarget::Enable ()
{
	GLint intValues[4];
	GLdouble doubleValues[2];

	glGetIntegerv(GL_VIEWPORT, intValues);
	glGetDoublev(GL_DEPTH_RANGE, doubleValues);

	m_SaveViewportX = intValues[0];
	m_SaveViewportY = intValues[1];
	m_SaveViewportWidth = intValues[2];
	m_SaveViewportHeight = intValues[3];
	m_SaveViewportNear = doubleValues[0];
	m_SaveViewportFar = doubleValues[1];

	auto viewportWidth = m_Target->GetWidth ();
	auto viewportHeight = m_Target->GetHeight ();

	glViewport (0, 0, viewportWidth, viewportHeight);

	glDepthRange (0.0, 1.0);

	//glBindTexture (GL_TEXTURE_2D, m_DSTexture->GetOGLDrawObject ());//
	
	//glTexImage2D (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, viewportWidth, viewportHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, 0);//
	//glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, viewportWidth, viewportHeight, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, 0);//

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC, GL_LESS);

	glBindFramebuffer (GL_DRAW_FRAMEBUFFER, m_Framebuffer);

	if (m_DSTexture)
	{
		glFramebufferTexture2D (GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DSTexture->GetOGLDrawObject (), 0);
	}
	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr,"FB error, status: 0x%x\n", Status);
    }

	glDrawBuffer (GL_NONE);
	glReadBuffer (GL_NONE);
	/*
	auto const numTargets = m_Target->GetNumTargets ();
	std::vector<GLenum> useDrawBuffers (numTargets);

	for (unsigned int i = 0; i < numTargets; i++)
	{
		auto colorTarget = GL_COLOR_ATTACHMENT0 + i;
		useDrawBuffers[i] = colorTarget;

		auto textureRT = m_RTTextures[i];
		glFramebufferTexture2D (GL_DRAW_FRAMEBUFFER, colorTarget, GL_TEXTURE_2D, textureRT->GetOGLDrawObject (), 0);
	}

	glDrawBuffers (static_cast<GLsizei> (useDrawBuffers.size ()), useDrawBuffers.data());

	

    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr,"FB error, status: 0x%x\n", Status);
    }*/
}

void OGLDrawTarget::Disable ()
{
	glBindFramebuffer (GL_DRAW_FRAMEBUFFER, 0);

	glViewport (m_SaveViewportX, m_SaveViewportY, m_SaveViewportWidth, m_SaveViewportHeight);

	glDepthRange (m_SaveViewportNear, m_SaveViewportFar);

	auto const numTargets = m_Target->GetNumTargets ();

	for (unsigned int i = 0; i < numTargets; i++)
	{
		auto textureRT = m_RTTextures[i];
		if (textureRT->CanGenerateAutoMipMaps ())
		{
			textureRT->GenerateMipMaps ();
		}
	}
}