#ifndef OGL_PROGRAM_PIPELINE_OBJECT_H
#define OGL_PROGRAM_PIPELINE_OBJECT_H

//#include "oglDrawObject.h"
//#include "program.h"
#include "oglInclude.h"
#include "oglContainerObject.h"
#include "oglVertexShader.h"
#include "oglFragmentShader.h"

class OGLProgramPipelineObject : public OGLContainerObject
{
public:
	~OGLProgramPipelineObject ();
	OGLProgramPipelineObject ();

	void Enable () const;
	void Disable () const;

	void UseProgramStages (OGLVertexShader const* oglVShader, OGLFragmentShader const* oglFShader);

};
#endif