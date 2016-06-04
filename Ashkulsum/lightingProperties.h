#pragma once
#ifndef LIGHTINGPROPERTIES
#define LIGHTINGPROPERTIES
#include <glload\gl_3_3.h>
#include <glload\gl_load.hpp>

struct LightingProperties {
	 glm::vec4 lightIntensity;
	 glm::vec4 ambientIntensity;
	 glm::vec3 g_lightPosition;
	 float g_fLightAttenuation;
	 float g_fShininessFactor;
	 int shadowSizeWidth;
	 int shadowSizeHeigth;
};
extern const LightingProperties lightingProperties;

#endif