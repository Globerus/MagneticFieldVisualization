#include "stdafx.h"
#include "gameObject.h"
#include "sceneNode.h"

Renderable* GameObject::GetRenderable ()
{
	return NULL;
}

boost::shared_ptr<SceneNode> GameObject::GetSceneNode ()
{
	return NULL;
}


void GameObject::SetSceneNode (SceneNode::SharedPtr sceneNode)
{
	this->m_SceneNode = sceneNode;
}
