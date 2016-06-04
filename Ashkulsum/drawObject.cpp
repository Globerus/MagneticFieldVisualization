#include "stdafx.h"
#include "drawObject.h"

DrawObject::DrawObject ()
{
	m_Type = DP_DRAW_OBJECT;
}

DrawObject::~DrawObject ()
{

}

DrawObjectType DrawObject::GetType () const
{
	return m_Type;
}