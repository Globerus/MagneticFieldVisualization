#include "stdafx.h"
#include "allScreen.h"

void drawSpring ()
{
	Spring ->Render ();
}
void drawCylinder ()
{
	Cylinder_body ->Render ();
	Cylinder_top ->Render ();
}
void drawSphere (glutil::MatrixStack &currMatrix)
{
	g_PointProgram->SetModelToWorldMatrix (currMatrix);
	g_PointProgram->UseProgram();
	currMatrix.Scale (30.0f, 30.0f, 30.0f);
	//Point ->Render ();
	glUseProgram (0);
}
void drawMagnet (glutil::MatrixStack &currMatrix)
{
	shadowMapFBO->BindForReading(GL_TEXTURE0);
	g_LightingColour->SetShadowMap (0);
	//glClear(GL_DEPTH_BUFFER_BIT );
	{
	glutil::PushStack push(currMatrix);
	currMatrix.Scale (3.0f, 3.0f, 3.0f);
	g_LightingColour->SetNormalModelToWorldMatrix (currMatrix);
	g_LightingColour->SetModelToWorldMatrix (currMatrix);
	g_LightingColour->UseProgram();
	drawSpring ();
	drawCylinder ();
	glUseProgram (0);
	}
	glBindTexture (GL_TEXTURE_2D, 0);
}
void drawPoints (glutil::MatrixStack &currMatrix)
{
	glutil::PushStack push(currMatrix);
	drawSphere (currMatrix);
}
void drawPositiveScale (glutil::MatrixStack &currMatrix, glm::vec3 translate)
{
	glutil::PushStack push(currMatrix);
	currMatrix.Translate(translate);
	currMatrix.ApplyMatrix (ProgramData::ReverseCamRotation (ProgramData::ResolveCamPosition(), translate, glm::vec3(0.0f, 1.0f, 0.0f)));
	currMatrix.Scale (3.0, 3.0, 3.0);
	g_NoLightingColour->SetModelToWorldMatrix (currMatrix);
	g_NoLightingColour->SetColor (glm::vec4 (1.0, 1.0, 1.0, 1.0));
	g_NoLightingColour->UseProgram();
	PositiveScale->Render ();
	glUseProgram (0);
}
void drawNegativeScale (glutil::MatrixStack &currMatrix, glm::vec3 translate)
{
	glutil::PushStack push(currMatrix);
	currMatrix.Translate(translate);
	currMatrix.ApplyMatrix (ProgramData::ReverseCamRotation (ProgramData::ResolveCamPosition(), translate, glm::vec3(0.0f, 1.0f, 0.0f)));
	currMatrix.Scale (3.0, 3.0, 3.0);
	g_NoLightingColour->SetModelToWorldMatrix (currMatrix);
	g_NoLightingColour->SetColor (glm::vec4 (1.0, 1.0, 1.0, 1.0));
	g_NoLightingColour->UseProgram();
	NegativeScale->Render ();
	glUseProgram (0);
}
void drawScaleCase (glutil::MatrixStack &currMatrix)
{	
	std::vector<glm::vec3> positiveTranslations;
	std::vector<glm::vec3> negativeTranslations;
	positiveTranslations.push_back(glm::vec3 (15.0, -25.0, 22.0));
	positiveTranslations.push_back(glm::vec3 (-25.0, -25.0, 15.0));
	positiveTranslations.push_back(glm::vec3 (-25.0, 15.0, -22.0));

	negativeTranslations.push_back(glm::vec3 (-18.0, -25.0, 22.0));
	negativeTranslations.push_back(glm::vec3 (-25.0, -25.0, -15.0));
	negativeTranslations.push_back(glm::vec3 (-25.0, -15.0, -22.0));

	for (unsigned int i = 0; i <positiveTranslations.size();i++)
	{
		glm::vec3 coordinate = positiveTranslations.at (i);
		drawPositiveScale (currMatrix, coordinate);
	}
	for (unsigned int i = 0; i <negativeTranslations.size();i++)
	{
		glm::vec3 coordinate = negativeTranslations.at (i);
		drawNegativeScale (currMatrix, coordinate);
	}
	{
	glutil::PushStack push(currMatrix);
	currMatrix.Scale (4.0f, 4.0f, 4.0f);	
	g_NoLightingColour->SetModelToWorldMatrix (currMatrix);
	g_NoLightingColour->SetColor (glm::vec4 (1.0, 1.0, 1.0, 1.0));
	g_NoLightingColour->UseProgram();
	ScaleCase ->Render ();
	glUseProgram (0);
	}
	std::vector <glm::vec3>().swap (positiveTranslations);
	std::vector <glm::vec3>().swap (negativeTranslations);
}
void drawShadowPass (glutil::MatrixStack &currMatrix) {
	g_ShadowMapping->SetLightWorldToCameraMatrix (lightingProperties.g_lightPosition, g_camTarget, glm::vec3 (0.0f, 1.0f, 0.0f));	
	shadowMapFBO->BindForWriting();
    glClear(GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_FRONT); 
	{
	glutil::PushStack push(currMatrix);
	currMatrix.Scale (4.0f, 4.0f, 4.0f);
	g_ShadowMapping->SetLightModelToWorldMatrix (currMatrix);
	g_ShadowMapping->UseProgram();
	drawSpring ();
	drawCylinder ();
	glUseProgram(0);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);			
}
void drawBigScreen (glutil::MatrixStack &currMatrix)
{
	glViewport(0,0,lightingProperties.shadowSizeWidth,lightingProperties.shadowSizeHeigth);
	drawShadowPass (currMatrix);
	g_LightingColour->SetLightPosition (lightingProperties.g_lightPosition);
	g_LightingColour->SetLightIntensity (lightingProperties.lightIntensity);
	g_LightingColour->SetAmbientIntensity (lightingProperties.ambientIntensity);
	g_LightingColour->SetShinniness (lightingProperties.g_fShininessFactor);
	g_LightingColour->SetLightAttenuation (lightingProperties.g_fLightAttenuation);
	g_LightingColour->SetLightWorldToCameraMatrix (lightingProperties.g_lightPosition, g_camTarget, glm::vec3 (0.0f, 1.0f, 0.0f));
	g_LightingColour->SetColor(glm::vec4 (1.0f));

	glViewport(0,height/4,width, 3*height/4);
	glCullFace(GL_BACK);
	drawMagnet (currMatrix);	
	drawPoints (currMatrix);
	drawScaleCase (currMatrix);
}