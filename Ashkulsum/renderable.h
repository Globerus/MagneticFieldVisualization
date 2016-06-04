#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "boost\shared_ptr.hpp"
#include "renderer.h"
//class Renderer;

class Renderable 
{
public:
	typedef boost::shared_ptr <Renderable> SharedPtr;

	Renderable () {};
	virtual ~Renderable () {};
	
	virtual void Render (Renderer &renderer)  = 0;
};
#endif