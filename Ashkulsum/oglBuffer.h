#ifndef OGLBUFFER_H
#define OGLBUFFER_H

#include "oglResource.h"
#include "buffer.h"

class OGLBuffer : public OGLResource
{
protected:
	virtual ~OGLBuffer ();
	OGLBuffer (std::shared_ptr<const Buffer> buffer, GLenum type);

public:
	std::shared_ptr<Buffer> GetBuffer () const;
	inline GLenum GetType () const;
	inline GLenum GetUsage () const;

	void Initialize ();
	virtual bool Update ();

protected:
	GLenum m_Type;
	GLenum m_Usage;

};

GLenum OGLBuffer::GetType () const
{
	return m_Type;
}

GLenum OGLBuffer::GetUsage () const
{
	return m_Usage;
}
#endif