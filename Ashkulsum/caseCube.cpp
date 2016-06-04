#include "stdafx.h"
#include "caseCube.h"
#include "caseCubeRenderable.h"

CaseCube::SharedPtr CaseCube::CreateCaseCube ()
{
	CaseCube::SharedPtr caseCube = boost::make_shared<CaseCube> ();
	caseCube->SetMesh ("data\\objects\\case.obj");
	caseCube->SetMaterial ("data\\objects\\case.mtrl");
	
	Renderable::SharedPtr renderable = boost::make_shared<CaseCubeRenderable> (caseCube);
	caseCube->SetRenderable (renderable);

	return caseCube;
}

void CaseCube::SetMesh (std::string meshName)
{
	this->m_Mesh = meshName;
}

void CaseCube::SetMaterial (std::string materialName)
{
	this->m_Mtrl = materialName;
}

void CaseCube::SetRenderable (Renderable::SharedPtr renderable)
{
	this->m_Renderable = renderable;
}

std::string CaseCube::GetMesh ()
{
	return this->m_Mesh;
}

std::string CaseCube::GetMaterial ()
{
	return this->m_Mtrl;
}

Renderable* CaseCube::GetRenderable ()
{
	return this->m_Renderable.get();
}

