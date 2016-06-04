#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

#include "groupNode.h"
#include "camera.h"

class CameraNode : public GroupNode
{
public:
	CameraNode (std::shared_ptr<Camera> const& camera);

	void SetCamera (std::shared_ptr<Camera> const& camera);
	std::shared_ptr<Camera> const& GetCamera () const;

	void SetShadowMapTransformation (glm::vec4 lightDir, std::shared_ptr<Camera> camera);
	void SetAddtnlUpdate (std::function<void(CameraNode*)> const& addtnlUpdate);

protected:
	virtual void UpdateWorldData (float appTime);
	std::function<void(CameraNode*)> m_AddtnlUpdate;
	std::shared_ptr<Camera> m_Camera;
};
#endif