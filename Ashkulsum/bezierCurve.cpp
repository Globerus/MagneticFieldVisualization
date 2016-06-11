#include "stdafx.h"
#include "bezierCurve.h"

BezierCurve::~BezierCurve ()
{

}

BezierCurve::BezierCurve (std::vector<glm::vec3> points)
	:	m_Points (points)
{

}

std::vector<glm::vec3> BezierCurve::GenerateBezierCurveLineCoords (int numSegments)
{
	float t;
	std::vector<glm::vec3> bezierCurvePoints;

	for (int i = 0; i < numSegments; i++)
	{
		t = (float)i / numSegments;
		glm::vec3 point = CalculateBezierPoint (t);
		bezierCurvePoints.push_back (point);
	}
	bezierCurvePoints.push_back (m_Points.back());

	return bezierCurvePoints;
}

glm::vec3 BezierCurve::CalculateBezierPoint (float t)
{
	glm::vec3 p;
	float len = float(m_Points.size());
	for(float i = 0.0f; i < len; i++)
	{
		p += m_Points[(int)i] * Choose(len - 1.0f, i) * std::powf(1.0f - t, len - 1.0f - i) * std::powf(t, i);
	} 

	return p;
}

float BezierCurve::Factorial(float num)
{
  if(num <= 1)
  {
	return 1;
  }

  float fac = 1;
  for(float i = 1; i <= num; i++)
  {
	  fac *= i;
  }

  return fac;
}

float BezierCurve::Choose(float a, float b)
{
	return Factorial(a) / (Factorial(b ) * Factorial(a - b));
}
