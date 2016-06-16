#ifndef DRAW_OBJECT_H
#define DRAW_OBJECT_H

#include <vector>
#include <string>
#include "include.h"

enum DrawObjectType 
{
	DP_DRAW_OBJECT,
		DP_RESOURCE,
	DP_BUFFER,
		DP_VERTEX_BUFFER,
		DP_INDEX_BUFFER,
		DP_UNIFORM_BUFFER,
	DP_TEXTURE,
		DP_TEXTURE_SOLO,
			DP_TEXTURE_1,
			DP_TEXTURE_2,
				DP_TEXTURE_RT,
				DP_TEXTURE_DS,
		DP_TEXTURE_ARRAY,
			DP_TEXTURE1_ARRAY,
			DP_TEXTURE2_ARRAY,
	DP_DRAWING_STATE,
		DP_BLEND_STATE,
		DP_DEPTH_STENCIL_STATE,
		DP_RASTERIZER_STATE,
		DP_SAMPLER_STATE,
	DP_SHADER,
		DP_VERTEX_SHADER,
		DP_FRAGMENT_SHADER,

	DP_NUM_TYPES
};
class DrawObject 
{

public:
	virtual ~DrawObject ();

	DrawObjectType GetType () const;
protected:
	DrawObject ();
	
protected:
	DrawObjectType m_Type;
};
#endif