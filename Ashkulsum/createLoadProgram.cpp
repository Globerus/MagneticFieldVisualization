#include "stdafx.h"
#include "createLoadProgram.h"

ProgramData::ProgramData (){}

ProgramData::~ProgramData () 
{
	ProgramData* self = this;
	glUseProgram(0);
	glDeleteProgram(self->theProgram);
}

std::wstring ProgramData::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}
std::string ProgramData::GetEmbededShader ( int id, const std::string type)
{
	HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(id), s2ws(type).c_str()); 
	if (!hRes)
		throw std::runtime_error("Could not find the resource ");
	HGLOBAL res_handle = LoadResource(NULL, hRes);
	if (!res_handle)
		throw std::runtime_error("Could not load the resource ");
	DWORD dataSize = SizeofResource(0, hRes);
	char*  res_data = (char*)LockResource(res_handle);
	std::string result;
	result.assign(res_data, dataSize);
	return result;
}

GLuint ProgramData::LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
{
	int id;
	if (strShaderFilename == "LOADING")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_LOADING_VERT;
		else
			id = IDR_LOADING_FRAG;
	}
	else if (strShaderFilename == "LIGHTING")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_LIGHTING_VERT;
		else
			id = IDR_LIGHTING_FRAG;
	}
	else if (strShaderFilename == "NO_LIGHTING")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_NO_LIGHTING_VERT;
		else
			id = IDR_NO_LIGHTING_FRAG;
	}
	else if (strShaderFilename == "POINT")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_POINT_VERT;
		else
			id = IDR_POINT_FRAG;
	}
	else if (strShaderFilename == "SCALE")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_SCALE_VERT;
		else
			id = IDR_SCALE_FRAG;
	}
	else if (strShaderFilename == "SHADOW")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_SHADOW_VERT;
		else
			id = IDR_SHADOW_FRAG;
	}
	else if (strShaderFilename == "TEXT")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_TEXT_VERT;
		else
			id = IDR_TEXT_FRAG;
	}
		std::string shaderData = GetEmbededShader (id, strShaderFilename);
	try
	{
		return glutil::CompileShader(eShaderType, shaderData);
	}
	catch(std::exception &e)
	{
		fprintf(stderr, "%s\n", e.what());
		throw;
	}
}

GLuint ProgramData::CreateProgram(const std::vector<GLuint> &shaderList)
{
	try
	{
		GLuint prog = glutil::LinkProgram(shaderList);
		std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
		return prog;
	}
	catch(std::exception &e)
	{
		std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
		fprintf(stderr, "%s\n", e.what());
		throw;
	}
}

void ProgramData::LoadProgram (const std::string &strShader)
{
	ProgramData* self = this;
	std::vector<GLuint> shaderList;
	shaderList.push_back(self->LoadShader(GL_VERTEX_SHADER, strShader));
	shaderList.push_back(self->LoadShader(GL_FRAGMENT_SHADER, strShader));
	
	self->theProgram = self->CreateProgram(shaderList);

	//Camera
	self->modelToWorldMatrixUnif = glGetUniformLocation(self->theProgram, "modelToWorldMatrix");
	self->worldToCameraMatrixUnif = glGetUniformLocation(self->theProgram, "worldToCameraMatrix");
	self->cameraToClipMatrixUnif = glGetUniformLocation(self->theProgram, "cameraToClipMatrix");
	self->baseColourUnif = glGetUniformLocation(self->theProgram, "color");

	//Shadow Mapping
	self->lightCameraToClipMatrixUnif = glGetUniformLocation(self->theProgram, "lightCameraToClipMatrix");
	self->lightWorldToCameraMatrixUnif = glGetUniformLocation(self->theProgram, "lightWorldToCameraMatrix");
	self->lightModelToWorldMatrixUnif = glGetUniformLocation(self->theProgram, "lightModelToWorldMatrix");
	self->shadowMapUnif = glGetUniformLocation (self->theProgram, "shadowMap");

	//Lighting
	self->normalModelToWorldMatrixUnif = glGetUniformLocation(self->theProgram, "normalModelToWorldMatrix");
	self->lightIntensityUnif = glGetUniformLocation(self->theProgram, "lightIntensity");
	self->lightPositionUnif = glGetUniformLocation(self->theProgram, "lightPos");
	self->ambientIntensityUnif = glGetUniformLocation(self->theProgram, "ambientIntensity");
	self->shinninessUnif = glGetUniformLocation(self->theProgram, "shinninessFactor");
	self->lightAttenuationUnif = glGetUniformLocation(self->theProgram, "lightAttenuation");

	//Texture
	self->scaleTextureUnif = glGetUniformLocation(self->theProgram, "scaleTexture");
	self->loadingTextureUnif = glGetUniformLocation(self->theProgram, "loadingTexture");

	std::vector <GLuint>().swap (shaderList);
}

