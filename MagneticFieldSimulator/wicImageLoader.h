#pragma warning (disable : 4005)
#ifndef WIC_IMAGE_LOADER_H
#define WIC_IMAGE_LOADER_H

#include <atlbase.h>
#include <wincodec.h>
#include "texture2.h"
#include "pathEnvironment.h"

#define IfFailedThrowHR(expr) {HRESULT hr = (expr); if (FAILED(hr)) throw hr;}

class WICImageLoader
{
public:
	virtual ~WICImageLoader ();
	WICImageLoader ();

	struct ImageFormat
	{
		ContainerType format;
		GUID const* wicInputGUID;
		GUID const* wicConvertGUID;
	};
	enum {NUM_LOAD_FORMATS = 9};

	static ImageFormat const m_ImageFormatLoadMap [NUM_LOAD_FORMATS];

	static std::shared_ptr<Texture2> Load(std::string const& fileName, bool hasMipMap, UINT nFrame = 0);

};
#endif