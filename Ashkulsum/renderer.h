#ifndef RENDERER_H
#define RENDERER_H

#include <boost\shared_ptr.hpp>
#include <boost\make_shared.hpp>
#include <vector>

class GameObject;

typedef enum {NO_CULL, CW_CULL, CCW_CULL} CullMode;
typedef enum {	CMPF_ALWAYS_FAIL, 	
				CMPF_ALWAYS_PASS, 	
				CMPF_LESS, 	
				CMPF_LESS_EQUAL, 	
				CMPF_EQUAL, 	
				CMPF_NOT_EQUAL, 	
				CMPF_GREATER_EQUAL, 	
				CMPF_GREATER	} CompareFunc;

class Renderer 
{
public:
	
	~Renderer () {};

	void RenderObjects(std::vector<boost::shared_ptr<GameObject>> gameObjects); 

	void EnableCullFace (bool enable);
	void EnableDepthTest (bool enable);
	void FrontFace (CullMode mode);
	void DepthFunc (CompareFunc func);
	void VertexProgramPointSize (bool enable);

	boost::shared_ptr <GameObject> gf;
};
#endif