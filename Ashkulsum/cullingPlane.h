#ifndef CULLING_PLANE_H
#define CULLING_PLANE_H
#include "include.h"

class CullingPlane
{
public:
	~CullingPlane ();
	CullingPlane ();
	CullingPlane (glm::vec4 const& normal, float result);

	void Set (glm::vec4 const& normal, float result);
	void Get (glm::vec4& normal, float& result) const;

	glm::vec4 GetNormal () const;
	float GetResult () const;
private:
	glm::vec4 m_ResultVec;
};

#endif;