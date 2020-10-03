//============================================================================
// Microplane Engine - ME2D
//
// Scene: Level 2 - Basic Geometries
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

#include "stdafx.hpp"
#include "GameController.h"
#include "Graphics.h"
#include "Level2.h"


void Level2::Load()
{
	ui_shapes = new SpriteSheet(L"Edit/dta/dsprites/ui_shapes.png", gfx, 32, 32);
	uiMenuLID = 1;
}

void Level2::UnLoad()
{
	if (ui_shapes) delete ui_shapes;
}

void Level2::Update(double timeTotal, double timeDelta)
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		if (uiMenuLID == UI_MENULIST_MAX) {
			uiMenuLID = UI_MENULIST_MAX;
		}
		else {
			uiMenuLID += 1;
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		if (uiMenuLID == UI_MENULIST_MIN) {
			uiMenuLID = UI_MENULIST_MIN;
		}
		else {
			uiMenuLID -= 1;
		}
	}
}

void Level2::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);

	//Circles
	if (uiMenuLID == 1) {
		ui_shapes->Draw(SPRITEFRAME_UI_CIRCLE_ACTIVE, (SCREEN_WIDTH / 2.0f) - (7 * 16.0f), 30.0f);

		gfx->DrawCircle(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 160.0f, 40.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawCircle(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 160.0f, 40.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawCircle(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 160.0f, 40.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawCircle(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 160.0f, 40.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawCircle(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 160.0f, 40.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawCircle(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 160.0f, 40.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawCircle(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 160.0f, 40.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		ui_shapes->Draw(SPRITEFRAME_UI_CIRCLE_NACTIVE, (SCREEN_WIDTH / 2.0f) - (7 * 16.0f), 30.0f);
	}

	//Ellipses
	if (uiMenuLID == 2) {
		ui_shapes->Draw(SPRITEFRAME_UI_ELLIPSE_ACTIVE, (SCREEN_WIDTH / 2.0f) - (5 * 16.0f), 30.0f);

		gfx->DrawEllipse(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 160.0f, 40.0f, 30.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawEllipse(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 160.0f, 40.0f, 30.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawEllipse(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 160.0f, 40.0f, 30.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawEllipse(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 160.0f, 40.0f, 30.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawEllipse(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 160.0f, 40.0f, 30.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawEllipse(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 160.0f, 40.0f, 30.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawEllipse(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 160.0f, 40.0f, 30.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		ui_shapes->Draw(SPRITEFRAME_UI_ELLIPSE_NACTIVE, (SCREEN_WIDTH / 2.0f) - (5 * 16.0f), 30.0f);
	}

	//Squares
	if (uiMenuLID == 3) {
		ui_shapes->Draw(SPRITEFRAME_UI_SQUARE_ACTIVE, (SCREEN_WIDTH / 2.0f) - (3 * 16.0f), 30.0f);

		gfx->DrawSquare(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 160.0f, 80.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquare(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 160.0f, 80.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquare(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 160.0f, 80.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquare(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 160.0f, 80.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquare(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 160.0f, 80.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquare(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 160.0f, 80.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquare(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 160.0f, 80.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		ui_shapes->Draw(SPRITEFRAME_UI_SQUARE_NACTIVE, (SCREEN_WIDTH / 2.0f) - (3 * 16.0f), 30.0f);
	}

	//Rounded Squares
	if (uiMenuLID == 4) {
		ui_shapes->Draw(SPRITEFRAME_UI_RSQUARE_ACTIVE, (SCREEN_WIDTH / 2.0f) - 16.0f, 30.0f);

		gfx->DrawSquareRounded(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 160.0f, 80.0f, 10.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquareRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 160.0f, 80.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquareRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 160.0f, 80.0f, 10.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquareRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 160.0f, 80.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquareRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 160.0f, 80.0f, 10.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquareRounded(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 160.0f, 80.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawSquareRounded(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 160.0f, 80.0f, 10.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		ui_shapes->Draw(SPRITEFRAME_UI_RSQUARE_NACTIVE, (SCREEN_WIDTH / 2.0f) - 16.0f, 30.0f);
	}

	//Rectangles
	if (uiMenuLID == 5) {
		ui_shapes->Draw(SPRITEFRAME_UI_RECT_ACTIVE, (SCREEN_WIDTH / 2.0f) + 16.0f, 30.0f);

		gfx->DrawRect(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 160.0f, 90.0f, 60.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRect(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 160.0f, 90.0f, 60.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRect(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 160.0f, 90.0f, 60.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRect(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 160.0f, 90.0f, 60.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRect(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 160.0f, 90.0f, 60.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRect(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 160.0f, 90.0f, 60.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRect(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 160.0f, 90.0f, 60.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		ui_shapes->Draw(SPRITEFRAME_UI_RECT_NACTIVE, (SCREEN_WIDTH / 2.0f) + 16.0f, 30.0f);
	}

	//Rounded Rectangles
	if (uiMenuLID == 6) {
		ui_shapes->Draw(SPRITEFRAME_UI_RRECT_ACTIVE, (SCREEN_WIDTH / 2.0f) + (3 * 16.0f), 30.0f);

		gfx->DrawRectRounded(ME2D_FILL_NONE, ME2D_OUTLINE_SOLID, 3.0f, 75.0f, 160.0f, 90.0f, 60.0f, 10.0f, 1.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRectRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DOTTED, 3.0f, 185.0f, 160.0f, 90.0f, 60.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRectRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASHED, 3.0f, 295.0f, 160.0f, 90.0f, 60.0f, 10.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRectRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOTTED, 3.0f, 405.0f, 160.0f, 90.0f, 60.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRectRounded(ME2D_FILL_NONE, ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 515.0f, 160.0f, 90.0f, 60.0f, 10.0f, 1.0f, 1.0f, 0.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRectRounded(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 3.0f, 625.0f, 160.0f, 90.0f, 60.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, NULL, NULL, NULL, NULL);
		gfx->DrawRectRounded(ME2D_FILL_SECONDARY, ME2D_OUTLINE_SOLID, 3.0f, 735.0f, 160.0f, 90.0f, 60.0f, 10.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		ui_shapes->Draw(SPRITEFRAME_UI_RRECT_NACTIVE, (SCREEN_WIDTH / 2.0f) + (3 * 16.0f), 30.0f);
	}

	//Lines
	if (uiMenuLID == 7) {
		ui_shapes->Draw(SPRITEFRAME_UI_LINE_ACTIVE, (SCREEN_WIDTH / 2.0f) + (5 * 16.0f), 30.0f);

		gfx->DrawLine(ME2D_OUTLINE_SOLID, 3.0f, 55.0f, 140.0f, 95.0f, 180.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->DrawLine(ME2D_OUTLINE_DOTTED, 3.0f, 165.0f, 140.0f, 205.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f);
		gfx->DrawLine(ME2D_OUTLINE_DASHED, 3.0f, 275.0f, 140.0f, 315.0f, 180.0f, 1.0f, 1.0f, 0.0f, 1.0f);
		gfx->DrawLine(ME2D_OUTLINE_DASH_DOTTED, 3.0f, 385.0f, 140.0f, 425.0f, 180.0f, 0.0f, 1.0f, 1.0f, 1.0f);
		gfx->DrawLine(ME2D_OUTLINE_DASH_DOT_DOTTED, 3.0f, 495.0f, 140.0f, 535.0f, 180.0f, 1.0f, 1.0f, 0.0f, 1.0f);

	}
	else {
		ui_shapes->Draw(SPRITEFRAME_UI_LINE_NACTIVE, (SCREEN_WIDTH / 2.0f) + (5 * 16.0f), 30.0f);
	}
}