//methods for calculating the projection matrix
float ProgramData::DegToRad(float fAngDeg)
{
	const float fDegToRad = 3.14159f * 2.0f / 360.0f;
	return fAngDeg * fDegToRad;
}

float ProgramData::CalcFrustumScale(float fFovDeg)
{
	float fFovRad = ProgramData::DegToRad (fFovDeg);
	return 1.0f / tan(fFovRad / 2.0f);
}

glm::mat4 ProgramData::CalcProjectionMatrix(float fzNear, float fzFar, float angle)
{
	const float fFrustumScale = CalcFrustumScale(angle);
	glm::mat4 cameraToClipMatrix;
	cameraToClipMatrix[0].x = fFrustumScale;
	cameraToClipMatrix[1].y = fFrustumScale;
	cameraToClipMatrix[2].z = (fzFar + fzNear) / (fzNear - fzFar);
	cameraToClipMatrix[3].z = (2 * fzFar * fzNear) / (fzNear - fzFar);
	cameraToClipMatrix[2].w = -1.0f;

	return cameraToClipMatrix;
}
/*
glm::mat4 ProgramData::CalcOrthographicMatrix(float fzNear, float fzFar, float angle)
{
	const float fFrustumScale = CalcFrustumScale(angle);
	glm::mat4 cameraToClipMatrix;
	cameraToClipMatrix[0].x = fFrustumScale;
	cameraToClipMatrix[1].y = fFrustumScale;
	cameraToClipMatrix[2].z = (fzFar + fzNear) / (fzNear - fzFar);
	cameraToClipMatrix[3].z = (2 * fzFar * fzNear) / (fzNear - fzFar);
	cameraToClipMatrix[2].w = -1.0f;

	return cameraToClipMatrix;
}*/
//Methods for calculating the camera matrix
glm::vec3 ProgramData::ResolveCamPosition()
{
	glutil::MatrixStack tempMat;

	float phi = DegToRad(g_sphereCamRelPos.x);
	float theta = DegToRad(g_sphereCamRelPos.y + 90.0f);

	float fSinTheta = sinf(theta);
	float fCosTheta = cosf(theta);
	float fCosPhi = cosf(phi);
	float fSinPhi = sinf(phi);

	glm::vec3 dirToCamera(fSinTheta * fCosPhi, fCosTheta, fSinTheta * fSinPhi);
	return  (dirToCamera * g_sphereCamRelPos.z) + g_camTarget;
}
glm::mat4 ProgramData::ReverseCamRotation(const glm::vec3 &cameraPt, const glm::vec3 &lookPt, const glm::vec3 &upPt)
{
	glm::vec3 lookDir = glm::normalize(lookPt - cameraPt);
	glm::vec3 upDir = glm::normalize(upPt);

	glm::vec3 rightDir = glm::normalize(glm::cross(lookDir, upDir));
	glm::vec3 perpUpDir = glm::cross(rightDir, lookDir);

	glm::mat4 rotMat(1.0f);
	rotMat[0] = glm::vec4(rightDir, 0.0f);
	rotMat[1] = glm::vec4(perpUpDir, 0.0f);
	rotMat[2] = glm::vec4(-lookDir, 0.0f);

	return rotMat;
}
glm::mat4 ProgramData::CalcLookAtMatrix(const glm::vec3 &cameraPt, const glm::vec3 &lookPt, const glm::vec3 &upPt)
{
	glm::vec3 lookDir = glm::normalize(lookPt - cameraPt);
	glm::vec3 upDir = glm::normalize(upPt);

	glm::vec3 rightDir = glm::normalize(glm::cross(lookDir, upDir));
	glm::vec3 perpUpDir = glm::cross(rightDir, lookDir);

	glm::mat4 rotMat(1.0f);
	rotMat[0] = glm::vec4(rightDir, 0.0f);
	rotMat[1] = glm::vec4(perpUpDir, 0.0f);
	rotMat[2] = glm::vec4(-lookDir, 0.0f);

	rotMat = glm::transpose(rotMat);

	glm::mat4 transMat(1.0f);
	transMat[3] = glm::vec4(-cameraPt, 1.0f);

	return rotMat * transMat;
}

