#ifndef GLSL_SHADER_H
#define GLSL_SHADER_H

#include "drawObject.h"

enum SType 
{
	ST_VERTEX,
	ST_FRAGMENT
};

class GLSLShader
{
public:
	GLSLShader ();

	std::string const& GetSource () const;
	std::string const& GetName () const;
	int GetType () const;

	void SetSource (std::string const sSource);
	void SetName (std::string const sName);
	void SetType (int const type);

	bool IsValid () const;

protected:
	std::string m_Name;
	std::string m_Source;
	int m_Type;
};
#endif