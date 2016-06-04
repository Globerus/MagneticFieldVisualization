#include "stdafx.h"
#include "texture.h"

Texture::Texture (std::string fileName)
{
	unsigned char* imageData;
	int img_width, img_height;

	this->SetSupportedExtensions ();
	LoadImage (fileName, imageData, img_width, img_height);

	this->SetImageData (imageData);
	this->SetImageWidth (img_width);
	this->SetImageHeight (img_height);
}

void Texture::SetSupportedExtensions ()
{
	std::string supportedExtensions[] = {".png", ".bmp", ".jpg", ".jpeg"};
	std::vector <std::string> supExt (begin(supportedExtensions), end (supportedExtensions));

	this->m_SupportedExtensions = supExt;
}

void Texture::LoadImage (std::string fileName, unsigned char* &imageData, int &img_width, int &img_height)
{
	std::string extension = boost::filesystem::extension (fileName);
	
	if (this->IsFileSupported (extension))
	{
		std::string fullDirPath = Utils::GetFullDirPath (fileName);
		imageData = SOIL_load_image(fullDirPath.c_str (), &img_width, &img_height, 0, SOIL_LOAD_RGB);

		if (imageData == nullptr)
			throw std::invalid_argument ("Error while opening the file! File not found");
	}
	else
		throw std::invalid_argument ("Error while opening the file! Unsupported format");
}

unsigned char* Texture::GetImageData ()
{
	return this->m_ImageData;
}

int Texture::GetImageWidth ()
{
	return this->m_ImageWidth;
}

int Texture::GetImageHeight ()
{
	return this->m_ImageHeight;
}


void Texture::SetImageData (unsigned char* imageData)
{
	this->m_ImageData = imageData;
}

void Texture::SetImageWidth (int width)
{
	this->m_ImageWidth = width;
}

void Texture::SetImageHeight (int height)
{
	this->m_ImageHeight = height;
}