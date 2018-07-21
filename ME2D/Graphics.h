//============================================================================
// Microplane Engine - ME2D
//----------------------------------------------------------------------------
// Copyright (c) 2018 Ivan Kmeťo
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

#include <Windows.h>

#include<d2d1.h>
#pragma comment(lib, "d2d1.lib")

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;

	ID2D1SolidColorBrush* brush;

public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget() // GetRenderTarget in file [SpriteSheet.cpp]
	{
		return renderTarget;
	}

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);

	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawRectangle(float x, float y, float rectleft, float recttop, float rectright, float rectbottom, float r, float g, float b, float a);
};