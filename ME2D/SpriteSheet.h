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

#pragma once

#include"Graphics.h"								// [Windows.h + D2D1.h]
#include<wincodec.h>								// WIC codec header for decoding image from file
#pragma comment(lib, "windowscodecs.lib")

class SpriteSheet
{
	Graphics* gfx;
	ID2D1Bitmap* bmp;								// Bitmap loaded file and converted to Direct2D format

	int spriteWidth;
	int spriteHeight;
	int spritesAccross;

public:
	//Constructor
	SpriteSheet(wchar_t* filename, Graphics*gfx);

	//Constructor specified for Bitmap Atlas
	SpriteSheet(wchar_t* filename, Graphics*gfx, int spriteWidth, int spriteHeight);


	~SpriteSheet();

	//Draw bitmap to the render target
	void Draw();

	//Draw method specified for Bitmap Atlas
	void Draw(
		int index,									// Index of sprite drawn within Bitmap Atlas
		float x,									// X Position to draw picture
		float y										// Y Position to draw picture
	);

};
