#include "stdafx.h"
#include "cullingPlane.h"

CullingPlane::~CullingPlane ()
{

}

CullingPlane::CullingPlane ()
{
	m_ResultVec = glm::vec4 (0.0f, 0.0f, 0.0f, 0.0f);
}

CullingPlane::CullingPlane (glm::vec4 const& normal, float result)
{
	m_ResultVec = glm::vec4 (normal.x, normal.y, normal.z, result);
}

void CullingPlane::Set (glm::vec4 const& normal, float result)
{
	m_ResultVec = glm::vec4 (normal.x, normal.y, normal.z, result);
}

void CullingPlane::Get (glm::vec4 & normal, float & result) const
{
	normal.x = m_ResultVec.x;
	normal.y = m_ResultVec.y;
	normal.z = m_ResultVec.z;
	result = m_ResultVec.w;
}

glm::vec4 CullingPlane::GetNormal () const
{
	return glm::vec4 (m_ResultVec.x, m_ResultVec.y, m_ResultVec.z, 0.0f);
}

float CullingPlane::GetResult () const
{
	return m_ResultVec.w;
}