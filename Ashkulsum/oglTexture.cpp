#include "stdafx.h"
#include "oglTexture.h"

OGLTexture::OGLTexture (std::shared_ptr<const Texture> texture, GLenum target)
	:	OGLResource (texture),
		m_Target (target),
		m_NumLevels (texture->GetNumLevels ()),
		m_InternalFormat (m_TableInternalFormat[texture->GetFormat ()]),
		m_ExternalFormat (m_TableExternalFormat[texture->GetFormat ()]),
		m_ExternalType (m_TableExternalType[DataAttributes::GetElementType (texture->GetFormat ())])
{

}

std::shared_ptr<Texture> OGLTexture::GetTexture () const
{
	return std::static_pointer_cast<Texture> (m_DPObject);
}

GLenum OGLTexture::GetTarget () const
{
	return m_Target;
}

GLuint const OGLTexture::m_TableInternalFormat[DP_MAX_CONTAINER_TYPE] =
{
	0, //DP_UNKNOWN,
	GL_RGBA32F, //DP_R32G32B32A32_FLOAT,
	GL_RGBA32UI, //DP_R32G32B32A32_UNSIGNED_INT,
	GL_RGBA32I, //DP_R32G32B32A32_SIGNED_INT,
	GL_RGB32F, //DP_R32G32B32_FLOAT,
	GL_RGB32UI, //DP_R32G32B32_UNSIGNED_INT,
	GL_RGB32I, //DP_R32G32B32_SIGNED_INT,
	GL_RGBA16F, //DP_R16G16B16A16_FLOAT,
	GL_RGBA16UI, //DP_R16G16B16A16_UNSIGNED_INT,
	GL_RGBA16, //DP_R16G16B16A16_UNSIGNED_NORM,
	GL_RGBA16I, //DP_R16G16B16A16_SIGNED_INT,
	GL_RGBA16_SNORM, //DP_R16G16B16A16_SIGNED_NORM,
	GL_RG32F, //DP_R32G32_FLOAT,
	GL_RG32UI, //DP_R32G32_UNSIGNED_INT,
	GL_RG32I, //DP_R32G32_SIGNED_INT,
	GL_RGBA8UI, //DP_R8G8B8A8_UNSIGNED_INT,
	GL_RGBA8, //DP_R8G8B8A8_UNSIGNED_NORM,
	GL_RGBA8I, //DP_R8G8B8A8_SIGNED_INT,
	GL_RGBA8_SNORM, //DP_R8G8B8A8_SIGNED_NORM,
	GL_RG16F, //DP_R16G16_FLOAT,
	GL_RG16UI, //DP_R16G16_UNSIGNED_INT,
	GL_RG16I, //DP_R16G16_SIGNED_INT,
	GL_DEPTH_COMPONENT32F, //DP_D32_FLOAT,
	GL_R32F, //DP_R32_FLOAT,
	GL_R32UI, //DP_R32_UNSIGNED_INT,
	GL_R32I, //DP_R32_SIGNED_INT,
	GL_DEPTH24_STENCIL8, //DP_D24_UNSIGNED_NORM_S8_UNSIGNED_INT,
	GL_RG8UI, //DP_R8G8_UNSIGNED_INT,
	GL_RG8,//DP_R8G8_UNSIGNED_NORM,
	GL_RG8I, //DP_R8G8_SIGNED_INT,
	GL_RG8_SNORM, //DP_R8G8_SIGNED_NORM,
	GL_R16F, //DP_R16_FLOAT,
	GL_DEPTH_COMPONENT16, //DP_D16_UNSIGNED_NORM,
	GL_R16UI, //DP_R16_UNSIGNED_INT,
	GL_R16, //DP_R16_UNSIGNED_NORM,
	GL_R16I, //DP_R16_SIGNED_INT,
	GL_R16_SNORM, //DP_R16_SIGNED_NORM,
	GL_R8UI, //DP_R8_UNSIGNED_INT,
	GL_R8, //DP_R8_UNSIGNED_NORM,
	GL_R8I, //DP_R8_SIGNED_INT,
	GL_R8_SNORM, //DP_R8_SIGNED_NORM,
};

