#ifndef OGL_TEXTURE_H
#define OGL_TEXTURE_H

#include "oglResource.h"
#include "textureO.h"

class OGLTexture : public OGLResource
{
protected:
	OGLTexture (std::shared_ptr<const Texture> texture, GLenum target);

public:
	std::shared_ptr<Texture> GetTexture () const;
	GLenum GetTarget () const;

protected:
	GLenum m_Target;
	unsigned int m_NumLevels;
	GLuint m_InternalFormat;
	GLuint m_ExternalFormat;
	GLuint m_ExternalType;

	static GLuint const m_TableInternalFormat[DP_MAX_CONTAINER_TYPE];
	static GLuint const m_TableExternalFormat[DP_MAX_CONTAINER_TYPE];
	static GLuint const m_TableExternalType[DP_MAX_ELEMENT_TYPE];

};
#endif