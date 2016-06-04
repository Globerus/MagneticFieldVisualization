#ifndef OGL_REFLECTION_H
#define OGL_REFLECTION_H

#include "oglInclude.h"

class OGLReflection
{
public:
	OGLReflection (GLuint pHandle);

	enum 
	{
		ST_VERTEX,
		ST_FRAGMENT
	};

	struct Uniform
    {
        std::string name;
        GLint type;
        GLint location;
        GLint offset;
        GLint blockIndex;
        GLint referencedBy[2];
    };

	struct DataBlock 
	{
		std::string name;
		GLint bufferBinding;
		GLint bufferDataSize;
		GLint referencedBy[2];
	};

	GLuint GetProgramHandle () const;
	std::vector<DataBlock> const& GetUniformBlocks () const;
	std::vector<Uniform> const& GetUniforms () const;

private:
	void ReflectUniformBlocks (std::vector<DataBlock>& uniformBlock);
	void ReflectUniforms (std::vector<Uniform>& uniform);

private:
	GLuint m_Handle;
	std::vector<DataBlock> m_UniformBlock;
	std::vector<Uniform> m_Uniform;
};
#endif