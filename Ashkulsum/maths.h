#ifndef MATHS_H
#define MATHS_H
#include "include.h"

namespace Maths
{
	inline float DegToRad (float angle);
	inline glm::vec3 RundKutta (glm::vec3 pos, float dt);
	const static float PI = 3.14159f;
}

inline float Maths::DegToRad (float angle)
{
	const float fDegToRad = PI * 2.0f / 360.0f;
	return angle * fDegToRad;
}

inline glm::vec3 Maths::RundKutta (glm::vec3 pos, float dt)
{
	glm::vec3 k1 = dt * pos;
	glm::vec3 k2 = 0.5f * dt * k1;
	glm::vec3 k3 = 0.5f * dt * k2;
	glm::vec3 k4 = dt * k3;

	float dtSixth = dt/6;

	return pos + dtSixth * (k1 + 2.0f * (k2 + k3) + k4);
}

#endif