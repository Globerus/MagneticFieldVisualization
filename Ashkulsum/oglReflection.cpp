#include "stdafx.h"
#include "oglReflection.h"

OGLReflection::OGLReflection (GLuint pHandle)
	:	m_Handle (pHandle)
{
	if (m_Handle > 0)
	{
		ReflectUniforms (m_Uniform);
		ReflectUniformBlocks (m_UniformBlock);
	}
	else
		fprintf (stderr, "The OGL reflection failed, because the input program is not correct.\n");
}

void OGLReflection::ReflectUniformBlocks (std::vector<DataBlock>& uniformBlock)
{
	GLint numUniformBlocks = 0;

	glGetProgramiv (m_Handle, GL_ACTIVE_UNIFORM_BLOCKS, &numUniformBlocks);

	if (numUniformBlocks > 0)
	{
		uniformBlock.resize (numUniformBlocks);

		GLenum properties[] =
		{
			GL_NAME_LENGTH,
            GL_BUFFER_DATA_SIZE,
            GL_REFERENCED_BY_VERTEX_SHADER,
            GL_REFERENCED_BY_FRAGMENT_SHADER
		};

		int const numProperties = sizeof(properties) / sizeof(int);

		

		for (int i = 0; i < numUniformBlocks; i++)
		{
			GLint results[numProperties] = { 0 };

			DataBlock& block = uniformBlock [i];

			glGetProgramResourceiv (m_Handle, GL_UNIFORM_BLOCK, i, numProperties, properties, numProperties, nullptr, results);

			GLint numBytes = results[0];
			GLchar* name = new GLchar [numBytes];

			glGetProgramResourceName (m_Handle, GL_UNIFORM_BLOCK, i, numBytes, nullptr, name);
			
			block.name = name;

			delete[] name;

			block.bufferBinding = glGetProgramResourceIndex(m_Handle, GL_UNIFORM_BLOCK, block.name.c_str());
			block.bufferDataSize = results[1];
			block.referencedBy[ST_VERTEX] = results[2];
			block.referencedBy[ST_FRAGMENT] = results[3];

		}
	}
}

void OGLReflection::ReflectUniforms (std::vector<Uniform>& uniform)
{
	GLint numUniforms = 0;

	glGetProgramiv (m_Handle, GL_ACTIVE_UNIFORMS, &numUniforms);

	if (numUniforms > 0)
	{
		uniform.resize (numUniforms);

		GLenum properties[] =
		{
			GL_NAME_LENGTH,
			GL_TYPE,
            GL_LOCATION,
            GL_OFFSET,
            GL_BLOCK_INDEX,
            GL_REFERENCED_BY_VERTEX_SHADER,
            GL_REFERENCED_BY_FRAGMENT_SHADER
		};

		int const numProperties = sizeof(properties) / sizeof(int);

		GLint results[numProperties] = { 0 };

		for (int i = 0; i < numUniforms; i++)
		{
			Uniform&  member = uniform[i];

			glGetProgramResourceiv (m_Handle, GL_UNIFORM, i, numProperties, properties, numProperties, nullptr, results);

			GLint numBytes = results[0];
			GLchar* name = new GLchar [numBytes];

			glGetProgramResourceName (m_Handle, GL_UNIFORM, i, numBytes, nullptr, name);

			member.name = name;

			delete[] name;
		
			member.type = results[1];
			member.location = results[2];
			member.offset = results[3];
			member.blockIndex = results[4];
			member.referencedBy[0] = results[5];
			member.referencedBy[1] = results[6];

			if (GL_INVALID_INDEX == member.blockIndex)
			{
				member.location = glGetUniformLocation (m_Handle, member.name.c_str ());
			}
		}
	}
}

std::vector<OGLReflection::DataBlock> const& OGLReflection::GetUniformBlocks () const
{
	return m_UniformBlock;
}

std::vector<OGLReflection::Uniform> const& OGLReflection::GetUniforms () const
{
	return m_Uniform;
}