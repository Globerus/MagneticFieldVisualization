#include "stdafx.h"
#include "wicImageLoader.h"

WICImageLoader::WICImageLoader()
{
    CoInitialize(nullptr);
}

WICImageLoader::~WICImageLoader()
{
    CoUninitialize();
}

std::shared_ptr<Texture2> WICImageLoader::Load(std::string const& fileName, bool hasMipMap, UINT nFrame/* = 0*/)
{
		PathEnvironment pathEnvironment;
		
		std::string filePath = pathEnvironment.GetExeDir () + fileName;
		CComPtr<IWICImagingFactory> wicImagingFactory;

		HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory, (LPVOID*)&wicImagingFactory);

		if (FAILED(hr))
		{
			fprintf (stderr, "The load method in WICImageLoader failed, because it was unable to create WIC imaging factory.\n");
			return nullptr;
		}
 
        // Create a decoder for the given image file
		std::wstring wfilePath (filePath.begin (), filePath.end ());
		
		CComPtr<IWICBitmapDecoder> decoder;

        hr = wicImagingFactory->CreateDecoderFromFilename(
			wfilePath.c_str (), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
		
		if (FAILED(hr))
		{
			fprintf (stderr, "The load method in WICImageLoader failed, because the wicFactory->CreateDecoderFromFilename failed.\n");
			return nullptr;
		}
        // Validate the given frame index nFrame
        UINT nCount = 0;
        // Get the number of frames in this image
        if (SUCCEEDED(decoder->GetFrameCount(&nCount)))
        {
            if (nFrame >= nCount)
                nFrame = nCount - 1; // If the requested frame number is too big, default to the last frame
        }
        // Retrieve the requested frame of the image from the decoder
		CComPtr<IWICBitmapFrameDecode> frame;

        hr = decoder->GetFrame(nFrame, &frame);
		
		if (FAILED(hr))
		{
			fprintf (stderr, "The load method in WICImageLoader failed, because the wicDecoder->GetFrame failed.\n");
			return nullptr;
		}

		WICPixelFormatGUID wicSourceGUID;
		hr = frame->GetPixelFormat(&wicSourceGUID);
		if (FAILED(hr))
		{
			fprintf (stderr, "The load method in WICImageLoader failed, because the wicFrameDecode->GetPixelFormat failed.\n");
			return nullptr;
		}
		
		WICPixelFormatGUID wicConvertGUID = GUID_WICPixelFormat32bppRGBA;
		ContainerType format = DP_R8G8B8A8_UNSIGNED_NORM;
		
		for (int i = 0; i < NUM_LOAD_FORMATS; i++)
		{
			if (IsEqualGUID (wicSourceGUID, *m_ImageFormatLoadMap[i].wicInputGUID))
			{
				if (m_ImageFormatLoadMap[i].wicConvertGUID)
				{
					wicConvertGUID = *m_ImageFormatLoadMap[i].wicConvertGUID;
				}
				else
				{
					wicConvertGUID = *m_ImageFormatLoadMap[i].wicInputGUID;
				}

				format = m_ImageFormatLoadMap[i].format;
			}
		}
        // Convert the format of the image frame to 32bppBGR
		CComPtr<IWICFormatConverter> convertedFrame;
        hr = wicImagingFactory->CreateFormatConverter(&convertedFrame);

		if (FAILED(hr))
        {
			fprintf (stderr, "The load method in WICImageLoader failed, because the wicFactory->CreateFormatConverter failed.\n");
            return nullptr;
        }
        hr = convertedFrame->Initialize(
                frame,                        // Source frame to convert
                wicConvertGUID,     // The desired pixel format
                WICBitmapDitherTypeNone,         // The desired dither pattern
                NULL,                            // The desired palette 
                0.f,                             // The desired alpha threshold
                WICBitmapPaletteTypeCustom       // Palette translation type
                );

		if (FAILED(hr))
        {
			fprintf (stderr, "The load method in WICImageLoader failed, because the convertedFrame->Initialize failed.\n");
            return nullptr;
        }
  
		UINT width, height;
		hr = convertedFrame->GetSize(&width, &height);

		if (FAILED(hr))
		{
			fprintf (stderr, "The load method in WICImageLoader failed, because the convertedFrame->GetSize failed.\n");
			return nullptr;
		}

		
		std::shared_ptr<Texture2> texture = std::make_shared<Texture2>(
        format, width, height, hasMipMap);

		UINT const stride = width * texture->GetElementSize();
		UINT const imageSize = stride * height;

		hr = convertedFrame->CopyPixels(nullptr, stride, imageSize, texture->Get<BYTE>());

		if (FAILED(hr))
		{
			fprintf (stderr, "The load method in WICImageLoader failed, because the wicBitmapSource->CopyPixels failed.\n");
			return nullptr;
		}


		return texture;
   
}

WICImageLoader::ImageFormat const WICImageLoader::m_ImageFormatLoadMap [NUM_LOAD_FORMATS] = 
{
	{ DP_R8_UNSIGNED_NORM, &GUID_WICPixelFormat2bppGray, &GUID_WICPixelFormat8bppGray },
    { DP_R8_UNSIGNED_NORM, &GUID_WICPixelFormat4bppGray, &GUID_WICPixelFormat8bppGray },
    { DP_R8_UNSIGNED_NORM, &GUID_WICPixelFormat8bppGray, nullptr },
    { DP_R16_UNSIGNED_NORM, &GUID_WICPixelFormat16bppGray, nullptr },
    { DP_R32_FLOAT, &GUID_WICPixelFormat32bppGrayFloat, nullptr },
    { DP_R8G8B8A8_UNSIGNED_NORM, &GUID_WICPixelFormat32bppRGBA, nullptr },
    { DP_R8G8B8A8_UNSIGNED_NORM, &GUID_WICPixelFormat32bppBGRA, &GUID_WICPixelFormat32bppRGBA },
    { DP_R16G16B16A16_UNSIGNED_NORM, &GUID_WICPixelFormat64bppRGBA, nullptr },
    { DP_R16G16B16A16_UNSIGNED_NORM, &GUID_WICPixelFormat64bppBGRA, &GUID_WICPixelFormat64bppRGBA }
};