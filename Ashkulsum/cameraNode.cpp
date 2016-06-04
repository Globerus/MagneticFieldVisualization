#include "stdafx.h"
#include "cameraNode.h"

CameraNode::CameraNode (std::shared_ptr<Camera> const& camera)
{
	SetCamera (camera);
}

void CameraNode::SetCamera (std::shared_ptr<Camera> const& camera)
{
	m_Camera = camera;

	if (m_Camera)
	{
		glm::mat4 rotation;
		glm::vec4 lookV = m_Camera->GetLookVector ();
		glm::vec4 upV = m_Camera->GetUpVector ();
		glm::vec4 rightV = m_Camera->GetRightVector ();

		rotation[0][0] = lookV.x;
		rotation[1][0] = lookV.y;
		rotation[2][0] = lookV.z;
		rotation[3][0] = lookV.w;

		rotation[0][1] = upV.x;
		rotation[1][1] = upV.y;
		rotation[2][1] = upV.z;
		rotation[3][1] = upV.w;
;
		rotation[0][2] = rightV.x;
		rotation[1][2] = rightV.y;
		rotation[2][2] = rightV.z;
		rotation[3][2] = rightV.w;
		
		rotation[0][3] = 0.0f;
		rotation[1][3] = 0.0f;
		rotation[2][3] = 0.0f;
		rotation[3][3] = 1.0f;

		m_LocalT.SetTranslation (m_Camera->GetPosition());
		m_LocalT.SetRotation (rotation);
		Update ();
	}
}

std::shared_ptr<Camera> const& CameraNode::GetCamera () const
{
	return m_Camera;
}

void CameraNode::SetShadowMapTransformation (glm::vec4 lightDir, std::shared_ptr<Camera> camera)
{
	glm::vec3 lightDir3 = glm::vec3 (lightDir);
	lightDir = glm::normalize (lightDir);
	float dMax;
	float dMin;

	glm::vec4 position = camera->GetPosition ();
	glm::vec4 lookVector = camera->GetLookVector ();
	glm::vec4 upVector = camera->GetUpVector ();
	glm::vec4 rightVector = camera->GetRightVector ();
	
	float fov, ar;

	camera->GetFrustum (fov, ar, dMin, dMax);
	glm::vec3 zAxis = glm::vec3(glm::normalize (position - lookVector));
	glm::vec3 xAxis = glm::normalize (glm::cross (glm::vec3 (upVector), zAxis));
	glm::vec3 yAxis = glm::normalize (glm::cross (xAxis, zAxis));

	glm::vec4 zAxis4 (zAxis, 0.0f);
	glm::vec4 xAxis4 (xAxis, 0.0f);
	glm::vec4 yAxis4 (yAxis, 0.0f);
	

	float nH = tan (fov/2)*dMin;
	float nW = nH *ar;

	float fH = tan(fov/2)*dMax;
	float fW = fH *ar;

	glm::vec4 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;

	glm::vec4 centerNear = position - zAxis4*dMin;
	glm::vec4 centerFar = position - zAxis4*dMax;


	ntl = centerNear + (yAxis4*(nH/2)) - (xAxis4*(nW/2));
	ntr = centerNear + (yAxis4*(nH/2)) + (xAxis4*(nW/2));
	nbl = centerNear - (yAxis4*(nH/2)) - (xAxis4*(nW/2));
	nbr = centerNear - (yAxis4*(nH/2)) + (xAxis4*(nW/2));

	ftl = centerFar + (yAxis4*(fH/2)) - (xAxis4*(fW/2));
	ftr = centerFar + (yAxis4*(fH/2)) + (xAxis4*(fW/2));
	fbl = centerFar - (yAxis4*(fH/2)) - (xAxis4*(fW/2));
	fbr = centerFar - (yAxis4*(fH/2)) + (xAxis4*(fW/2));

	glm::vec4 frustumCorners[8] = { ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr };
	glm::vec4 frustumCenter (0.0f);

	glm::mat4 view = camera->GetViewMatrix ();


	for (int i = 0; i < 8; i++)
	{
		frustumCorners[i] = view * frustumCorners[i];
		frustumCenter += frustumCorners[i];
	}
	frustumCenter /= 8;

	float nearClipOffset = 100.0f;
	float distFromCenter = dMax-dMin + 150.0f;
	glm::vec4 lightPosition = frustumCenter - (lightDir*distFromCenter);

	m_Camera->SetFrame (lightPosition, frustumCenter, upVector);
	auto viewM = m_Camera->GetViewMatrix ();

	for (int i = 0; i < 8; i++)
	{
		frustumCorners[i] = viewM * frustumCorners[i] ;
	}

	glm::vec4 minV, maxV;
	minV = frustumCorners[0];
	maxV = frustumCorners[0];
	for (int i = 0; i < 8; i++)
    {
		 minV.x = std::min(frustumCorners[i].x, minV.x);
         maxV.x = std::max (frustumCorners[i].x, maxV.x);
         minV.y = std::min(frustumCorners[i].y, minV.y);
		 maxV.y = std::max (frustumCorners[i].y, maxV.y);
         minV.z = std::min (frustumCorners[i].z, minV.z);
         maxV.z = std::max (frustumCorners[i].z, maxV.z);
    }

	m_Camera->SetFrustum (-maxV.z - nearClipOffset, -minV.z, minV.y, maxV.y, minV.x, maxV.x);

	m_LocalT.SetRotation (viewM);
	m_LocalT.SetTranslation (lightPosition);
}

void CameraNode::SetAddtnlUpdate (std::function<void(CameraNode*)> const& addtnlUpdate)
{
	m_AddtnlUpdate = addtnlUpdate;
}

void CameraNode::UpdateWorldData (float appTime)
{
	GroupNode::UpdateWorldData (appTime);

	if (m_Camera)
	{
		glm::vec4 position = m_WorldT.GetTranslationW1 ();
		glm::mat4 rotation = m_WorldT.GetTransformationMatrix ();

		glm::vec4 lookV (rotation[0][0], rotation[1][0], rotation[2][0], rotation[3][0]);
		glm::vec4 upV (rotation[0][1], rotation[1][1], rotation[2][1], rotation[3][1]);

		m_Camera->SetFrame (position, lookV, upV);

		if (m_AddtnlUpdate)
			m_AddtnlUpdate(this);
	}
}