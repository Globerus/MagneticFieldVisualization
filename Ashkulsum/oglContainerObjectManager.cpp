#include "stdafx.h"
#include "oglContainerObjectManager.h"

OGLContainerObjectManager::~OGLContainerObjectManager ()
{
	if (m_COMap.HasElements ())
	{
		UnbindAll ();
	}
}

OGLContainerObjectManager::OGLContainerObjectManager ()
{
}

OGLContainerObject* OGLContainerObjectManager::Bind (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer)
{
	OGLContainerObject* co = nullptr;

	if (vBuffer)
	{
		if (!m_COMap.Get (std::make_pair(vBuffer, iBuffer), co))
			{
				co = new OGLVertexArrayObject ();
				m_COMap.Insert (std::make_pair(vBuffer, iBuffer), co);
			}
		else
		{
			fprintf (stderr, "The OGL Container Object is not found in the OGL Container Manager.\n");
		}
	}
	return co;
}

/*OGLContainerObject* OGLContainerObjectManager::Bind (VertexShader const* vShader, FragmentShader const* fShader)
{
	OGLContainerObject* co = nullptr;

	if (vShader && fShader)
	{
		if (!m_COMap.Get (std::make_pair(vShader, fShader), co))
			{
				co = new OGLProgramPipelineObject ();
				m_COMap.Insert (std::make_pair(vShader, fShader), co);
			}
	}
	return co;
}
*/
bool OGLContainerObjectManager::Unbind (DrawObject const* drawObjOne, DrawObject const* drawObjTwo)
{
	if (drawObjOne && drawObjTwo)
	{
		OGLContainerObject* vao = nullptr;

		if (m_COMap.Remove (std::make_pair(drawObjOne, drawObjTwo), vao))
		{
			delete vao;
		}
		return true;
	}
	else
	{
		fprintf (stderr, "The Unbind cannot be done as the input arguments are not correct.");
		return false;
	}
}

void OGLContainerObjectManager::UnbindAll ()
{
	if (m_COMap.HasElements ())
	{
		std::vector<OGLContainerObject*> vVao;
		m_COMap.GatherAll (vVao);
		
		for (auto iter = vVao.begin (); iter!= vVao.end (); iter++)
		{
			delete *iter;
		}
		
		m_COMap.RemoveAll ();
	}
}

OGLContainerObject* OGLContainerObjectManager::Get (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer) const
{
		OGLContainerObject* vao = nullptr;
		if (m_COMap.Get (std::make_pair(vBuffer, iBuffer), vao)) 
		{
		}

		return vao;
}
/*
OGLContainerObject* OGLContainerObjectManager::Get (VertexShader const* vShader, FragmentShader const* fShader) const
{
		OGLContainerObject* vao = nullptr;
		if (m_COMap.Get (std::make_pair(vShader, fShader), vao)) 
		{
		}

		return vao;
}
*/

OGLContainerObjectManager::COMap::~COMap ()
{
}

OGLContainerObjectManager::COMap::COMap ()
{
}