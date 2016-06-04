#pragma once
#ifndef SHADOWMAPFBO
#define SHADOWMAPFBO
#include <glload\gl_3_3.h>
#include <glload\gl_load.hpp>
#include <glutil\glutil.h>

class ShadowMapFBO {
	public:
		ShadowMapFBO();
		~ShadowMapFBO();

		bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
		void BindForWriting();
		void BindForReading(GLenum TextureUnit);

	private:
		GLuint m_fbo;
        GLuint m_shadowMap;
	};
#endif