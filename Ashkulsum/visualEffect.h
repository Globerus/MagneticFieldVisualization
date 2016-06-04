#ifndef VISUAL_EFFECT_H
#define VISUAL_EFFECT_H

#include "program.h"

class VisualEffect
{
public:
	virtual ~VisualEffect ();

	VisualEffect ();
	VisualEffect (std::shared_ptr<Program> const& program);

	std::shared_ptr<Program> const& GetProgram () const;
	std::shared_ptr<VertexShader> const& GetVertexShader () const;
	std::shared_ptr<FragmentShader> const& GetFragmentShader () const;

protected:
	std::shared_ptr<Program> m_Program;
	BufferUpdater m_BufferUpdater;
};
#endif