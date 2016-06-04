#pragma once

#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include "shaderManager.h"
#include "renderable.h"
#include "boost\shared_ptr.hpp"
//#include "renderer.h"


template <typename T>
class RenderableObject : virtual public Renderable
{
public:
	typedef boost::shared_ptr<RenderableObject<T>> SharedPtr;
	
	RenderableObject () : m_Object (nullptr) {};
	RenderableObject (typename T::SharedPtr object) : m_Object (object) {};
    virtual ~RenderableObject(){};

    virtual void Render(Renderer& renderer) 
	{
		Render(renderer, m_Object);		
	};

protected:
	virtual void Render(Renderer &renderer, typename T::SharedPtr object)  = 0;
	typename T::SharedPtr m_Object;
	
};
#endif