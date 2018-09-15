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
#include <sstream>

#include<d2d1.h>
#pragma comment(lib, "d2d1.lib")

#include<dwrite.h>
#pragma comment(lib, "dwrite.lib")


typedef enum ME_TYPE2D_FILL {
	ME2D_FILL_NONE = 0,
	ME2D_FILL_PRIMARY = 1,
	ME2D_FILL_SECONDARY = 2
};

typedef enum ME_TYPE2D_OUTLINE {
	ME2D_OUTLINE_NONE = 0,
	ME2D_OUTLINE_SOLID = 1,
	ME2D_OUTLINE_DOTTED = 2,
	ME2D_OUTLINE_DASHED = 3,
	ME2D_OUTLINE_DASH_DOTTED = 4,
	ME2D_OUTLINE_DASH_DOT_DOTTED = 5
};


class Graphics
{
	//Direct2D
	ID2D1Factory* m_pFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	ID2D1StrokeStyle* m_pStrokeStyleDashDotDotted;
	ID2D1StrokeStyle* m_pStrokeStyleDashDotted;
	ID2D1StrokeStyle* m_pStrokeStyleDotted;
	ID2D1StrokeStyle* m_pStrokeStyleDashed;
	ID2D1SolidColorBrush* m_pOutlineBrush;
	ID2D1SolidColorBrush* m_pFillBrush;

	//DirectWrite
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pTextBrush;
	std::wstring printText;

public:
	Graphics();
	~Graphics();

	Graphics(const Graphics &) = delete;
	Graphics(Graphics &&) = delete;
	Graphics& operator =(const Graphics &) = delete;
	Graphics& operator =(Graphics &&) = delete;

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget() // GetRenderTarget in file [SpriteSheet.cpp]
	{
		return m_pRenderTarget;
	}

	void BeginDraw() { m_pRenderTarget->BeginDraw(); }
	void EndDraw() { m_pRenderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);

	void RenderText(std::wstring text, int offsetX, int offsetY, float r, float g, float b, float a);


	//-----------------------------------------------[OBJECTS: 2D GEOMETRY]-----------------------------------------------

	void DrawCircle(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float radius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
	void DrawEllipse(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float xRadius, float yRadius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
	void DrawSquare(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float size, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
	void DrawSquareRounded(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float size, float radius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
	void DrawRect(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float width, float height, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
	void DrawRectRounded(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float width, float height, float radius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
};
