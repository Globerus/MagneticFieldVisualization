#include "stdafx.h"
#include "font.h"

Font::Font (std::string fileName)
{
	unsigned char* imageData;
	int img_width, img_height;

	this->SetSupportedExtensions ();
	LoadFont (fileName, imageData, img_width, img_height);

	this->SetImageData (imageData);
	this->SetImageWidth (img_width);
	this->SetImageHeight (img_height);
}
void Font::SetSupportedExtensions ()
{
	std::string supportedExtensions[] = {".bmp", ".dds"};
	std::vector <std::string> supExt (begin(supportedExtensions), end (supportedExtensions));

	this->m_SupportedExtensions = supExt;
}

void Font::LoadFont (std::string fileName, unsigned char* &imageData, int &img_width, int &img_height)
{
	std::string extension = boost::filesystem::extension (fileName);
	
	if (this->IsFileSupported (extension))
	{
		std::string fullDirPath = Utils::GetFullDirPath (fileName);

		if (extension == ".dds")
			imageData = LoadTextAtlasDDS (fullDirPath, img_width, img_height);
		else if (extension == ".bmp")
			imageData = LoadTextAtlasBMP (fullDirPath, img_width, img_height);
	}
	else
		throw std::invalid_argument ("Error while opening the file! Unsupported format");
}

unsigned char* Font::LoadTextAtlasBMP (std::string fileName, int &width, int &height)
{
	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE* file; 
	errno_t err = fopen_s(&file, fileName.c_str (),"rb");
	if (!file)		
		throw std::invalid_argument ("Error while opening the file! File not found");
	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if ( fread(header, 1, 54, file)!=54 ){ 
		throw std::invalid_argument ("Not a correct BMP file");
	}
	// A BMP files always begins with "BM"
	if ( header[0]!='B' || header[1]!='M' ){
		throw std::invalid_argument ("Not a correct BMP file");
	}
	// Make sure this is a 24bpp file
	if ( *(int*)&(header[0x1E])!=0  )         {throw std::invalid_argument ("Not a correct BMP file");}
	if ( *(int*)&(header[0x1C])!=24 )         {throw std::invalid_argument ("Not a correct BMP file");}

	// Read the information about the image
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	// Everything is in memory now, the file wan be closed
	fclose (file);

	return data;
}

unsigned char* Font::LoadTextAtlasDDS (std::string fileName, int &width, int &height)
{
	unsigned char header[124];

	FILE *fp; 
  
	errno_t err = fopen_s(&fp, fileName.c_str (), "rb"); 
	if (fp == NULL){
		throw std::invalid_argument ("Error while opening the file! File not found");
	}

	char filecode[4]; 
	fread(filecode, 1, 4, fp); 
	if (strncmp(filecode, "DDS ", 4) != 0) { 
		fclose(fp); 
		throw std::invalid_argument ("Not a correct DDS file"); 
	}
	

	fread(&header, 124, 1, fp); 

	height      = *(unsigned int*)&(header[8 ]);
	width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);

 
	unsigned char * buffer;
	unsigned int bufsize;

	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
	fread(buffer, 1, bufsize, fp); 

	fclose(fp);
	return buffer;
}

unsigned char* Font::GetImageData ()
{
	return this->m_ImageData;
}

int Font::GetImageWidth ()
{
	return this->m_ImageWidth;
}

int Font::GetImageHeight ()
{
	return this->m_ImageHeight;
}


void Font::SetImageData (unsigned char* imageData)
{
	this->m_ImageData = imageData;
}

void Font::SetImageWidth (int width)
{
	this->m_ImageWidth = width;
}

void Font::SetImageHeight (int height)
{
	this->m_ImageHeight = height;
}