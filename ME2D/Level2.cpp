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

#include "stdafx.h"
#include "GameController.h"
#include "Graphics.h"
#include "Level2.h"


void Level2::Load()
{
}

void Level2::UnLoad()
{
}

void Level2::Update(double timeTotal, double timeDelta)
{
}

void Level2::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	
	// Circles
	gfx->RenderCircleRGBA(75.0f, 60.0f, 40.0f, 1.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderCircleRGBAF(200.0f, 60.0f, 40.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderCircleRGBASF(325.0f, 60.0f, 40.0f, 1.0f, 0.0f, 1.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// Ellipses
	gfx->RenderEllipseRGBA(75.0f, 160.0f, 40.0f, 30.0f, 1.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderEllipseRGBAF(200.0f, 160.0f, 40.0f, 30.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderEllipseRGBASF(325.0f, 160.0f, 40.0f, 30.f, 1.0f, 0.0f, 1.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// Squares
	gfx->RenderSquareRGBA(75.0f, 260.0f, 80.0f, 1.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderSquareRGBAF(200.0f, 260.0f, 80.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderSquareRGBASF(325.0f, 260.0f, 80.0f, 1.0f, 0.0f, 1.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// Rounded Squares
	gfx->RenderRoundSquareRGBA(75.0f, 365.0f, 80.0f, 10.0f, 1.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderRoundSquareRGBAF(200.0f, 365.0f, 80.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderRoundSquareRGBASF(325.0f, 365.0f, 80.0f, 10.0f, 1.0f, 0.0f, 1.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// Rectangles
	gfx->RenderRectRGBA(75.0f, 460.0f, 90.0f, 60.0f, 1.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderRectRGBAF(200.0f, 460.0f, 90.0f, 60.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderRectRGBASF(325.0f, 460.0f, 90.0f, 60.0f, 1.0f, 0.0f, 1.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// Rounded Rectangles
	gfx->RenderRoundRectRGBA(75.0f, 550.0f, 90.0f, 60.0f, 10.0f, 1.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderRoundRectRGBAF(200.0f, 550.0f, 90.0f, 60.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f);
	gfx->RenderRoundRectRGBASF(325.0f, 550.0f, 90.0f, 60.0f, 10.0f, 1.0f, 0.0f, 1.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}
