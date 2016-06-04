#pragma once
#ifndef SMALLSCREEN
#define SMALLSCREEN

#include "createLoadProgram.h"
#include "shadowMapFBO.h"
#include "lightingProperties.h"
#include "interpolator.h"
#include "fontText.h"
#include <vector>

extern ProgramData *g_NoLightingColour;
extern ProgramData *g_LightingColour;
extern ProgramData *g_ShadowMapping;
extern ProgramData *g_ScaleProgram;
extern ProgramData *g_PointProgram;
extern ProgramData *g_LoadingProgram;
extern ProgramData *g_Text2DProgram;

extern ShadowMapFBO *shadowMapFBO;
extern int width, height;

extern Loader *Scale;
extern Loader *ScaleCase;
extern Loader *PositiveScale;
extern Loader *NegativeScale;
extern Loader *Cylinder_body;
extern Loader *Cylinder_top;
extern Loader *Vector;
extern Loader *Cone;
extern Loader *LetterX;
extern Loader *LetterY;
extern Loader *LetterZ;
extern Loader *Spring;
//extern Interpolator *Point;

extern glm::vec3 g_camTarget;
extern glm::vec3 g_sphereCamRelPos;

void drawLetter(Loader *Letter, glutil::MatrixStack &currMatrix, glm::vec4 colour);
void drawPoints (glutil::MatrixStack &currMatrix);
void drawSphere (glutil::MatrixStack &currMatrix);
void drawMagnet (glutil::MatrixStack &currMatrix);
void drawCylinder ();
void drawSpring ();
void drawLine( glutil::MatrixStack &currMatrix, glm::vec4 colour);
void drawCone( glutil::MatrixStack &currMatrix, glm::vec4 colour);
void drawX( glutil::MatrixStack &currMatrix, glm::vec3 &colour);
void drawY( glutil::MatrixStack &currMatrix, glm::vec3 &colour);
void drawZ( glutil::MatrixStack &currMatrix, glm::vec3 &colour);
void drawSmallScreen ( glutil::MatrixStack &currMatrix);
void drawBigScreen ( glutil::MatrixStack &currMatrix);
void drawScaleScreen ( glutil::MatrixStack &currMatrix);

#endif