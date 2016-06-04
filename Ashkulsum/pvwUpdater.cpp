#include "stdafx.h"
#include "pvwUpdater.h"


PVWUpdater::~PVWUpdater ()
{

}

PVWUpdater::PVWUpdater ()
{

}

PVWUpdater::PVWUpdater (std::shared_ptr<Camera> const& camera, BufferUpdater const& updater)
	:	m_Camera (camera),
		m_Updater (updater)
{

}

void PVWUpdater::Set (std::shared_ptr<Camera> const& camera, BufferUpdater const& updater)
{
	m_Updater = updater;
	m_Camera = camera;
}

bool PVWUpdater::Subscribe (std::shared_ptr<UniformBuffer> const& uBuffer, glm::mat4 const& worldMatrix, std::string const& pvwMatrixName)
{
	if (uBuffer && uBuffer->HasMember (pvwMatrixName))
	{
		if (m_Subscribers.find (uBuffer) == m_Subscribers.end ())
		{
			m_Subscribers.insert (std::make_pair (uBuffer, std::make_pair (&worldMatrix, pvwMatrixName)));
			return true;
		}
	}
	fprintf (stderr, "The subscribe method in PVWUpdater failed, because it has already been subscribed or the buffer has no such member.\n");
	return false;
}

bool PVWUpdater::Unsubscribe (std::shared_ptr<UniformBuffer> const& uBuffer)
{
	return m_Subscribers.erase (uBuffer) > 0;
}

void PVWUpdater::Update ()
{
	glm::mat4 projectionViewMatrix = m_Camera->GetProjectionViewMatrix ();
	std::map<PVWKey, PVWValue>::iterator iter;
	
	for (iter = m_Subscribers.begin (); iter != m_Subscribers.end (); iter++)
	{
		
		auto const worldMatrix = *iter->second.first;
		glm::mat4 PVWMatrix = projectionViewMatrix * worldMatrix;
		iter->first->SetMember (iter->second.second, PVWMatrix);	

		m_Updater(iter->first);
	}
}