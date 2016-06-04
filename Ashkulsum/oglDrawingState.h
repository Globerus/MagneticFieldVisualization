#ifndef OGL_DRAWSTATE_H
#define OGL_DRAWSTATE_H

#include "oglDrawObject.h"
#include "drawingState.h"

class OGLDrawingState : public OGLDrawObject
{
protected:
	OGLDrawingState (std::shared_ptr<const DrawingState> drawingState);

};
#endif