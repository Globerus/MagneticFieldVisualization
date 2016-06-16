#include "stdafx.h"
#include "culler.h"

Culler::~Culler ()
{

}

Culler::Culler ()
{

}

void Culler::PushViewFrustumPlanes (std::shared_ptr<Camera> camera)
{
	float dMax = camera->GetDMax ();
	float dMin = camera->GetDMin ();
	float uMax = camera->GetUMax ();
	float uMin = camera->GetUMin ();
	float rMax = camera->GetRMax ();
	float rMin = camera->GetRMin ();

	glm::vec4 position = camera->GetPosition ();
	glm::vec4 lookVector = camera->GetLookVector ();
	glm::vec4 upVector = camera->GetUpVector ();
	glm::vec4 rightVector = camera->GetRightVector ();

	float dirToCamera = glm::dot (position, lookVector);

}