#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include "include.h"
#include <cmath>

class BezierCurve 
{
public:

	~BezierCurve ();

	BezierCurve (std::vector<glm::vec3> points);

	std::vector<glm::vec3> GenerateBezierCurveLineCoords (int numSegments);
	
	glm::vec3 CalculateBezierPoint (float t);
	float Factorial(float num);
	float Choose(float a, float b);

private:
	std::vector<glm::vec3> m_Points;
};
#endif