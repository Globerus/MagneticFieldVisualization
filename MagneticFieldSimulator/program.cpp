#include "stdafx.h"
#include "program.h"

Program::~Program ()
{

}

Program::Program ()
{

}

std::shared_ptr<VertexShader> const& Program::GetVertexShader () const
{
	return m_VShader;
}
std::shared_ptr<FragmentShader> const& Program::GetFragmentShader () const
{
	return m_FShader;
}

std::string Program::GetProgramName () const
{
	return m_ProgName;
}

void Program::SetVertexShader (std::shared_ptr<VertexShader> const& vShader)
{
	m_VShader = vShader;
}
void Program::SetFragmentShader (std::shared_ptr<FragmentShader> const& fShader)
{
	m_FShader = fShader;
}

void Program::SetProgramName (std::string pName)
{
	m_ProgName = pName;
}

