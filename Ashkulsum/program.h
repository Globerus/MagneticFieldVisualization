#ifndef PROGRAM_H
#define PROGRAM_H

#include "vertexShader.h"
#include "fragmentShader.h"

class Program
{
public:
	virtual ~Program ();
	Program ();

	std::shared_ptr<VertexShader> const& GetVertexShader () const;
	std::shared_ptr<FragmentShader> const& GetFragmentShader () const;
	std::string GetProgramName () const;

public:
	void SetVertexShader (std::shared_ptr<VertexShader> const& vShader);
	void SetFragmentShader (std::shared_ptr<FragmentShader> const& fShader);
	void SetProgramName (std::string pName);

private:
	std::shared_ptr<VertexShader> m_VShader;
	std::shared_ptr<FragmentShader> m_FShader;

	std::string m_ProgName;
};

#endif