void ProgramData::SetLightCameraToClipMatrix (float fzNear, float fzFar, float angle)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glm::mat4 lightCameraToClipMatrix = CalcProjectionMatrix (fzNear, fzFar, angle);
	glUniformMatrix4fv(self->lightCameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(lightCameraToClipMatrix));
	glUseProgram (0);
}
void ProgramData::SetLightWorldToCameraMatrix (glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glm::mat4 lightWorldToCameraMatrix = CalcLookAtMatrix (position, target, up);
	glUniformMatrix4fv(self->lightWorldToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(lightWorldToCameraMatrix));
	glUseProgram (0);
}
void ProgramData::SetLightModelToWorldMatrix (glutil::MatrixStack modelMatrix)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glUniformMatrix4fv(self->lightModelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
	glUseProgram (0);
}
void ProgramData::SetModelToWorldMatrix (glutil::MatrixStack modelMatrix)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glUniformMatrix4fv(self->modelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(modelMatrix.Top()));
	glUseProgram (0);
}
void ProgramData::SetWorldToCameraMatrix (glm::vec3 target, glm::vec3 up)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	const glm::vec3 &camPos = ResolveCamPosition();
	glm::mat4 worldToCameraMatrix = CalcLookAtMatrix (camPos, target, up);
	glUniformMatrix4fv(self->worldToCameraMatrixUnif, 1, GL_FALSE, glm::value_ptr(worldToCameraMatrix));
	glUseProgram (0);
}
void ProgramData::SetCameraToClipMatrix (float fzNear, float fzFar, float angle)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glm::mat4 cameraToClipMatrix = CalcProjectionMatrix (fzNear, fzFar, angle);
	glUniformMatrix4fv(self->cameraToClipMatrixUnif, 1, GL_FALSE, glm::value_ptr(cameraToClipMatrix));
	glUseProgram (0);
}
void ProgramData::SetColor (glm::vec4 color) 
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glUniform4f(self->baseColourUnif, color.x, color.y, color.z, color.w);
	glUseProgram (0);
}
void ProgramData::SetNormalModelToWorldMatrix (glutil::MatrixStack normalMatrix)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glm::mat3 normMatrix(normalMatrix.Top());
	glUniformMatrix3fv(self->normalModelToWorldMatrixUnif, 1, GL_FALSE, glm::value_ptr(normMatrix));
	glUseProgram (0);
}
void ProgramData::SetAmbientIntensity (glm::vec4 ambientIntensity)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glUniform4f(self->ambientIntensityUnif, ambientIntensity.x, ambientIntensity.y, ambientIntensity.z, ambientIntensity.w);
	glUseProgram (0);
}
void ProgramData::SetShinniness (float shinniness)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glUniform1f(self->shinninessUnif, shinniness);
	glUseProgram (0);
}
void ProgramData::SetLightIntensity (glm::vec4 lightIntensity)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glUniform4f(self->lightIntensityUnif, lightIntensity.x, lightIntensity.y, lightIntensity.z, lightIntensity.w);
	glUseProgram (0);
}
void ProgramData::SetLightAttenuation (float lightAttenuation)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glUniform1f(self->lightAttenuationUnif, lightAttenuation);
	glUseProgram (0);
}
void ProgramData::SetShadowMap (int shadowMap)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glUniform1i(self->shadowMapUnif, shadowMap);
	glUseProgram (0);
}
void ProgramData::SetLightPosition (glm::vec3 lightPosition)
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
	glUniform3fv(self->lightPositionUnif, 1, glm::value_ptr(lightPosition));
	glUseProgram (0);
}

void ProgramData::SetTexture (std::string texUnif, int textureMap)
{
	ProgramData* self = this;
	if (texUnif == "scaleTextureUnif")
	{
		glUseProgram (self->theProgram);
		glUniform1i(self->scaleTextureUnif, textureMap);
		glUseProgram (0);
	}
	else if (texUnif == "loadingTextureUnif")
	{
		glUseProgram (self->theProgram);
		glUniform1i(self->loadingTextureUnif, textureMap);
		glUseProgram (0);
	}
}
void ProgramData::UseProgram ()
{
	ProgramData* self = this;
	glUseProgram (self->theProgram);
}
