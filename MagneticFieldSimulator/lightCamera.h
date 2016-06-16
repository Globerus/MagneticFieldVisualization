#ifndef LIGHT_CAMERA_H
#define LIGHT_CAMERA_H

#include "camera.h"
#include "lighting.h"

class LightCamera : public Camera
{
public:
	LightCamera (bool isPerspective);

	std::shared_ptr<Lighting> m_Lighting;
};
#endif