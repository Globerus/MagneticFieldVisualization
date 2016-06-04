#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "renderableObject.h"
#include "boost\shared_ptr.hpp"

class SceneNode;

class GameObject 
{
public:
	typedef boost::shared_ptr <GameObject> SharedPtr;

	GameObject () {};
	~GameObject () {};

	virtual Renderable* GetRenderable ();
	virtual boost::shared_ptr<SceneNode> GetSceneNode ();

	void SetSceneNode (boost::shared_ptr<SceneNode> sceneNode);

protected:
	boost::shared_ptr<SceneNode> m_SceneNode;
};
#endif