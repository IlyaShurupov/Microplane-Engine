//============================================================================
// Microplane Engine - ME2D
//----------------------------------------------------------------------------
// Copyright (c) 2018, 2020 Ivan Kmeťo
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//	  claim that you wrote the original software. If you use this software
//	  in a product, an acknowledgment in the product documentation would be
//	  appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//	  misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
//============================================================================

#include "SpriteSheet.hpp"
#include "CoreModule.hpp"


SpriteSheet::SpriteSheet(wchar_t* filename, Graphics*gfx)
{
	//Init
	this->gfx = gfx;
	bmp = NULL;

	//Create WIC factory
	IWICImagingFactory *wicFactory = NULL;
	HRESULT errchck005 = CoCreateInstance(
		CLSID_WICImagingFactory,                                                            // CLS ID of the object
		NULL,                                                                               // Not part of an aggregate
		CLSCTX_INPROC_SERVER,                                                               // DLL runs in the same process (We want WIC Factory to run from DLL in same process as the calling thread)
		IID_IWICImagingFactory,                                                             // Reference to interface that communicates with the object
		(LPVOID*)&wicFactory                                                                // Pointer that will contain factory
	);
	ASSERT_ME2D_AUTO(errchck005, "[ERRSPRS001]  WIC Factory failed to initialize CoCreateInstance!", "Error");

	//Create Decoder (Decoder will read file and decode it to WIC bitmap)
	IWICBitmapDecoder *wicDecoder = NULL;
	HRESULT errchck006 = wicFactory->CreateDecoderFromFilename(
		filename,                                                                           // The file name (passed from constructor "wchar_t* filename, Graphics*gfx")
		NULL,                                                                               // No prefered vendor
		GENERIC_READ,                                                                       // Reading file
		WICDecodeMetadataCacheOnLoad,                                                       // Cache on *load
		&wicDecoder                                                                         // Decoder
	);
	ASSERT_ME2D_AUTO(errchck006, "[ERRSPRS002] WIC Factory failed to Create Decoder from File!", "Error");

	//Read frame from the image (frame means if is static(1 frame)/animated image(2+ frames)
	IWICBitmapFrameDecode *wicFrame = NULL;                                                 // Return WIC bitmap
	HRESULT errchck007 = wicDecoder->GetFrame(0, &wicFrame);                                // 0 - frame number
	ASSERT_ME2D_AUTO(errchck007, "[ERRSPRS003] WIC Factory failed to read frame from the image!", "Error");

	//Create Converter
	//ID2D1 Bitmap needed, converts it from previous step
	IWICFormatConverter *wicConverter = NULL;
	HRESULT errchck008 = wicFactory->CreateFormatConverter(&wicConverter);
	ASSERT_ME2D_AUTO(errchck008, "[ERRSPRS004] WIC Factory failed to create Format Converter!", "Error");

	//Setup Converter
	HRESULT errchck009 = wicConverter->Initialize(
		wicFrame,                                                                           // Frame
		GUID_WICPixelFormat32bppPBGRA,                                                      // Output Type Pixel Format ("GUID_WICPixelFormat32bppPBGRA" makes the format 0xBBRRGGAA)
                                                                                            // "GUID_WICPixelFormat32bppPBGRAFloat" is used for extra precision in channels
		WICBitmapDitherTypeNone,                                                            // No dithering
		NULL,                                                                               // No palette
		0.0,                                                                                // Alpha Transparency in % (percentage)
		WICBitmapPaletteTypeCustom
	);
	ASSERT_ME2D_AUTO(errchck009, "[ERRSPRS005] WIC Factory failed to set up Format Converter!", "Error");

	//Use the Converter to Create ID2D1 Bitmap
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,                                                                       // Converter
		NULL,                                                                               // D2D1_BITMAP_PROPERTIES
		&bmp                                                                                // Destination D2D1 Bitmap (Output)
	);

	//Release WIC
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();

	spriteWidth = (int)bmp->GetSize().width;
	spriteHeight = (int)bmp->GetSize().height;
	spritesAccross = 1;
}

//Constructor specified for Bitmap Atlas
SpriteSheet::SpriteSheet(wchar_t* filename, Graphics*gfx, int spriteWidth, int spriteHeight) :
	SpriteSheet(filename, gfx)
{
	this->spriteHeight = spriteHeight;                                                      // Sprite height
	this->spriteWidth = spriteWidth;                                                        // Sprite width
	this->spritesAccross = (int)bmp->GetSize().width / spriteWidth;                         // This says how many sprites are accross in Bitmap Atlas
}


SpriteSheet::~SpriteSheet()
{
	if (bmp) bmp->Release();
}


//Draw entire image at (0,0)
void SpriteSheet::Draw()
{
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,                                                                                // Bitmap created in SpriteSheet::SpriteSheet
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),               // Destination Rectangle (place where you want draw bitmap)
		1.0f,                                                                               // Opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,    // Interpolation
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height)                // Source Rectangle
	);
}

//BITMAP ATLAS: Draw entire image at (0,0)
void SpriteSheet::Draw(int index, float x, float y)
{
	D2D_RECT_F src = D2D1::RectF(
		(float)((index % spritesAccross) * spriteWidth),                                    // This defines how to take single sprite from Bitmap Atlas [x starting point]
		(float)((index / spritesAccross) * spriteHeight),                                   // This defines how to take single sprite from Bitmap Atlas [y starting point]
		(float)((index % spritesAccross) * spriteWidth) + spriteWidth,                      // This defines how to take single sprite from Bitmap Atlas
		(float)((index / spritesAccross) * spriteHeight) + spriteHeight);                   // This defines how to take single sprite from Bitmap Atlas

	D2D_RECT_F dest = D2D1::RectF(
		x, y,                                                                               // Position of sprite on screen (place where you want draw bitmap)
		x + spriteWidth, y + spriteHeight);                                                 // Position of sprite on screen (place where you want draw bitmap)

	gfx->GetRenderTarget()->DrawBitmap(
		bmp,                                                                                // Bitmap created in SpriteSheet::SpriteSheet
		dest,                                                                               // Destination Rectangle (place where you want draw bitmap)
		1.0f,                                                                               // Opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,              // Interpolation
		src                                                                                 // Source Rectangle
	);
}
