#ifndef CULLER_H
#define CULLER_H

#include "cullingPlane.h"
#include "camera.h"

class Culler
{
public:
	~Culler ();
	Culler ();

	void PushViewFrustumPlanes (std::shared_ptr<Camera> camera);

protected:
	CullingPlane m_Planes[6];
};

#endif