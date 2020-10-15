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

#include "stdafx.hpp"


typedef enum ME_TYPE2D_FILL : uint8_t {
	ME2D_FILL_NONE = 0x00,
	ME2D_FILL_PRIMARY = 0x01,
	ME2D_FILL_SECONDARY = 0x02
} ME_TYPE2D_FILL;

typedef enum ME_TYPE2D_OUTLINE : uint8_t {
	ME2D_OUTLINE_NONE = 0x00,
	ME2D_OUTLINE_SOLID = 0x01,
	ME2D_OUTLINE_DOTTED = 0x02,
	ME2D_OUTLINE_DASHED = 0x03,
	ME2D_OUTLINE_DASH_DOTTED = 0x04,
	ME2D_OUTLINE_DASH_DOT_DOTTED = 0x05
} ME_TYPE2D_OUTLINE;


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
	IDWriteTextFormat* m_pTextFormatMenu;
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

	void RenderText(std::wstring text, float offsetX, float offsetY, float r, float g, float b, float a);
	void RenderTextMenu(std::wstring text, float offsetX, float offsetY, float r, float g, float b, float a);


	//--------------------------------------[PASS MOUSE POSITON RELATIVE TO WINDOW]---------------------------------------
	uint16_t mousePosX;
	uint16_t mousePosY;

	//-----------------------------------------------[OBJECTS: 2D GEOMETRY]-----------------------------------------------

	void DrawCircle(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float radius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
	void DrawEllipse(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float xRadius, float yRadius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
	void DrawSquare(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float size, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
	void DrawSquareRounded(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float size, float radius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
	void DrawRect(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float width, float height, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
	void DrawRectRounded(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float width, float height, float radius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a);
	void DrawLine(ME_TYPE2D_OUTLINE outlineType, float outlineSize, float point0X, float point0Y, float point1X, float point1Y, float r, float g, float b, float a);
};
