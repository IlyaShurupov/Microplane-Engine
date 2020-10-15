//============================================================================
// Microplane Engine - ME2D
//
// Scene: ME2D Main Menu
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
#include "MainMenu.h"
#include "LevelList.hpp"
#include "CoreModule.hpp"


void MainMenu::Load()
{
	menuLID = 1;
}

void MainMenu::UnLoad()
{
}

void MainMenu::Update(double timeTotal, double timeDelta)
{
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		if (menuLID == MENULIST_MAX) {
			menuLID = MENULIST_MAX;
		}
		else {
			menuLID += 1;
		}
	}

	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		if (menuLID == MENULIST_MIN) {
			menuLID = MENULIST_MIN;
		}
		else {
			menuLID -= 1;
		}
	}


	if (GetAsyncKeyState(VK_RETURN)) {
		if (menuLID == 1) {
			GameController::SwitchLevel(new Level1());
		}

		if (menuLID == 2) {
			GameController::SwitchLevel(new Level2());
		}
	}

	//Mouse
	if (gfx->mousePosX > 5 &&gfx->mousePosX < 205)
	{
		if (gfx->mousePosY > 15 && gfx->mousePosY < 55)
		{
			menuLID = 1;
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				GameController::SwitchLevel(new Level1());
			}
		}
	}

	if (gfx->mousePosX > 5 && gfx->mousePosX < 205)
	{
		if (gfx->mousePosY > 75 && gfx->mousePosY < 115)
		{
			menuLID = 2;
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				GameController::SwitchLevel(new Level2());
			}
		}
	}
}

void MainMenu::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	

	if (menuLID == 1) {
		gfx->RenderTextMenu(L"Level 1", 20, 20, 1.0f, 0.0f, 0.0f, 1.0f);
		gfx->RenderText(L"Basic level for testing purposes", 20, 45, 1.0f, 1.0f, 1.0f, 0.8f);
	}
	else {
		gfx->RenderTextMenu(L"Level 1", 20, 20, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->RenderText(L"Basic level for testing purposes", 20, 45, 1.0f, 1.0f, 1.0f, 0.2f);
	}

	if (menuLID == 2) {
		gfx->RenderTextMenu(L"Level 2", 20, 80, 1.0f, 0.0f, 0.0f, 1.0f);
		gfx->RenderText(L"Presentation of basic geometries", 20, 105, 1.0f, 1.0f, 1.0f, 0.8f);
	}
	else {
		gfx->RenderTextMenu(L"Level 2", 20, 80, 1.0f, 1.0f, 1.0f, 1.0f);
		gfx->RenderText(L"Presentation of basic geometries", 20, 105, 1.0f, 1.0f, 1.0f, 0.2f);
	}


#ifdef _DEBUG
	gfx->RenderText(ME_STRING_DEBUG_VERSION, (float)(SCREEN_WIDTH - 200), (float)(SCREEN_HEIGHT - 25), 1.0f, 1.0f, 1.0f, 1.0f);
#endif

}
