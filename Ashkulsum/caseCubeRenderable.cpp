#include "stdafx.h"
#include "caseCubeRenderable.h"

CaseCubeRenderable::CaseCubeRenderable (CaseCube::SharedPtr caseCube) : RenderableObject<CaseCube>::RenderableObject (caseCube) 
{
	InitBuffers (caseCube);
	BindBuffers ();
}

void CaseCubeRenderable::InitBuffers (CaseCube::SharedPtr object)
{
	std::string meshName = object->GetMesh ();
	ResourceManager::SharedPtr rsrcManager = ResourceManager::GetInstance ();

	Mesh::SharedPtr mesh = rsrcManager->GetResource<Mesh> (meshName)->GetPtr ();

	const std::vector <glm::vec3> vertices = mesh->GetVertices ();
	if (!vertices.empty ())
	{
		GLuint vertexBufferObject;
		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, vertices.size ()*sizeof (glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		SetVBO (vertexBufferObject);
	}		

	const std::vector <glm::vec3> vertexNormals = mesh->GetVertexNormals ();
	if (!vertexNormals.empty ())
	{
		GLuint normalBufferObject;
		glGenBuffers(1, &normalBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferObject);
		glBufferData(GL_ARRAY_BUFFER, vertexNormals.size ()*sizeof (glm::vec3), &vertexNormals[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		SetNBO (normalBufferObject);
	}

	const std::vector <glm::vec2> processedTexCoords = mesh->GetTexCoords ();
	if (!processedTexCoords.empty ())
	{
		GLuint textureBufferObject;
		glGenBuffers(1, &textureBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, textureBufferObject);
		glBufferData(GL_ARRAY_BUFFER, processedTexCoords.size ()*sizeof (glm::vec2), &processedTexCoords[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		SetTBO (textureBufferObject);
	}
}

void CaseCubeRenderable::BindBuffers ()
{
	GLuint vao;
	
	GLuint vertexBufferObject = GetVBO();
	GLuint normalBufferObject = GetNBO();
	GLuint textureBufferObject = GetTBO();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer (GL_ARRAY_BUFFER, vertexBufferObject);	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer (GL_ARRAY_BUFFER, normalBufferObject);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, textureBufferObject);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	SetVAO (vao);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
}

GLuint CaseCubeRenderable::LoadShaderProgram (CaseCube::SharedPtr object)
{
	ResourceManager::SharedPtr rsrcManager = ResourceManager::GetInstance ();
	ShaderManager::SharedPtr shaderManager = ShaderManager::GetInstance ();

	std::string mtrlName = object->GetMaterial ();
	Material::SharedPtr mtrl = rsrcManager->GetResource<Material> (mtrlName)->GetPtr ();

	std::string shaderName = mtrl->GetShaderProgramID ();
	ShaderProgram::SharedPtr shaderProgram = shaderManager->GetShaderProgram (shaderName.c_str ());
	
	return shaderProgram->GetShaderProgram ();
}

void CaseCubeRenderable::Render (Renderer& renderer, CaseCube::SharedPtr caseCube)
{
	ResourceManager::SharedPtr rsrcManager = ResourceManager::GetInstance ();

	
	std::string meshName = caseCube->GetMesh ();
	Mesh::SharedPtr mesh = rsrcManager->GetResource<Mesh> (meshName)->GetPtr ();
	const std::vector <glm::vec3> processedVertices = mesh->GetVertices ();
	
	//GLuint sProgram = LoadShaderProgram (caseCube);

	Primitives drawPrimitive = mesh->GetPrimitives ();
	glBindVertexArray(GetVAO ());
	glDrawArrays (GL_LINES, 0, processedVertices.size());
	glBindVertexArray(0);
}

void CaseCubeRenderable::SetVAO (GLuint vao)
{
	this->m_Vao = vao;
}

void CaseCubeRenderable::SetVBO (GLuint vbo)
{
	this->m_Vbo = vbo;
}

void CaseCubeRenderable::SetNBO (GLuint nbo)
{
	this->m_Nbo =nbo;
}

void CaseCubeRenderable::SetTBO (GLuint tbo)
{
	this->m_Tbo = tbo;
}

void CaseCubeRenderable::SetShaderProgram (ShaderProgram::SharedPtr sProgram)
{
	this->m_SProgram = sProgram;
}

GLuint CaseCubeRenderable::GetVAO ()
{
	return this->m_Vao;
}

GLuint CaseCubeRenderable::GetVBO ()
{
	return this->m_Vbo;
}

GLuint CaseCubeRenderable::GetNBO ()
{
	return this->m_Nbo;
}

GLuint CaseCubeRenderable::GetTBO ()
{
	return this->m_Tbo;
}

ShaderProgram::SharedPtr CaseCubeRenderable::GetShaderProgram ()
{
	return this->m_SProgram;
}