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
	ID2D1Factory* m_pFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	ID2D1StrokeStyle* m_pStrokeStyle;
	ID2D1SolidColorBrush* m_pMainBrush;
	ID2D1SolidColorBrush* m_pFillBrush;

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


	//-----------------------------------------------[OBJECTS: 2D GEOMETRY]-----------------------------------------------

	void RenderCircleRGBA(float x, float y, float radius, float r, float g, float b, float a, float strokesize);
	void RenderCircleRGBAF(float x, float y, float radius, float r, float g, float b, float a, float strokesize);
	void RenderCircleRGBASF(float x, float y, float radius, float r, float g, float b, float a, float strokesize, float fill_r, float fill_g, float fill_b, float fill_a);

	void RenderCircleRGBADotted(float x, float y, float radius, float r, float g, float b, float a, float strokesize);

	void RenderEllipseRGBA(float x, float y, float xRadius, float yRadius, float r, float g, float b, float a, float strokesize);
	void RenderEllipseRGBAF(float x, float y, float xRadius, float yRadius, float r, float g, float b, float a, float strokesize);
	void RenderEllipseRGBASF(float x, float y, float xRadius, float yRadius, float r, float g, float b, float a, float strokesize, float fill_r, float fill_g, float fill_b, float fill_a);

	void RenderSquareRGBA(float x, float y, float size, float r, float g, float b, float a, float strokesize);
	void RenderSquareRGBAF(float x, float y, float size, float r, float g, float b, float a, float strokesize);
	void RenderSquareRGBASF(float x, float y, float size, float r, float g, float b, float a, float strokesize, float fill_r, float fill_g, float fill_b, float fill_a);

	void RenderRoundSquareRGBA(float x, float y, float size, float radius, float r, float g, float b, float a, float strokesize);
	void RenderRoundSquareRGBAF(float x, float y, float size, float radius, float r, float g, float b, float a, float strokesize);
	void RenderRoundSquareRGBASF(float x, float y, float size, float radius, float r, float g, float b, float a, float strokesize, float fill_r, float fill_g, float fill_b, float fill_a);

	void RenderRectRGBA(float x, float y, float width, float height, float r, float g, float b, float a, float strokesize);
	void RenderRectRGBAF(float x, float y, float width, float height, float r, float g, float b, float a, float strokesize);
	void RenderRectRGBASF(float x, float y, float width, float height, float r, float g, float b, float a, float strokesize, float fill_r, float fill_g, float fill_b, float fill_a);

	void RenderRoundRectRGBA(float x, float y, float width, float height, float radius, float r, float g, float b, float a, float strokesize);
	void RenderRoundRectRGBAF(float x, float y, float width, float height, float radius, float r, float g, float b, float a, float strokesize);
	void RenderRoundRectRGBASF(float x, float y, float width, float height, float radius, float r, float g, float b, float a, float strokesize, float fill_r, float fill_g, float fill_b, float fill_a);
};
