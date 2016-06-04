#include "stdafx.h"
#include "oglDrawingState.h"

OGLDrawingState::OGLDrawingState (std::shared_ptr<const DrawingState> drawingState)
	:	OGLDrawObject (drawingState)
{

}