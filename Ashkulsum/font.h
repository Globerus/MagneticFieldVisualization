#ifndef FONT_H
#define FONT_H

#include "resourceBase.h"
#include "utils.h"
#include <string>
#include <boost\shared_ptr.hpp>
#include <boost\filesystem.hpp>

class Font : public ResourceBase
{
public:
	Font (std::string fileName);
	~Font () {};

	typedef boost::shared_ptr <Font> SharedPtr;

	void SetSupportedExtensions ();

	void LoadFont (std::string fileName, unsigned char* &imageData, int &img_width, int &img_height);

	unsigned char* LoadTextAtlasBMP (std::string fileName, int &width, int &height);
	unsigned char* LoadTextAtlasDDS (std::string fileName, int &width, int &height);

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