GLuint const OGLTexture::m_TableExternalFormat[DP_MAX_CONTAINER_TYPE] = 
{
	0, //DP_UNKNOWN,
	GL_RGBA, //DP_R32G32B32A32_FLOAT,
	GL_RGBA_INTEGER, //DP_R32G32B32A32_UNSIGNED_INT,
	GL_RGBA_INTEGER, //DP_R32G32B32A32_SIGNED_INT,
	GL_RGB, //DP_R32G32B32_FLOAT,
	GL_RGB_INTEGER, //DP_R32G32B32_UNSIGNED_INT,
	GL_RGB_INTEGER, //DP_R32G32B32_SIGNED_INT,
	GL_RGBA, //DP_R16G16B16A16_FLOAT,
	GL_RGBA_INTEGER, //DP_R16G16B16A16_UNSIGNED_INT,
	GL_RGBA, //DP_R16G16B16A16_UNSIGNED_NORM,
	GL_RGBA_INTEGER, //DP_R16G16B16A16_SIGNED_INT,
	GL_RGBA, //DP_R16G16B16A16_SIGNED_NORM,
	GL_RG, //DP_R32G32_FLOAT,
	GL_RG_INTEGER, //DP_R32G32_UNSIGNED_INT,
	GL_RG_INTEGER, //DP_R32G32_SIGNED_INT,
	GL_RGBA_INTEGER, //DP_R8G8B8A8_UNSIGNED_INT,
	GL_RGBA, //DP_R8G8B8A8_UNSIGNED_NORM,
	GL_RGBA_INTEGER, //DP_R8G8B8A8_SIGNED_INT,
	GL_RGBA, //DP_R8G8B8A8_SIGNED_NORM,
	GL_RG, //DP_R16G16_FLOAT,
	GL_RG_INTEGER, //DP_R16G16_UNSIGNED_INT,
	GL_RG_INTEGER, //DP_R16G16_SIGNED_INT,
	GL_DEPTH_COMPONENT, //DP_D32_FLOAT,
	GL_RED, //DP_R32_FLOAT,
	GL_RED_INTEGER, //DP_R32_UNSIGNED_INT,
	GL_RED_INTEGER, //DP_R32_SIGNED_INT,
	GL_DEPTH_COMPONENT, //DP_D24_UNSIGNED_NORM_S8_UNSIGNED_INT,
	GL_RG_INTEGER, //DP_R8G8_UNSIGNED_INT,
	GL_RG,//DP_R8G8_UNSIGNED_NORM,
	GL_RG_INTEGER, //DP_R8G8_SIGNED_INT,
	GL_RG, //DP_R8G8_SIGNED_NORM,
	GL_RED, //DP_R16_FLOAT,
	GL_DEPTH_COMPONENT, //DP_D16_UNSIGNED_INT,
	GL_RED_INTEGER, //DP_R16_UNSIGNED_INT,
	GL_RED, //DP_R16_UNSIGNED_NORM,
	GL_RED_INTEGER, //DP_R16_SIGNED_INT,
	GL_RED, //DP_R16_SIGNED_NORM,
	GL_RED_INTEGER, //DP_R8_UNSIGNED_INT,
	GL_RED, //DP_R8_UNSIGNED_NORM,
	GL_RED_INTEGER, //DP_R8_SIGNED_INT,
	GL_RED, //DP_R8_SIGNED_NORM,
};

GLuint const OGLTexture::m_TableExternalType[DP_MAX_ELEMENT_TYPE] = 
{
	GL_ZERO, //DP_NO_TYPE,
	GL_HALF_FLOAT, //DP_HALF,
	GL_FLOAT, //DP_FLOAT,
	GL_INT, //DP_INT,
	GL_UNSIGNED_INT, //DP_U_INT,
	GL_BYTE, //DP_BYTE,
	GL_UNSIGNED_BYTE, //DP_U_BYTE,
	GL_SHORT, //DP_SHORT,
	GL_UNSIGNED_SHORT, //DP_U_SHORT,
};