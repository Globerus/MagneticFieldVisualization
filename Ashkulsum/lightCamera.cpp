#include "stdafx.h"
#include "lightCamera.h"

LightCamera::LightCamera (bool isPerspective)
	:	Camera (isPerspective),
		m_Lighting (nullptr)
{

}