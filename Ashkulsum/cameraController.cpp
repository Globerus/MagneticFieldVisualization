#include "stdafx.h"
#include "cameraController.h"

CameraControllerNode::CameraControllerNode (std::shared_ptr<CameraNode> cameraNode)
	:	m_CameraNode (cameraNode)
{
	
}
/*
void CameraControllerNode::RecalculatePositionAlternative ()
{
	glm::vec4 position = m_Camera->GetPosition ();
	glm::vec4 newPosition (1.0f);
	glm::vec4 lookDirection = m_Camera->GetLookDirection ();

	glm::vec2 delta;
	GetMouseDelta (delta);

	position.x = position.x + delta.x;
	position.y = position.y + delta.y;

	position.y = glm::clamp((float)(position.y), -60.9f, 60.9f);
	
	if (position.x == 0)
		position.x = std::numeric_limits<float>::epsilon ();
	float radius = sqrt (position.x * position.x + position.y * position.y + position.z * position.z);
	position = position * 1.0f/radius;
	float theta = atan2 (position.z, position.x);
	float phi = acos (position.y);
	phi += (phi < 0) ? 2*3.14 : 0;
	newPosition.z = radius*sin(phi)*sin(theta);
	newPosition.y = radius*cos(phi);
	newPosition.x = radius*sin(phi)*cos(theta);

	m_Camera->UpdatePosition  ( newPosition + lookDirection);
}
*/
/*
void CameraControllerNode::RecalculatePosition ()
{
	auto camera = m_CameraNode->GetCamera ();

	glm::vec4 position = camera->GetPosition ();
	glm::vec4 lookDirection = camera->GetLookDirection ();
	
	//glm::vec4 position = m_Camera->GetPosition ();
	//glm::vec4 lookDirection = m_Camera->GetLookDirection ();

	glm::vec2 delta;
	GetMouseDelta (delta);

	m_CameraNode->m_LocalT.SetTranslation (glm::vec4 (delta.x, delta.y, 0.0f, 0.0f));
	//position.x = position.x + delta.x;
	//position.y = position.y + delta.y;
	
	//m_Camera->SetPosition (position);
	
	position.y = glm::clamp((float)(position.y), -60.9f, 60.9f);
	
	float phi = Camera::DegToRad(position.x);
	float theta = Camera::DegToRad(position.y+ 90.0f);

	float fSinTheta = sinf(theta);
	float fCosTheta = cosf(theta);
	float fCosPhi = cosf(phi);
	float fSinPhi = sinf(phi);

	glm::vec3 dirToCamera(fSinTheta * fCosPhi, fCosTheta, fSinTheta * fSinPhi);
	//m_Camera->UpdatePosition  ( glm::vec4((dirToCamera * position.z) + glm::vec3 (lookDirection), 1.0));
	m_Camera->SetSpherePosition  ( glm::vec4((dirToCamera * position.z) + glm::vec3 (lookDirection), 1.0));
	m_Camera->OnFrameChange ();
}
*/
/*
std::shared_ptr<CameraNode> CameraControllerNode::GetCameraNode () const
{
	return m_CameraNode;
}
*/
void CameraControllerNode::SetDragging (bool value)
{
	m_IsDragging = value;
}

bool CameraControllerNode::GetDragging () const
{
	return m_IsDragging;
}

void CameraControllerNode::SetMouseCoordinates (glm::vec2 const& prevPos) 
{
	m_PrevPos = prevPos;
}

glm::vec2 const& CameraControllerNode::GetMouseCoordinates () const
{
	return m_PrevPos;
}

void CameraControllerNode::SetMouseDelta (glm::vec2 const& delta)
{
	m_Delta = delta;
}

glm::vec2 const& CameraControllerNode::GetMouseDelta () const
{
	return m_Delta;
}