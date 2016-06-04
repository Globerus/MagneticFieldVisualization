#include "stdafx.h"
#include "oglEngine.h"

OpenGLEngine::OpenGLEngine ()
{
	Initialize ();
}

OpenGLEngine::~OpenGLEngine ()
{

}

void OpenGLEngine::Initialize ()
{
	m_ClearDepth = 1.0f;
	m_ClearColor = glm::vec4 (0.5f, 0.5f, 0.5f, 1.0f);
	SetViewport (glm::vec4 (0.0f, 0.0f, 0.0f, 0.0f));
	SetDepthRange (0.0f, 1.0f);

	m_DefaultBlendState = std::make_shared<BlendState> ();
	m_DefaultDepthStencilState = std::make_shared<DepthStencilState> ();
	m_DefaultRasterizerState = std::make_shared<RasterizerState> ();

	SetDefaultBlendState();
    SetDefaultDepthStencilState();
    SetDefaultRasterizerState();
}

void OpenGLEngine::SetViewport (glm::vec4 viewPort)
{
	m_Viewport.m_BotLeftX = viewPort.x;
	m_Viewport.m_BotLeftY = viewPort.y;
	m_Viewport.m_Width = viewPort.z;
	m_Viewport.m_Height = viewPort.w;

	glViewport ((int)viewPort.x, (int)viewPort.y, (int)viewPort.z, (int)viewPort.w);
}

void OpenGLEngine::GetViewport (int & x, int & y, int & width, int & height)
{
	x = (int)m_Viewport.m_BotLeftX;
	y = (int)m_Viewport.m_BotLeftY;
	width = (int)m_Viewport.m_Width;
	height = (int)m_Viewport.m_Height;
}

void OpenGLEngine::SetDepthRange (float nearVal, float farVal)
{
	m_DepthRange.m_Near = nearVal;
	m_DepthRange.m_Far = farVal;

	glDepthRangef (nearVal, farVal);
}

void OpenGLEngine::SetClearColour (glm::vec4 clearColour)
{
	m_ClearColor = clearColour;
}

