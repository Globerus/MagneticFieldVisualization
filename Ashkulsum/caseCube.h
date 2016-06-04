#ifndef CASE_CUBE_H
#define CASE_CUBE_H

#include "gameObject.h"
#include "resourceManager.h"
#include "shaderManager.h"
#include <boost\shared_ptr.hpp>
#include <boost\make_shared.hpp>

class CaseCubeRenderable;

class CaseCube : public GameObject
{
public:
	typedef boost::shared_ptr<CaseCube> SharedPtr;

	static CaseCube::SharedPtr CreateCaseCube ();

	void SetMesh (std::string meshName);
	void SetMaterial (std::string mtrlName);
	void SetRenderable (Renderable::SharedPtr renderable);

	std::string GetMesh ();
	std::string GetMaterial ();
	Renderable* GetRenderable ();

protected:
	std::string m_Mesh, m_Mtrl;
	Renderable::SharedPtr m_Renderable;
	
};


#endif