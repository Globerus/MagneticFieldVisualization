#ifndef TRACKBALL_H
#define TRACKBALL_H
#include "groupNode.h"
#include "camera.h"
#include "glm\gtx\orthonormalize.hpp"

class TrackBall
{
public:
	~TrackBall ();
	TrackBall ();
	TrackBall (int xSize, int ySize, std::shared_ptr<Camera> camera);

	void Set (int xSize, int ySize, std::shared_ptr<Camera> camera);
	
	void SetInitialCoordinates (int x, int y);
	void SetFinalCoordinates (int x, int y);

	void SetZoomActive (bool zoomActive);
	bool GetZoomActive () const;

	void SetActive (bool active);
	bool GetActive () const;

	void UpdateOrientation ();

protected:
	int m_XSize, m_YSize;
	float m_Multiplier;
	glm::vec4 m_InitialOrientation;
	std::shared_ptr<Camera> m_Camera;
	float m_X0, m_X1, m_Y0, m_Y1;
	bool m_Active, m_Valid, m_ZoomActive;
};
#endif