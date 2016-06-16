#include "stdafx.h"
#include "shader.h"

Shader::Shader ()
{
	m_Type = DP_SHADER;
}

Shader::Shader (OGLReflection const& reflector, int type)
{
	auto & uniforms = reflector.GetUniforms ();

	for (auto uniform = uniforms.begin (); uniform != uniforms.end (); uniform ++)
	{
		if (uniform->referencedBy[type])
		{
			switch (uniform->type)
			{
				case GL_SAMPLER_1D:
                case GL_INT_SAMPLER_1D:
                case GL_UNSIGNED_INT_SAMPLER_1D:
					{
						m_Data[TextureSolo::shaderLookUp].push_back(Data(DP_TEXTURE_SOLO, uniform->name, uniform->location, 0));
						m_Data[SamplerState::shaderLookUp].push_back(Data(DP_SAMPLER_STATE, uniform->name, uniform->location, 0));
						break;
					}

                case GL_SAMPLER_2D:
                case GL_INT_SAMPLER_2D:
                case GL_UNSIGNED_INT_SAMPLER_2D:
					{
						m_Data[TextureSolo::shaderLookUp].push_back(Data(DP_TEXTURE_SOLO, uniform->name, uniform->location, 0));
						m_Data[SamplerState::shaderLookUp].push_back(Data(DP_SAMPLER_STATE, uniform->name, uniform->location, 0));
						break;
					}
				case GL_SAMPLER_2D_ARRAY:
                case GL_INT_SAMPLER_2D_ARRAY:
                case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
                    m_Data[TextureArray::shaderLookUp].push_back(Data(DP_TEXTURE_ARRAY, uniform->name, uniform->location, 0));
                    m_Data[SamplerState::shaderLookUp].push_back(Data(DP_SAMPLER_STATE, uniform->name, uniform->location, 0));
                    break;
			}
		}
	}
	
	auto & uniformBlocks = reflector.GetUniformBlocks ();
	int numReferences = 0;
	
	for (auto block = uniformBlocks.begin (); block != uniformBlocks.end (); block ++)
	{
		if (block->referencedBy[type])
		{
			++numReferences;
		}
	}

	if (numReferences > 0)
	{
		int index = UniformBuffer::shaderLookUp;
		
		m_VLayout.resize (numReferences);
		auto & uniforms = reflector.GetUniforms ();
		int blockIndex = 0;
		int layoutIndex = 0;
		for (auto block = uniformBlocks.begin (); block != uniformBlocks.end (); block ++)
		{
			if (block->referencedBy[type])
			{

				m_Data[index].push_back (Data (DP_UNIFORM_BUFFER, block->name, block->bufferBinding, block->bufferDataSize));

				for ( auto uniform = uniforms.begin (); uniform != uniforms.end (); uniform++)
				{
					if (uniform->blockIndex != blockIndex)
					{
						continue;
					}

					if (uniform->referencedBy[type])
					{
						Layout member;
						member.m_Name = uniform->name;
						member.m_NumElements = 0;
						member.m_Offset = uniform->offset;
			
						m_VLayout[layoutIndex].push_back (member);
					}
				}
				++layoutIndex;
			}
			++blockIndex;
		}	
	}

	m_Type = static_cast<DrawObjectType> (DP_SHADER + type + 1);
}

bool Shader::IsValid () const
{
	return true;
}

Shader::Data::Data(DrawObjectType inType, std::string const& inName, int inBindPoint, int inNumBytes)
	:	name (inName),
		bindPoint (inBindPoint),
		numBytes (inNumBytes),
		type (inType)
{

}

int Shader::Set (std::string const& name, std::shared_ptr<UniformBuffer> const& object)
{
	int count = 0;
	int index = UniformBuffer::shaderLookUp;
	for (auto data = m_Data[index].begin (); data != m_Data[index].end (); data++)
	{
		if (name == data->name)
		{
			data->object = object;
			object->SetLayout(m_VLayout[count]);
			return count;
		}
		++count;
	}
	return -1;
}

std::vector<Shader::Data> Shader::GetData (int lookUp) const
{
	return m_Data[lookUp];
}