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

	//Circles
	gfx->DrawCircle(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 60.0f, 40.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawCircle(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 60.0f, 40.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawCircle(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 60.0f, 40.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawCircle(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 60.0f, 40.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawCircle(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 60.0f, 40.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawCircle(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 60.0f, 40.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawCircle(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 60.0f, 40.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//Ellipses
	gfx->DrawEllipse(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 160.0f, 40.0f, 30.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawEllipse(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 160.0f, 40.0f, 30.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawEllipse(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 160.0f, 40.0f, 30.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawEllipse(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 160.0f, 40.0f, 30.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawEllipse(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 160.0f, 40.0f, 30.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawEllipse(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 160.0f, 40.0f, 30.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawEllipse(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 160.0f, 40.0f, 30.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//Squares
	gfx->DrawSquare(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 260.0f, 80.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquare(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 260.0f, 80.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquare(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 260.0f, 80.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquare(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 260.0f, 80.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquare(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 260.0f, 80.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquare(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 260.0f, 80.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquare(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 260.0f, 80.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//Rounded Squares
	gfx->DrawSquareRounded(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 365.0f, 80.0f, 10.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquareRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 365.0f, 80.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquareRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 365.0f, 80.0f, 10.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquareRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 365.0f, 80.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquareRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 365.0f, 80.0f, 10.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquareRounded(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 365.0f, 80.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawSquareRounded(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 365.0f, 80.0f, 10.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//Rectangles
	gfx->DrawRect(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 460.0f, 90.0f, 60.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRect(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 460.0f, 90.0f, 60.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRect(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 460.0f, 90.0f, 60.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRect(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 460.0f, 90.0f, 60.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRect(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 460.0f, 90.0f, 60.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRect(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 460.0f, 90.0f, 60.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRect(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 460.0f, 90.0f, 60.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//Rounded Rectangles
	gfx->DrawRectRounded(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 550.0f, 90.0f, 60.0f, 10.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRectRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 550.0f, 90.0f, 60.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRectRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 550.0f, 90.0f, 60.0f, 10.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRectRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 550.0f, 90.0f, 60.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRectRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 550.0f, 90.0f, 60.0f, 10.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRectRounded(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 550.0f, 90.0f, 60.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
	gfx->DrawRectRounded(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 550.0f, 90.0f, 60.0f, 10.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}
