#include "stdafx.h"
#include "allScreen.h"

void drawScaleScreen (glutil::MatrixStack &currMatrix)
{ 
	Scale->ActivateTexture (GL_TEXTURE_2D);
	g_ScaleProgram->UseProgram();		
	Scale->Render ();
	glUseProgram (0);
	glBindTexture (GL_TEXTURE_2D, 0);
}