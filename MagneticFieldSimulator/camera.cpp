#include "stdafx.h"
#include "camera.h"

Camera::~Camera ()
{

}

Camera::Camera (bool isPerspective)
	:	m_IsPerspective (isPerspective),
		m_ProjectionMatrix (glm::mat4(1.0f)),
		m_ViewMatrix (glm::mat4(1.0f))
{
	SetFrame (glm::vec4 (0.0f, 0.0f, 25.0f, 1.0f), glm::vec4 (0.0f, 0.4f, 0.0f, 0.0f), glm::vec4 (0.0f, 1.0f, 0.0f, 0.0f));
	if (isPerspective)
	{
		SetFrustum (110.0f, 1.0f, 1.0f, 100.0f);
	}
	else
	{
		SetFrustum (0.0f, 100.0f, -10.0f, 10.0f, -10.0f, 10.0f);
	}
}

void Camera::SetFrame (glm::vec4 const& position, glm::vec4 const& lookVector, glm::vec4 const& upVector)
{	
	SetPosition (position);
	SetLookVector (lookVector);
	SetUpVector (upVector);

	OnFrameChange ();
}

void Camera::SetFrustum (float angle, float ratio, float zNear, float zFar)
{
	float halfAngleRads = 0.5f * Maths::DegToRad (angle);
	float tang = (float)tan (halfAngleRads);

	m_Frustum [UMAX] = zNear * tang;
	m_Frustum [RMAX] = ratio * m_Frustum [UMAX];
	m_Frustum [UMIN] = -m_Frustum [UMAX];
	m_Frustum [RMIN] = -m_Frustum [RMAX];
	m_Frustum [DMIN] = zNear;
	m_Frustum [DMAX] = zFar;

	OnFrustumChange ();
}

void Camera::SetFrustum (float dMin, float dMax, float uMin, float uMax, float rMin, float rMax)
{
	m_Frustum[UMAX] = uMax;
	m_Frustum[RMAX] = rMax;
	m_Frustum[UMIN] = uMin;
	m_Frustum[RMIN] = rMin;
	m_Frustum[DMIN] = dMin;
	m_Frustum[DMAX] = dMax;

	OnFrustumChange ();
}

void Camera::SetPosition (glm::vec4 const& position)
{
	m_Position = position;
}

void Camera::SetLookVector (glm::vec4 const& lookVector)
{
	m_LookVector = lookVector;
}

void Camera::SetUpVector (glm::vec4 const& upVector)
{
	m_UpVector = upVector;
}

void Camera::SetRightVector (glm::vec4 const& rightVector)
{
	m_RightVector = rightVector;
}

void Camera::SetProjectionMatrix () 
{
	float umax = m_Frustum [UMAX];
	float umin = m_Frustum [UMIN];
	float rmax = m_Frustum [RMAX];
	float rmin = m_Frustum [RMIN];
	float dmin = m_Frustum [DMIN];
	float dmax = m_Frustum [DMAX];

	if (m_IsPerspective)
	{
		m_ProjectionMatrix[0].x = rmax;
		m_ProjectionMatrix[1].y = umax;
		m_ProjectionMatrix[2].z = (dmax + dmin) / (dmin - dmax);
		m_ProjectionMatrix[3].z = (2 * dmax * dmin)/ (dmin - dmax);
		m_ProjectionMatrix[2].w = -1.0f;
	}
	else
	{
		m_ProjectionMatrix[0].x = 2/(rmax - rmin);
		m_ProjectionMatrix[1].y = 2/(umax - umin);
		m_ProjectionMatrix[2].z = -2/(dmax - dmin);
		m_ProjectionMatrix[3].x = - (rmax + rmin) / (rmax - rmin);
		m_ProjectionMatrix[3].y = - (umax + umin) / (umax - umin);
		m_ProjectionMatrix[3].z = -(dmax + dmin)/(dmax - dmin);	
	}

};

void Camera::SetViewMatrix () 
{
	glm::vec3 position = glm::vec3 (m_Position);

	glm::vec3 lookVector = glm::vec3 (m_LookVector);
	glm::vec3 upVector = glm::vec3 (m_UpVector);

	glm::vec3 depthAxis = glm::normalize (lookVector - position);
	glm::vec3 upAxis = glm::normalize (upVector);
	glm::vec3 rightAxis = glm::normalize (glm::cross (depthAxis, upAxis));

	glm::vec3 perpUpDir = glm::normalize (glm::cross(rightAxis, depthAxis));

	m_ViewMatrix[0].x = rightAxis.x;
	m_ViewMatrix[1].x = rightAxis.y;
	m_ViewMatrix[2].x = rightAxis.z;
	m_ViewMatrix[3].x = -glm::dot (rightAxis, position);
	m_ViewMatrix[0].y = perpUpDir.x;
	m_ViewMatrix[1].y = perpUpDir.y;
	m_ViewMatrix[2].y = perpUpDir.z;
	m_ViewMatrix[3].y = -glm::dot (perpUpDir, position);
	m_ViewMatrix[0].z = -depthAxis.x;
	m_ViewMatrix[1].z = -depthAxis.y;
	m_ViewMatrix[2].z = -depthAxis.z;
	m_ViewMatrix[3].z = glm::dot (depthAxis, position);
}


glm::vec4 const& Camera::GetPosition () const
{
	return m_Position;
}

glm::vec4 const& Camera::GetLookVector () const
{
	return m_LookVector;
}

glm::vec4 const& Camera::GetUpVector () const
{
	return m_UpVector;
}

glm::vec4 const& Camera::GetRightVector () const
{
	return m_RightVector;
}

glm::mat4 const& Camera::GetProjectionMatrix () const
{
	return m_ProjectionMatrix;
}

glm::mat4 const& Camera::GetViewMatrix () const
{
	return m_ViewMatrix;
}

glm::mat4 const& Camera::GetProjectionViewMatrix () const
{
	return m_ProjectionViewMatrix;
}


float Camera::GetDMax () const
{
	return m_Frustum[DMAX];
}

float Camera::GetDMin () const
{
	return m_Frustum[DMIN];
}

float Camera::GetUMax () const
{
	return m_Frustum[UMAX];
}

float Camera::GetUMin () const
{
	return m_Frustum[UMIN];
}

float Camera::GetRMax () const
{
	return m_Frustum[RMAX];
}

float Camera::GetRMin () const
{
	return m_Frustum[RMIN];
}

bool Camera::GetFrustum (float & fov, float & aspectRatio, float & dMin, float & dMax)
{
	if (m_Frustum[RMIN] == -m_Frustum[RMAX]
        && m_Frustum[UMIN] == -m_Frustum[UMAX])
    {
        float tmp = (m_Frustum[UMAX] / m_Frustum[DMIN]);
		fov = 2.0f * atan(tmp);
		fov = Maths::RadToDeg (fov);
        aspectRatio = m_Frustum[RMAX] / m_Frustum[UMAX];
        dMin = m_Frustum[DMIN];

        dMax = m_Frustum[DMAX];
        return true;
    }
    return false;
}

void Camera::OnFrameChange ()
{
	SetViewMatrix ();
	UpdatePVMatrix ();
}

void Camera::OnFrustumChange ()
{
	SetProjectionMatrix ();
	UpdatePVMatrix ();
}

void Camera::UpdatePVMatrix ()
{
	m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
