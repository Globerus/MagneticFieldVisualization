#include "stdafx.h"
#include "allScreen.h"

void drawLine(glutil::MatrixStack &currMatrix, glm::vec4 colour)
{
	//Set the base color for this object.
	g_NoLightingColour->SetColor (colour);
	g_NoLightingColour->SetModelToWorldMatrix (currMatrix);
	g_NoLightingColour->UseProgram();
	Vector ->Render ();
	glUseProgram (0);
}
void drawCone(glutil::MatrixStack &currMatrix, glm::vec4 colour)
{
    //Set the base color for this object.
	g_NoLightingColour->SetColor (colour);
	g_NoLightingColour->SetModelToWorldMatrix (currMatrix);
	g_NoLightingColour->UseProgram();
	Cone ->Render ();
	glUseProgram (0);
}
void drawLetter(Loader *Letter, glutil::MatrixStack &currMatrix, glm::vec4 colour)
{
    //Set the base color for this object.
	g_NoLightingColour->SetColor (colour);
	g_NoLightingColour->SetModelToWorldMatrix (currMatrix);
	g_NoLightingColour->UseProgram();
	Letter ->Render ();
	glUseProgram (0);
}

void drawX(glutil::MatrixStack &currMatrix, glm::vec3 &colour)
{	
	{
	glutil::PushStack push (currMatrix);
	currMatrix.Translate (glm::vec3 (10.0f, 0.0f, 0.0f));
	currMatrix.RotateZ(-90.0f);
	drawCone (currMatrix, glm::vec4 (colour, 1.0f));
	}
	{
	glm::vec3 translation (12.0f, 0.0f, 0.0f);
	glutil::PushStack push (currMatrix);
	currMatrix.Translate (translation);
	currMatrix.ApplyMatrix (ProgramData::ReverseCamRotation (ProgramData::ResolveCamPosition(), translation, glm::vec3(0.0f, 1.0f, 0.0f)));
	currMatrix.Scale (glm::vec3 (5.0f, 5.0f, 5.0f));	
	drawLetter (LetterX, currMatrix, glm::vec4 (colour, 1.0f));
	}
	{
	glutil::PushStack push(currMatrix);
	currMatrix.RotateZ(-90.0f);
	currMatrix.Scale (1.0f, 10.0f, 1.0f);
	drawLine (currMatrix, glm::vec4 (colour, 1.0f));
	}
}
void drawY(glutil::MatrixStack &currMatrix, glm::vec3 &colour)
{
	{
	glutil::PushStack push (currMatrix);
	currMatrix.Translate (glm::vec3 (0.0f, 10.0f, 0.0f));
	drawCone (currMatrix, glm::vec4 (colour, 1.0f));
	}
	{
	glm::vec3 translation (-1.0f, 13.0f, 0.0f);
	glutil::PushStack push (currMatrix);
	currMatrix.Translate (translation);
	currMatrix.ApplyMatrix (ProgramData::ReverseCamRotation (ProgramData::ResolveCamPosition(), translation, glm::vec3(0.0f, 1.0f, 0.0f)));
	currMatrix.Scale (glm::vec3 (5.0f, 5.0f, 5.0f));	
	drawLetter (LetterY, currMatrix, glm::vec4 (colour, 1.0f));
	}
	{
	glutil::PushStack push(currMatrix);
	currMatrix.Scale (1.0f, 10.0f, 1.0f);
	drawLine (currMatrix, glm::vec4 (colour, 1.0f));
	}
}
void drawZ(glutil::MatrixStack &currMatrix, glm::vec3 colour)
{
	{
	glutil::PushStack push (currMatrix);
	currMatrix.Translate (glm::vec3 (0.0f, 0.0f, 10.0f));
	currMatrix.RotateX(90.0f);	
	drawCone (currMatrix, glm::vec4 (colour, 1.0f));
	}
	{
	glm::vec3 translation (-1.0f, 0.0, 13.0f);
	glutil::PushStack push (currMatrix);
	currMatrix.Translate (translation);
	currMatrix.ApplyMatrix (ProgramData::ReverseCamRotation (ProgramData::ResolveCamPosition(), translation, glm::vec3(0.0f, 1.0f, 0.0f)));
	currMatrix.Scale (glm::vec3 (5.0f, 5.0f, 5.0f));	
	drawLetter (LetterZ, currMatrix, glm::vec4 (colour, 1.0f));
	}
	{
	glutil::PushStack push(currMatrix);
	currMatrix.RotateX(90.0f);
	currMatrix.Scale (1.0f, 10.0f, 1.0f);
	drawLine (currMatrix, glm::vec4 (colour, 1.0f));
	}
}
void drawSmallScreen (glutil::MatrixStack &currMatrix)
{ 
	currMatrix.Scale (3.0f, 3.0f, 3.0f);
	drawY(currMatrix, glm::vec3 (0.0f, 1.0f, 0.0f));
	drawX(currMatrix, glm::vec3 (1.0f, 0.0f, 0.0f));
	drawZ(currMatrix, glm::vec3 (0.0f, 0.0f, 1.0f));
}