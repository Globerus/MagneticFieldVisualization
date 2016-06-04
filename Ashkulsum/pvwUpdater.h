#ifndef PVW_UPDATER_H
#define PVW_UPDATER_H

#include "camera.h"
#include "uniformBuffer.h"
#include "geometryNode.h"
#include <map>

class PVWUpdater 
{
public:

	virtual ~PVWUpdater ();

	PVWUpdater ();
	PVWUpdater (std::shared_ptr<Camera> const& camera, BufferUpdater const& updater);
	
	void  Set (std::shared_ptr<Camera> const& camera, BufferUpdater const& updater);
	bool Subscribe (std::shared_ptr<UniformBuffer> const& uBuffer, glm::mat4 const& worldMatrix, std::string const& pvwMatrixName = "pvwMatrix");
	bool Unsubscribe (std::shared_ptr<UniformBuffer> const& uBuffer);

	void Update ();

protected:
	std::shared_ptr<Camera> m_Camera;
	BufferUpdater m_Updater;
	typedef std::shared_ptr<UniformBuffer> PVWKey;
    typedef std::pair<glm::mat4 const*, std::string> PVWValue;
	std::map<PVWKey, PVWValue> m_Subscribers;
};
#endif