#pragma once
#ifndef CREATELOADPROGRAM
#define CREATELOADPROGRAM
#include "embeddedShaders.h"
#include <vector>
#include <string>
#include <glload\gl_3_3.h>
#include <glload\gl_load.hpp>
#include <glutil\glutil.h>

extern glm::vec3 g_camTarget;
extern glm::vec3 g_sphereCamRelPos;

class ProgramData {

public:
	ProgramData ();
	~ProgramData ();
//	static std::string FindFileOrThrow( const std::string &strBasename );
	std::wstring s2ws(const std::string& s);
	std::string GetEmbededShader ( int id, std::string type);
	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename);
	GLuint CreateProgram(const std::vector<GLuint> &shaderList);
	void LoadProgram (const std::string &Shader);

	static float DegToRad(float fAngDeg);
	static float CalcFrustumScale(float fFovDeg);
	static glm::mat4 CalcProjectionMatrix(float fzNear, float fzFar, float angle);
	
	static glm::vec3 ResolveCamPosition();
	static glm::mat4 CalcLookAtMatrix(const glm::vec3 &cameraPt, const glm::vec3 &lookPt, const glm::vec3 &upPt);
	static glm::mat4 ReverseCamRotation(const glm::vec3 &cameraPt, const glm::vec3 &lookPt, const glm::vec3 &upPt);

	//void LoadTexture (GLenum enumerator, int i, GLuint texture, Loader* loader);
	void SetLightCameraToClipMatrix (float fzNear, float fzFar, float angle);
	void SetLightWorldToCameraMatrix (glm::vec3 position, glm::vec3 target, glm::vec3 up);
	void SetLightModelToWorldMatrix (glutil::MatrixStack modelMatrix);
	void SetModelToWorldMatrix (glutil::MatrixStack modelMatrix);
	void SetWorldToCameraMatrix (glm::vec3 target, glm::vec3 up);
	void SetCameraToClipMatrix (float fzNear, float fzFar, float angle);
	void SetColor (glm::vec4 color);
	void SetNormalModelToWorldMatrix (glutil::MatrixStack normalMatrix);
	void SetAmbientIntensity (glm::vec4 ambientIntensity);
	void SetShinniness (float shinniness);
	void SetLightIntensity (glm::vec4 lightIntensity);
	void SetLightAttenuation (float lightAttenuation);
	void SetShadowMap (int shadowMap);
	void SetLightPosition (glm::vec3 lightPosition);
	void SetTexture (std::string texUnif, int textureMap); 
	void UseProgram ();
private:
	GLuint theProgram;
	GLuint lightIntensityUnif;
	GLuint lightPositionUnif;

	GLuint modelToWorldMatrixUnif;
	GLuint worldToCameraMatrixUnif;
	GLuint cameraToClipMatrixUnif;
	GLuint baseColourUnif;
	GLuint normalModelToWorldMatrixUnif;
	GLuint ambientIntensityUnif;
	GLuint shinninessUnif;
	GLuint lightAttenuationUnif;
	GLuint lightWorldToCameraMatrixUnif;
	GLuint lightCameraToClipMatrixUnif;
	GLuint lightModelToWorldMatrixUnif;
	GLuint shadowMapUnif;
	GLuint scaleTextureUnif;
	GLuint loadingTextureUnif;
	//GLuint text2DTextureUnif;

};
#endif