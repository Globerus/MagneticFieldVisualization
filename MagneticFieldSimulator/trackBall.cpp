#include "stdafx.h"
#include "trackBall.h"

TrackBall::~TrackBall ()
{

}

TrackBall::TrackBall ()
	:	m_X0 (0.0f),
		m_Y0 (0.0f),
		m_X1 (0.0f),
		m_Y1 (0.0f),
		m_Multiplier (0.0f),
		m_Active (false),
		m_Valid (false),
		m_ZoomActive (false)
{
	m_InitialOrientation = m_Camera->GetPosition ();
}

TrackBall::TrackBall (int xSize, int ySize, std::shared_ptr<Camera> camera)
	:	m_X0 (0.0f),
		m_Y0 (0.0f),
		m_X1 (0.0f),
		m_Y1 (0.0f),
		m_Multiplier (0.0f),
		m_Active (false),
		m_Valid (false),
		m_ZoomActive (false)
{
	Set (xSize, ySize, camera);
	m_InitialOrientation = m_Camera->GetPosition ();
	UpdateOrientation ();
}


void TrackBall::Set (int xSize, int ySize, std::shared_ptr<Camera> camera)
{
	if (xSize > 0 && ySize > 0 && camera)
	{
		m_XSize = xSize;
		m_YSize = ySize;
		m_X0 = 0.5f * m_XSize;
		m_Y0 = 0.5f * m_YSize;
		m_X1 = m_X0;
		m_Y1 = m_Y0;
		m_Multiplier = 1.0f / (m_XSize >= m_YSize ? m_YSize : m_XSize);
		m_Camera = camera;
		m_Valid = true;
	}
	else
	{
		fprintf (stderr, "The set method in TrackBall failed, because the input parameters are incorrect.\n");
	}
}

void TrackBall::SetInitialCoordinates (int x, int y)
{
	if (m_Valid)
	{
		m_X0 = 1.0f*x;
		m_Y0 = 1.0f*y;
	}
}

void TrackBall::SetFinalCoordinates (int x, int y)
{
	if (m_Valid)
	{
		m_X1 = 1.0f*x;
		m_Y1 = 1.0f*y;
		if ((m_X1 != m_X0) || (m_Y1 != m_Y0))
		{
			UpdateOrientation ();
		}
	}
}

void TrackBall::SetZoomActive (bool zoomActive)
{
	m_ZoomActive = zoomActive;
}

bool TrackBall::GetZoomActive () const
{
	return m_ZoomActive;
}

void TrackBall::SetActive (bool active)
{
	m_Active = active;
}

bool TrackBall::GetActive () const
{
	return m_Active;
}

void TrackBall::UpdateOrientation ()
{

	if (GetZoomActive ())
	{
		m_InitialOrientation.z += (m_Y0 - m_Y1);
	}
	else
	{
		m_InitialOrientation.x += (m_X0 - m_X1);
		m_InitialOrientation.y += (m_Y0 - m_Y1);
	}
	

	m_InitialOrientation.y = glm::clamp(m_InitialOrientation.y , -60.9f, 20.9f);
	m_InitialOrientation.z = glm::clamp(m_InitialOrientation.z, 10.0f, 28.0f);

	glm::vec4 lookVector = m_Camera->GetLookVector ();
	glm::vec4 upVector = m_Camera->GetUpVector ();
	float phi = Maths::DegToRad(m_InitialOrientation.x);
	float theta = Maths::DegToRad(m_InitialOrientation.y+ 90.0f);

	float fSinTheta = sinf(theta);
	float fCosTheta = cosf(theta);
	float fCosPhi = cosf(phi);
	float fSinPhi = sinf(phi);

	glm::vec3 dirToCamera(fSinTheta * fCosPhi, fCosTheta, fSinTheta * fSinPhi);
	glm::vec4 result ((dirToCamera * m_InitialOrientation.z) + glm::vec3 (lookVector), 1.0f);

	m_Camera->SetFrame (result, lookVector, upVector);	
}