void OpenGLEngine::ClearColorBuffer ()
{
	glClearColor (m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
	
}

void OpenGLEngine::ClearDepthBuffer ()
{
	glClearDepth (m_ClearDepth);
	glClear (GL_DEPTH_BUFFER_BIT);	
}

void OpenGLEngine::ClearBuffers ()
{
	
	glClearColor (m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
	glClearDepth (m_ClearDepth);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	
}

void OpenGLEngine::SetEnable (GLenum glEnum)
{
	glEnable (glEnum);
}

void OpenGLEngine::SetDisable (GLenum glEnum)
{
	glDisable (glEnum);
}

void OpenGLEngine::SetCullFace (GLenum glEnum)
{
	glCullFace (glEnum);
}

void OpenGLEngine::SetFrontFace (GLenum glEnum)
{
	glFrontFace (glEnum);
}

void OpenGLEngine::SetDepthFunc (GLenum glEnum)
{
	glDepthFunc (glEnum);
}

void OpenGLEngine::SetDepthMask (GLenum glEnum)
{
	glDepthMask (glEnum);
}

void OpenGLEngine::SetCullBackFace ()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void OpenGLEngine::SetCullFrontFace ()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
}

void OpenGLEngine::SetFont (std::shared_ptr<Font> const& font)
{
	if (font)
	{
		if (font != m_ActiveFont)
		{
			if (m_ActiveFont)
			{
				Unbind(m_ActiveFont->GetVertexBuffer());
                Unbind(m_ActiveFont->GetIndexBuffer());
				Unbind(m_ActiveFont->GetVertexBuffer(), m_ActiveFont->GetIndexBuffer());
                Unbind(m_ActiveFont->GetTextEffect()->GetTranslate());
                Unbind(m_ActiveFont->GetTextEffect()->GetColor());
			}

			m_ActiveFont = font;
		}
	}
	else
	{
		fprintf (stderr, "The setFont method in OpenGLEngine failed, because the input argument is not correct.\n");
	}
}


void OpenGLEngine::SetBlendState (std::shared_ptr<BlendState> const& blendState)
{
	if (blendState)
	{
		if (blendState != m_ActiveBlendState)
		{
			std::shared_ptr<OGLBlendState> oglBlendState = std::static_pointer_cast<OGLBlendState> (Bind (blendState));
			if (oglBlendState)
			{
				oglBlendState->Enable ();
				m_ActiveBlendState = blendState;
			}
			else
			{
				fprintf (stderr, "The setBlendState method in OpenGLEngine failed, because the oglBlendState object was created incorrectly.\n");
			}
		}
	}
	else
	{
		fprintf (stderr, "The setBlendState method in OpenGLEngine failed, because the input argument is incorrect.\n");
	}
}

void OpenGLEngine::SetDepthStencilState (std::shared_ptr<DepthStencilState> const& depthStencilState)
{
	if (depthStencilState)
	{
		if (depthStencilState != m_ActiveDepthStencilState)
		{
			std::shared_ptr<OGLDepthStencilState> oglDepthStencilState = std::static_pointer_cast<OGLDepthStencilState> (Bind (depthStencilState));
			if (oglDepthStencilState)
			{
				oglDepthStencilState->Enable ();
				m_ActiveDepthStencilState = depthStencilState;
			}
			else
			{
				fprintf (stderr, "The setDepthStencilState method in OpenGLEngine failed, because the oglBlendState object was created incorrectly.\n");
			}
		}
	}
	else
	{
		fprintf (stderr, "The setDepthStencilState method in OpenGLEngine failed, because the input argument is incorrect.\n");
	}
}

void OpenGLEngine::SetRasterizerState (std::shared_ptr<RasterizerState> const& rasterizerState)
{
	if (rasterizerState)
	{
		if (rasterizerState != m_ActiveRasterizerState)
		{
			std::shared_ptr<OGLRasterizerState> oglRasterizerState = std::static_pointer_cast<OGLRasterizerState> (Bind (rasterizerState));
			if (oglRasterizerState)
			{
				oglRasterizerState->Enable ();
				m_ActiveRasterizerState = rasterizerState;
			}
			else
			{
				fprintf (stderr, "The setRasterizerState method in OpenGLEngine failed, because the oglBlendState object was created incorrectly.\n");
			}
		}
	}
	else
	{
		fprintf (stderr, "The setRasterizerState method in OpenGLEngine failed, because the input argument is incorrect.\n");
	}
}

std::shared_ptr<OGLDrawObject> OpenGLEngine::Bind (std::shared_ptr<DrawObject> const& dObject)
{
	if (!dObject)
	{
		fprintf (stderr, "The bind method in OpenGLEngine failed, because the input argument is not correct.\n");
		return nullptr;
	}
	
	std::shared_ptr<OGLDrawObject> oglObject;
	if (!m_MapDO.Get (dObject, oglObject))
	{
		CreateOGLObject create = m_CreateOGLObject[dObject->GetType ()];
		if (!create)
		{
			fprintf (stderr, "The bind method in OpenGLEngine failed, because a create function was not found.\n");
			return nullptr;
		}

		oglObject = create (dObject);

		if (!oglObject)
		{
			fprintf (stderr, "The bind method in OpenGLEngine failed, because the created OGL Object was not correct.\n");
		}

		m_MapDO.Insert (dObject, oglObject);
	}

	return oglObject;
}

std::shared_ptr<OGLDrawTarget> OpenGLEngine::Bind (std::shared_ptr<DrawTarget> const& dTarget)
{
	if (!dTarget)
	{
		fprintf (stderr, "The bind method in OpenGLEngine failed, because the input argument is not correct.\n");
		return nullptr;
	}
	std::shared_ptr<OGLDrawTarget> oglTarget;
	if (!m_MapDT.Get (dTarget, oglTarget))
	{
		auto const numTargets = dTarget->GetNumTargets ();
		std::vector<std::shared_ptr<OGLDrawObject>> rtTextures (numTargets);

		for (unsigned int i = 0; i < numTargets; i++)
		{
			rtTextures[i] = std::static_pointer_cast<OGLDrawObject> (Bind (dTarget->GetRTTexture (i)));
		}

		std::shared_ptr<OGLDrawObject> dsTexture = std::static_pointer_cast<OGLDrawObject> (Bind (dTarget->GetDSTexture ()));

		oglTarget = m_CreateOGLDrawTarget (dTarget, rtTextures, dsTexture);
		m_MapDT.Insert (dTarget, oglTarget);
	}

	return oglTarget;
}

OGLVertexArrayObject* OpenGLEngine::Bind (std::shared_ptr<OGLVertexBuffer> const& oglVBuffer, std::shared_ptr<OGLIndexBuffer> const& oglIBuffer)
{
	if (!oglVBuffer || !oglIBuffer)
	{
		fprintf (stderr, "The bind method in OpenGLEngine failed, because the input arguments are not correct.\n");
		return nullptr;
	}

	std::shared_ptr<VertexBuffer> vBuffer = std::static_pointer_cast<VertexBuffer> (oglVBuffer->GetDrawObject ());
	std::shared_ptr<IndexBuffer> iBuffer = std::static_pointer_cast<IndexBuffer> (oglIBuffer->GetDrawObject ());

	OGLVertexArrayObject* co;

	if (vBuffer)
	{
		if (!m_MapCO.Get (std::make_pair(vBuffer.get(), iBuffer.get ()), co))
			{
				co = new OGLVertexArrayObject (oglVBuffer, oglIBuffer);

				if (!co)
				{
					fprintf (stderr, "The bind method in OpenGLEngine failed, because the created OGL Object was not correct.\n");
					return nullptr;
				}

				m_MapCO.Insert (std::make_pair(vBuffer.get(), iBuffer.get ()), co);
			}
	}
	return co;
}

std::shared_ptr<OGLDrawObject> OpenGLEngine::Get (std::shared_ptr<DrawObject> const& dObject)
{
	if (!dObject)
	{
		fprintf (stderr, "The get method in OpenGLEngine failed, because the input argument is not correct.\n");
		return nullptr;
	}
	
	std::shared_ptr<OGLDrawObject> oglObject;

	if (m_MapDO.Get (dObject, oglObject))
	{
		return oglObject;
	}

	fprintf (stderr, "The get method in OpenGLEngine failed, because an oglObject was not found.\n");
	return nullptr;
}

std::shared_ptr<OGLDrawTarget> OpenGLEngine::Get (std::shared_ptr<DrawTarget> const& dTarget)
{
	if (!dTarget)
	{
		fprintf (stderr, "The get method in OpenGLEngine failed, because the input argument is not correct.\n");
		return nullptr;
	}
	
	std::shared_ptr<OGLDrawTarget> oglTarget;

	if (m_MapDT.Get (dTarget, oglTarget))
	{
		return oglTarget;
	}

	fprintf (stderr, "The get method in OpenGLEngine failed, because an oglTarget was not found.\n");
	return nullptr;
}

bool OpenGLEngine::Unbind (std::shared_ptr<DrawObject> const& dObject)
{
	if (!dObject)
	{
		fprintf (stderr, "The unbind method in OpenGLEngine failed, because the input argument is not correct.\n");
		return nullptr;
	}
	
	std::shared_ptr<OGLDrawObject> oglObject;
	if (m_MapDO.Get (dObject, oglObject))
	{
		m_MapDO.Remove (dObject, oglObject);
		return true;
	}

	return false;
}

bool OpenGLEngine::Unbind (std::shared_ptr<DrawTarget> const& dTarget)
{
	if (!dTarget)
	{
		fprintf (stderr, "The unbind method in OpenGLEngine failed, because the input argument is not correct.\n");
		return nullptr;
	}
	
	std::shared_ptr<OGLDrawTarget> oglTarget;
	if (m_MapDT.Get (dTarget, oglTarget))
	{
		m_MapDT.Remove (dTarget, oglTarget);
		return true;
	}

	return false;
}


bool OpenGLEngine::Unbind (std::shared_ptr<VertexBuffer> const& vBuffer, std::shared_ptr<IndexBuffer> const& iBuffer)
{
	if (!vBuffer || !iBuffer)
	{
		fprintf (stderr, "The unbind method in OpenGLEngine failed, because the input argument is not correct.\n");
		return nullptr;
	}

	OGLVertexArrayObject* oglVarray;
	if (m_MapCO.Get (std::make_pair(vBuffer.get(), iBuffer.get()), oglVarray))
	{
		m_MapCO.Remove (std::make_pair(vBuffer.get(), iBuffer.get()), oglVarray);
		return true;
	}

	return false;
}

void OpenGLEngine::Draw (std::shared_ptr<GeometryNode> const& geometryNode)
{
	Draw (geometryNode.get ());
}

void OpenGLEngine::Draw (GeometryNode const* geometryNode)
{
	if (geometryNode)
	{
		auto const& vertexBuffer = geometryNode->GetVertexBuffer ();
		auto const& instancedBuffer = geometryNode->GetInstancedBuffer ();
		auto const& indexBuffer = geometryNode->GetIndexBuffer ();
		auto const& visualEffect = geometryNode->GetVisualEffect ();

		if (vertexBuffer && indexBuffer && visualEffect)
		{
			if (instancedBuffer)
				Draw (vertexBuffer, instancedBuffer, indexBuffer, visualEffect);
			else
				Draw (vertexBuffer, indexBuffer, visualEffect);
		}
	}
	else
	{
		fprintf (stderr, "The draw method in OpenGLEngine failed, because the input argument is not correct.\n");
	}
}

void OpenGLEngine::Draw (std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<VisualEffect> visualEffect)
{
	std::shared_ptr<Program> program = visualEffect->GetProgram ();
	std::string programName = program->GetProgramName ();

	OGLProgram* oglProgram = dynamic_cast<OGLProgram*> (program.get());

	if (oglProgram)
	{
		GLuint programHandle = oglProgram->GetProgramHandle ();
		glUseProgram (programHandle);
	
		if (EnableShaders (visualEffect, programHandle))
		{
			std::shared_ptr<OGLVertexBuffer> oglVertexBuffer = nullptr;
			std::shared_ptr<OGLIndexBuffer> oglIndexBuffer = nullptr;
			OGLVertexArrayObject* vao = nullptr;

			m_MapCO.Get (std::make_pair (vertexBuffer.get(), indexBuffer.get ()), vao);
			if (vao)
			{
				vao->Enable ();
			}
			else
			{

				if (vertexBuffer)
				{
					oglVertexBuffer = std::static_pointer_cast<OGLVertexBuffer> (Bind (vertexBuffer));
				}

				if (indexBuffer)
				{
					oglIndexBuffer = std::static_pointer_cast<OGLIndexBuffer> (Bind(indexBuffer));
				}

				vao = static_cast<OGLVertexArrayObject*> (Bind (oglVertexBuffer, oglIndexBuffer));

			}

			DrawPrimitive (vertexBuffer.get (), indexBuffer.get ());

			vao->Disable ();

			DisableShaders (visualEffect, programHandle);
		}
		else
		{
			fprintf (stderr, "The draw method in OpenGLEngine failed, because the OGL Program was not correct.\n");
		}
	}
}

void OpenGLEngine::Draw (std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<VertexBuffer> instancedBuffer, std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<VisualEffect> visualEffect)
{
	std::shared_ptr<Program> program = visualEffect->GetProgram ();
	std::string programName = program->GetProgramName ();

	OGLProgram* oglProgram = dynamic_cast<OGLProgram*> (program.get());

	if (oglProgram)
	{
		GLuint programHandle = oglProgram->GetProgramHandle ();
		glUseProgram (programHandle);
	
		if (EnableShaders (visualEffect, programHandle))
		{
			std::shared_ptr<OGLVertexBuffer> oglVertexBuffer = nullptr;
			std::shared_ptr<OGLVertexBuffer> oglInstancedBuffer = nullptr;
			std::shared_ptr<OGLIndexBuffer> oglIndexBuffer = nullptr;
			OGLVertexArrayObject* vao = nullptr;

			m_MapCO.Get (std::make_pair (vertexBuffer.get(), indexBuffer.get ()), vao);
			if (vao)
			{
				vao->Enable ();
			}
			else
			{

				if (vertexBuffer)
				{
					oglVertexBuffer = std::static_pointer_cast<OGLVertexBuffer> (Bind (vertexBuffer));
				}

				if (indexBuffer)
				{
					oglIndexBuffer = std::static_pointer_cast<OGLIndexBuffer> (Bind(indexBuffer));
				}

				vao = static_cast<OGLVertexArrayObject*> (Bind (oglVertexBuffer, oglIndexBuffer));

				oglInstancedBuffer = std::static_pointer_cast<OGLVertexBuffer> (Bind (instancedBuffer));
				oglInstancedBuffer->Enable ();

				VertexAttributes vertexAttrib = vertexBuffer->GetVertexAttrib ();
				VertexAttributes instancedAttrib = instancedBuffer->GetVertexAttrib ();

				int vertexBufferNumAttrib = vertexAttrib.GetNumAttrib ();
				int instancedBufferNumAttrib = instancedAttrib.GetNumAttrib ();

				for (int i = vertexBufferNumAttrib; i < vertexBufferNumAttrib + instancedBufferNumAttrib; i++)
				{
					ContainerType type = instancedAttrib.GetContainerType (i - vertexBufferNumAttrib);
					int offset = instancedAttrib.GetOffset(i - vertexBufferNumAttrib);
		
					int numElements = DataAttributes::GetNumElement (type);	
					GLenum channelType = oglInstancedBuffer->m_ChannelType[DataAttributes::GetElementType (type)];
					size_t vertSize = instancedAttrib.GetVertexSize ();

					glEnableVertexAttribArray (i);
		
					glVertexAttribPointer (i, numElements, channelType, GL_FALSE, vertSize, (void*)offset);

					glVertexAttribDivisor (i, 1);
				}
				
			}

			DrawPrimitive (vertexBuffer.get (), instancedBuffer.get (), indexBuffer.get ());

			vao->Disable ();

			DisableShaders (visualEffect, programHandle);
		}
		else
		{
			fprintf (stderr, "The draw method in OpenGLEngine failed, because the OGL Program was not correct.\n");
		}
	}
}
void OpenGLEngine::Draw (int x, int y, glm::vec4 const& color, std::string const& message)
{
	if (message.length () > 0)
	{
		int vx, vy, vw, vh;

		GetViewport (vx, vy, vw, vh);

		m_ActiveFont->SetStringData (vw, vh, x, y, color, message);

		Update (m_ActiveFont->GetTextEffect () ->GetTranslate ());
		Update (m_ActiveFont->GetTextEffect () ->GetColor ());
		Update (m_ActiveFont->GetVertexBuffer ());

		std::shared_ptr<BlendState> blendState = GetBlendState ();
		std::shared_ptr<DepthStencilState> depthState = GetDepthStencilState ();
		std::shared_ptr<RasterizerState> rasterizerState = GetRasterizerState ();

		SetDefaultBlendState ();
		SetDefaultDepthStencilState ();
		SetDefaultRasterizerState ();

		Draw (m_ActiveFont->GetVertexBuffer (), m_ActiveFont->GetIndexBuffer (), m_ActiveFont->GetTextEffect ());
		
		SetBlendState (blendState);
		SetDepthStencilState (depthState);
		SetRasterizerState (rasterizerState);
	}
}

void OpenGLEngine::DrawPrimitive (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer) const
{
	GLenum primitiveType = m_PTypeTable[iBuffer->GetPrimitiveType ()];
	
	if (iBuffer->IsIndexed ())
	{
		int numActivePrimitives = iBuffer->GetNumActivePrimitives ();

		unsigned int indexSize = iBuffer->GetElementSize ();

		GLenum indexType = indexSize == 4 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT;
		glDrawElements (primitiveType, numActivePrimitives, indexType, 0);

	}
	else
	{
		int numElements = vBuffer->GetNumElements ();

		glDrawArrays (primitiveType, 0, numElements);
	}
}

void OpenGLEngine::DrawPrimitive (VertexBuffer const* vBuffer, VertexBuffer const* instancedBuffer, IndexBuffer const* iBuffer) const
{
	int numInstances = instancedBuffer->GetNumActiveElements ();

	GLenum primitiveType = m_PTypeTable[iBuffer->GetPrimitiveType ()];
	
	if (iBuffer->IsIndexed ())
	{
		int numActivePrimitives = iBuffer->GetNumActivePrimitives ();

		unsigned int indexSize = iBuffer->GetElementSize ();

		GLenum indexType = indexSize == 4 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT;
		glDrawElementsInstanced (primitiveType, numActivePrimitives, indexType, 0, numInstances);
	}
	else
	{
		int numElements = vBuffer->GetNumElements ();
		glDrawArraysInstanced (primitiveType, 0, numElements, numInstances);
	}
}

bool OpenGLEngine::EnableShaders (std::shared_ptr<VisualEffect> vEffect, GLuint program)
{
	auto vShader = vEffect->GetVertexShader ().get ();
	
	if (!vShader)
	{
		fprintf (stderr, "The enable shaders method in OpenGLEngine failed, because the vertex shader is not correct.\n");
		return false;
	}
	
	Enable (vShader, program);

	auto fShader = vEffect->GetFragmentShader ().get ();

	if (!fShader)
	{
		fprintf (stderr, "The enable shaders method in OpenGLEngine failed, because the fragment shader is not correct.\n");
		return false;
	}

	Enable (fShader, program);

	return true;
}

void OpenGLEngine::DisableShaders (std::shared_ptr<VisualEffect> vEffect, GLuint program)
{
	auto vShader = vEffect->GetVertexShader ().get();
	auto fShader = vEffect->GetFragmentShader ().get();

	Disable (fShader, program);
	Disable (vShader, program);
}

void OpenGLEngine::Enable (Shader const* shader, GLuint program)
{
	EnableUniformBuffers (shader, program);
	EnableTextures (shader, program);
	EnableSamplers (shader, program);
}

void OpenGLEngine::Disable (Shader const* shader, GLuint program)
{
	DisableSamplers (shader, program);
	DisableTextures (shader, program);
	DisableUniformBuffers (shader, program);	
}

void OpenGLEngine::EnableUniformBuffers (Shader const* shader, GLuint program)
{
	auto const uniformBuffers = shader->GetData (UniformBuffer::shaderLookUp);
	for (auto buffer = uniformBuffers.begin (); buffer != uniformBuffers.end (); buffer ++)
	{
		if (buffer->object)
		{
			std::shared_ptr<OGLUniformBuffer> ub = std::static_pointer_cast<OGLUniformBuffer> (Bind (buffer->object));

			if (ub)
			{
				int unit = m_ProgramUnitMap.AskConnectionUnit (program, buffer->bindPoint);
				glUniformBlockBinding(program, buffer->bindPoint, unit);
				ub->BindData (buffer->bindPoint, unit);
			}
			else
			{
				fprintf (stderr, "The enable uniform buffers method in OpenGLEngine failed, because the binding of the object failed.\n");
			}
		}
		else
		{
			fprintf (stderr, "The enable uniform buffers method in OpenGLEngine failed, because the object in the buffer is null.\n");
		}
	}
}

void OpenGLEngine::DisableUniformBuffers (Shader const* shader, GLuint program)
{
	auto const uniformBuffers = shader->GetData (UniformBuffer::shaderLookUp);
	for (auto buffer = uniformBuffers.begin (); buffer != uniformBuffers.end (); buffer ++)
	{
		auto blockIndex = buffer->bindPoint;
		if (blockIndex != GL_INVALID_INDEX)
		{
			auto unit = m_ProgramUnitMap.GetUnit (program, blockIndex);
			glBindBufferBase (GL_UNIFORM_BUFFER, unit, 0);
			m_ProgramUnitMap.ReleaseUnit (unit);
		}
	}
}

void OpenGLEngine::EnableTextures (Shader const* shader, GLuint program)
{
	auto const textures = shader->GetData (TextureSolo::shaderLookUp);
	for (auto texture = textures.begin (); texture != textures.end (); texture ++)
	{
		if (texture->object)
		{
			std::shared_ptr<OGLTextureSolo> oglTex = std::static_pointer_cast<OGLTextureSolo> (Bind (texture->object));

			if (oglTex)
			{

				auto target = oglTex->GetTarget ();
				auto oglObject = oglTex->GetOGLDrawObject ();

				auto location = texture->bindPoint;
				int unit = m_TextureUnitMap.AskConnectionUnit (program, location);
				glProgramUniform1i (program, location, unit);
				glActiveTexture (GL_TEXTURE0 + unit);
				glBindTexture (target, oglObject);
			}
			else
			{
				fprintf (stderr, "The enable textures method in OpenGLEngine failed, because the binding of the object failed.\n");
			}
		}
		else
		{
			fprintf (stderr, "The enable textures method in OpenGLEngine failed, because the object in the buffer is null.\n");
		}
	}
}

void OpenGLEngine::DisableTextures (Shader const* shader, GLuint program)
{
	auto const textures = shader->GetData (TextureSolo::shaderLookUp);
	for (auto texture = textures.begin (); texture != textures.end (); texture ++)
	{
		std::shared_ptr<OGLTextureSolo> oglTex = std::static_pointer_cast<OGLTextureSolo> (Get (texture->object));

		if (oglTex)
		{
			auto target = oglTex->GetTarget ();

			auto location = texture->bindPoint;
			int unit = m_TextureUnitMap.GetUnit (program, location);
			glActiveTexture (GL_TEXTURE0 + unit);
			glBindTexture (target, 0);
			m_TextureUnitMap.ReleaseUnit (unit);
		}
	}
}

void OpenGLEngine::EnableSamplers (Shader const* shader, GLuint program)
{
	auto const samplers = shader->GetData (SamplerState::shaderLookUp);
	for (auto sampler = samplers.begin (); sampler != samplers.end (); sampler ++)
	{
		if (sampler->object)
		{
			std::shared_ptr<OGLSamplerState> oglSampler = std::static_pointer_cast<OGLSamplerState> (Bind (sampler->object));

			if (oglSampler)
			{
				auto location = sampler->bindPoint;
				int unit = m_TextureUnitMap.AskConnectionUnit (program, location);
				glBindSampler (unit, oglSampler->GetOGLDrawObject());
			}
			else
			{
				fprintf (stderr, "The enable samplers method in OpenGLEngine failed, because the binding of the object failed.\n");
			}
		}
		else
		{
			fprintf (stderr, "The enable samplers method in OpenGLEngine failed, because the object in the buffer is null.\n");
		}
	}
}

void OpenGLEngine::DisableSamplers (Shader const* shader, GLuint program)
{
	auto const samplers = shader->GetData (SamplerState::shaderLookUp);
	for (auto sampler = samplers.begin (); sampler != samplers.end (); sampler ++)
	{
		std::shared_ptr<OGLSamplerState> oglSampler = std::static_pointer_cast<OGLSamplerState> (Get (sampler->object));

		if (oglSampler)
		{
			auto location = sampler->bindPoint;
			int unit = m_TextureUnitMap.GetUnit (program, location);
			glBindSampler (unit, 0);
			m_TextureUnitMap.ReleaseUnit (unit);
		}
	}
}

bool OpenGLEngine::Update (std::shared_ptr<Buffer> const& buffer)
{
	if (!buffer->GetData ())
	{
		fprintf(stderr, "The update method in OpenGLEngine failed, because there is no loaded data for the buffer.\n");
		buffer->CreateStorage ();
	}

	auto oglBuffer = std::static_pointer_cast<OGLBuffer> (Bind (buffer));
	return oglBuffer->Update ();
}

bool OpenGLEngine::Update (std::shared_ptr<TextureSolo> const& texture)
{
	if (!texture->GetData ())
	{
		fprintf(stderr, "The update method in OpenGLEngine failed, because there is no loaded data for the texture.\n");
		texture->CreateStorage ();
	}

	auto oglTexture = std::static_pointer_cast<OGLTextureSolo> (Bind (texture));
	return oglTexture->Update ();
}

bool OpenGLEngine::Update (std::shared_ptr<TextureSolo> const& texture, int level)
{
	if (!texture->GetData ())
	{
		fprintf(stderr, "The update method in OpenGLEngine failed, because there is no loaded data for the texture.\n");
		texture->CreateStorage ();
	}

	auto oglTexture = std::static_pointer_cast<OGLTextureSolo> (Bind (texture));
	return oglTexture->Update (level);
}

void OpenGLEngine::Enable (std::shared_ptr<DrawTarget> const& dTarget)
{
	auto oglTarget = std::static_pointer_cast<OGLDrawTarget> (Bind (dTarget)); 
	oglTarget->Enable ();
}

void OpenGLEngine::Disable (std::shared_ptr<DrawTarget> const& dTarget)
{
	auto oglTarget = std::static_pointer_cast<OGLDrawTarget> (Get (dTarget)); 
	if (oglTarget)
		oglTarget->Disable ();
}

GLenum const OpenGLEngine::m_PTypeTable [P_NUM_TYPES] =
{
	GL_POINTS,
	GL_LINES,
	GL_TRIANGLES,
	GL_TRIANGLE_STRIP
};

OpenGLEngine::CreateOGLObject const OpenGLEngine::m_CreateOGLObject [DP_NUM_TYPES] =
{
	nullptr,
	nullptr,
	nullptr,
	&OGLVertexBuffer::Create,
	&OGLIndexBuffer::Create,
	&OGLUniformBuffer::Create,
	nullptr,
	nullptr,
	&OGLTexture1::Create,
	&OGLTexture2::Create,
	&OGLTextureRT::Create,
	&OGLTextureDS::Create,
	nullptr,
	&OGLBlendState::Create,
	&OGLDepthStencilState::Create,
	&OGLRasterizerState::Create,
	&OGLSamplerState::Create,
	nullptr,
	nullptr,
	nullptr
};

OpenGLEngine::CreateOGLDrawTarget const OpenGLEngine::m_CreateOGLDrawTarget  = &OGLDrawTarget::Create;
/*
bool OpenGLEngine::SubscribeAsDrawObject (std::shared_ptr<GeometryNode> node)
{
	if (node->m_IsDrawable)
	{
		m_DrawingSet.push_back (node);
		return true;
	}

	return false;
}

bool OpenGLEngine::UnsubscribeDrawObject (std::shared_ptr<GeometryNode> node)
{
	if (node->m_IsDrawable)
	{
		int pos = std::find (m_DrawingSet.begin (), m_DrawingSet.end (), node) - m_DrawingSet.begin ();
		if (pos <= m_DrawingSet.size ())
		{
				m_DrawingSet.erase (m_DrawingSet.begin () + pos);
				return true;
		}
	}

	return false;
}

std::vector<std::shared_ptr<GeometryNode>> OpenGLEngine::GetDrawingSet ()
{
	return m_DrawingSet;
}

bool OpenGLEngine::MapViewport (std::shared_ptr<GeometryNode> geometryNode, glm::vec4 viewPort)
{
	if (geometryNode)
	{
		m_MapVP.Insert (geometryNode.get(), viewPort);
		return true;
	}

	return false;
}

bool OpenGLEngine::GetMappedViewport (std::shared_ptr<GeometryNode> geometryNode, glm::vec4& viewPort)
{
	if (m_MapVP.Get (geometryNode.get(), viewPort))
	{
		return true;
	}

	return false;
}

bool OpenGLEngine::UnmapViewport (std::shared_ptr<GeometryNode> geometryNode)
{
	if(m_MapVP.Exists (geometryNode.get()))
	{
		glm::vec4 viewPort;
		m_MapVP.Remove (geometryNode.get(), viewPort);
		return true;
	}

	return false;
}

bool OpenGLEngine::RemapViewport (std::shared_ptr<GeometryNode> geometryNode, glm::vec4 viewPort)
{
	if (m_MapVP.Exists (geometryNode.get()))
	{
		if (m_MapVP.Update (geometryNode.get(), viewPort))
		{
			return true;
		}
	}
	return false;
}*/