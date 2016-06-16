#include "stdafx.h"
#include "oglVertexArrayObjectManager.h"

OGLVertexArrayObjectManager::~OGLVertexArrayObjectManager ()
{
	if (m_Map.HasElements ())
	{
		UnbindAll ();
	}
}

OGLVertexArrayObjectManager::OGLVertexArrayObjectManager ()
{
}

OGLVertexArrayObject* OGLVertexArrayObjectManager::Bind (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer)
{
	OGLVertexArrayObject* vao = nullptr;

	if (vBuffer && iBuffer)
	{
		if (!m_Map.Get (std::make_pair(vBuffer, iBuffer), vao))
			{
				vao = new OGLVertexArrayObject ();
				m_Map.Insert (std::make_pair(vBuffer, iBuffer), vao);
			}
	}
	return vao;
}

bool OGLVertexArrayObjectManager::Unbind (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer)
{
	if (vBuffer && iBuffer)
	{
		OGLVertexArrayObject* vao = nullptr;

		if (m_Map.Remove (std::make_pair(vBuffer, iBuffer), vao))
		{
			delete vao;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void OGLVertexArrayObjectManager::UnbindAll ()
{
	if (m_Map.HasElements ())
	{
		std::vector<OGLVertexArrayObject*> vVao;
		m_Map.GatherAll (vVao);
		
		for (auto iter = vVao.begin (); iter!= vVao.end (); iter++)
		{
			delete *iter;
		}
		
		m_Map.RemoveAll ();
	}
}

OGLVertexArrayObject* OGLVertexArrayObjectManager::Get (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer) const
{
		OGLVertexArrayObject* vao = nullptr;
		if (m_Map.Get (std::make_pair(vBuffer, iBuffer), vao)) 
		{
		}

		return vao;
}