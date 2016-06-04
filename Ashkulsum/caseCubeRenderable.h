#ifndef CASE_CUBE_RENDERABLE_H
#define CASE_CUBE_RENDERABLE_H

#include "caseCube.h"
#include "renderableObject.h"
#include <boost\make_shared.hpp>
#include <glload\gl_3_3.h>
#include <glload\gl_load.hpp>
#include <glutil\glutil.h>

class CaseCubeRenderable : public RenderableObject<CaseCube>
{
public:
	typedef boost::shared_ptr<CaseCubeRenderable> SharedPtr;

	CaseCubeRenderable (CaseCube::SharedPtr object);

	void InitBuffers (CaseCube::SharedPtr object);
	void BindBuffers ();
	GLuint LoadShaderProgram (CaseCube::SharedPtr object);

	void SetVAO (GLuint vao);
	void SetVBO (GLuint vbo);
	void SetNBO (GLuint nbo);
	void SetTBO (GLuint tbo);
	void SetShaderProgram (ShaderProgram::SharedPtr sProgram);

	GLuint GetVAO ();
	GLuint GetVBO ();
	GLuint GetNBO ();
	GLuint GetTBO ();
	ShaderProgram::SharedPtr GetShaderProgram ();

protected:
	virtual void Render (Renderer &renderer, CaseCube::SharedPtr object);

private:
	GLuint m_Vao, m_Vbo, m_Nbo, m_Tbo;
	ShaderProgram::SharedPtr m_SProgram;

};
#endif