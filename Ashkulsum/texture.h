#ifndef TEXTURE_H
#define TEXTURE_H

#include "resourceBase.h"
#include "utils.h"
#include "SOIL.h"
#include <boost\shared_ptr.hpp>
#include <boost\filesystem.hpp>

class Texture : public ResourceBase
{
public:
	Texture (std::string fileName);
	~Texture () {};

	typedef boost::shared_ptr <Texture> SharedPtr;

	void SetSupportedExtensions ();

	void LoadImage (std::string fileName, unsigned char* &imageData, int &img_width, int &img_height);

	unsigned char* GetImageData ();
	int GetImageWidth ();
	int GetImageHeight ();

	void SetImageData (unsigned char* imageData);
	void SetImageWidth (int imageWidth);
	void SetImageHeight (int imageHeigth);

private:
	unsigned char* m_ImageData;
	int m_ImageWidth, m_ImageHeight;

};

#endif