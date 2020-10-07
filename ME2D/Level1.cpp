//============================================================================
// Microplane Engine - ME2D
//
// Scene: Level 1 - Platformer
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
#include "LevelList.hpp"
#include "Graphics.h"
#include "Level1.h"


void Level1::Load()
{
	//Load Bitmap Atlas (SpriteSheet)
	s_sprites = new SpriteSheet(L"Edit/dta/dsprites/bmatlas.png", gfx, 64, 64);
	s_starAnim = new SpriteSheet(L"Edit/dta/dsprites/bmstaranim.png", gfx, 64, 64);
	frame = SPRITEFRAME_PLAYER_RIGHT;
	framestaranim = SPRITEFRAME_STARINIT;

	yPlayerPosition = ySpeed = 0.0f;
	xPlayerPosition = (SCREEN_WIDTH/2) - 32.0f;
}

void Level1::UnLoad()
{
	if (s_starAnim) delete s_starAnim;
	if (s_sprites) delete s_sprites;
}

void Level1::Update(double timeTotal, double timeDelta)
{
	frame = SPRITEFRAME_PLAYER_RIGHT;
	ySpeed += 1.0f;
	yPlayerPosition += ySpeed;
	if (yPlayerPosition > SCREEN_HEIGHT)
	{
		yPlayerPosition = (float)SCREEN_HEIGHT;
	}


	if (GetAsyncKeyState(VK_ESCAPE)) {
		GameController::SwitchLevel(new MainMenu());
	}

	if (GetAsyncKeyState(VK_LEFT)) {
		frame = SPRITEFRAME_PLAYER_LEFT;
		xPlayerPosition -= 80.0f * timeDelta;
	}

	if (GetAsyncKeyState(VK_RIGHT)) {
		frame = SPRITEFRAME_PLAYER_RIGHT;
		xPlayerPosition += 80.0f * timeDelta;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		frame = SPRITEFRAME_PLAYER_RIGHTFLY;
		if (yPlayerPosition > 10.0f) {
			ySpeed = -3.0f;
			yPlayerPosition += ySpeed * timeDelta;
		}
		if (yPlayerPosition < 10.0f) {
			ySpeed += 1.0f * timeDelta;
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			frame = SPRITEFRAME_PLAYER_LEFTFLY;
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			frame = SPRITEFRAME_PLAYER_RIGHTFLY;
		}
	}

	if (xPlayerPosition > (SCREEN_WIDTH - 64.0f)) xPlayerPosition = (SCREEN_WIDTH - 64.0f);
	if (yPlayerPosition > (SCREEN_HEIGHT - 64.0f - 52.0f)) yPlayerPosition = (SCREEN_HEIGHT - 64.0f - 52.0f);
	if (xPlayerPosition < 0) xPlayerPosition = 0.0f;

	framestaranim++;
}

void Level1::Render()
{
	gfx->ClearScreen(0.286f, 0.302f, 0.494f);

	s_sprites->Draw(SPRITEFRAME_PLANET % 5, (SCREEN_WIDTH - 200.0f), 50.0f);                // Render Planet
	s_starAnim->Draw((framestaranim / 10) % 5, 125.0f, 75.0f);                              // Render First Star
	s_starAnim->Draw((framestaranim / 10) % 5, (SCREEN_WIDTH - 300.0f), 150.0f);            // Render Second Star

	s_sprites->Draw(frame % 4, (float)xPlayerPosition, (float)yPlayerPosition);             // Render Player

	for (int i = 0; i < (((int)SCREEN_WIDTH / 64) + 2); i++)                                // Render Bottom Ground
	{
		s_sprites->Draw(SPRITEFRAME_GROUND, SCREEN_WIDTH - (64.0f * i), SCREEN_HEIGHT - 64.0f);
	}

	gfx->RenderText(L"Movement Controls: ARROW KEYS + SPACE", 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
}
