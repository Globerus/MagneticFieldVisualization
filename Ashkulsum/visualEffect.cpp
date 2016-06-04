#include "stdafx.h"
#include "visualEffect.h"

VisualEffect::~VisualEffect ()
{
}

VisualEffect::VisualEffect ()
{

}

VisualEffect::VisualEffect (std::shared_ptr<Program> const& program)
	: m_Program (program)
{
}

std::shared_ptr<Program> const& VisualEffect::GetProgram () const
{
	return m_Program;
}

std::shared_ptr<VertexShader> const& VisualEffect::GetVertexShader () const
{
	return m_Program->GetVertexShader ();
}

std::shared_ptr<FragmentShader> const& VisualEffect::GetFragmentShader () const
{
	return m_Program->GetFragmentShader ();
}