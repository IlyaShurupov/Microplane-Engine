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
#include "Level1.h"


void Level1::Load()
{
	//Load Image spritesheet.png
	sprites = new SpriteSheet(L"Edit/dta/dsprites/spritesheet.png", gfx, 64, 64);
	frame = SPRITEFRAME_PLAYER_RIGHT;

	yPlayerPosition = ySpeed = 0.0f;
	xPlayerPosition = 0.0f;
	cloudPosition = 0.0f;
	cloudPosition2 = 200.0f;
	xWallPosition = 400.0f;
}

void Level1::UnLoad()
{
	delete sprites;
}

void Level1::Update(double timeTotal, double timeDelta)
{
	frame = SPRITEFRAME_PLAYER_RIGHT;
	ySpeed += 1.0f;
	yPlayerPosition += ySpeed;
	if (yPlayerPosition > SCREEN_HEIGHT)
	{
		yPlayerPosition = SCREEN_HEIGHT;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		frame = SPRITEFRAME_PLAYER_LEFT;
		xPlayerPosition -= 50.0f * timeDelta;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		frame = SPRITEFRAME_PLAYER_RIGHT;
		xPlayerPosition += 50.0f * timeDelta;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		frame = SPRITEFRAME_PLAYER_RIGHTFLY;
		if (yPlayerPosition > 10.0f) {
			ySpeed = -2.0f;
			yPlayerPosition += ySpeed;
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

	cloudPosition += 20.0f * timeDelta;
	if (cloudPosition > SCREEN_WIDTH) cloudPosition = -64.0f;

	cloudPosition2 += 30.0f * timeDelta;
	if (cloudPosition2 > SCREEN_WIDTH) cloudPosition2 = -64.0f;
}

void Level1::Render()
{
	gfx->ClearScreen(0.6f, 0.6f, 1.0f);


	sprites->Draw(SPRITEFRAME_CLOUD % 5, cloudPosition, 80);								// Render Cloud

	sprites->Draw(SPRITEFRAME_WALLBROKEN, xWallPosition, SCREEN_HEIGHT - 64 - 52);			// Render Wall
	sprites->Draw(SPRITEFRAME_WALLBROKEN, xWallPosition, SCREEN_HEIGHT - (64 * 2) - 52);	// Render Wall

	sprites->Draw(frame % 4, xPlayerPosition, yPlayerPosition);								// Render Player

	sprites->Draw(SPRITEFRAME_CLOUD, cloudPosition2, 130);									// Render Cloud2

	for (int i = 0; i < ((SCREEN_WIDTH / 64) + 2); i++)										// Render Bottom Ground
	{
		sprites->Draw(SPRITEFRAME_GROUND, SCREEN_WIDTH - (64.0f * i), SCREEN_HEIGHT - 64.0f);
	}
}
