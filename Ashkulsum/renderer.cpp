#include "stdafx.h"
#include "renderer.h"
#include "gameObject.h"

void Renderer::RenderObjects(std::vector<boost::shared_ptr<GameObject>> gameObjects)
{
	std::vector <boost::shared_ptr<GameObject>>::iterator itr;
	for (itr = gameObjects.begin (); itr != gameObjects.end (); itr++)
	{
		GameObject::SharedPtr gameObject = (*itr);
        gameObject->GetRenderable()->Render(*this);
	}
}