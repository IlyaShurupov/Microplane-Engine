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
#include "SplashScreen.h"
#include "LevelList.h"
#include "MEUtils.h"


void SplashScreen::Load()
{
	s_resSplashScreen = new SpriteSheet(L"Edit/splash.png", gfx, 640, 480);
	fadeoutalpha = 1.0f;
}

void SplashScreen::UnLoad()
{
	if (s_resSplashScreen) delete s_resSplashScreen;
}

void SplashScreen::Update(double timeTotal, double timeDelta)
{
	if (fadeoutalpha <= 1.0f && fadeoutalpha > 0.0f) {
		if (fadeoutalpha <= 0.01f) {
			Sleep(2000);
			GameController::SwitchLevel(new MainMenu());
		}
		else {
			fadeoutalpha -= 0.008f;
		}
	}
}

void SplashScreen::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.0f);

	s_resSplashScreen->Draw(0, (SCREEN_WIDTH / 2.0f) - 320.0f, (SCREEN_HEIGHT / 2.0f) - 240.0f);

	gfx->DrawSquare(ME2D_FILL_PRIMARY, ME2D_OUTLINE_SOLID, 1.0f, (SCREEN_WIDTH / 2.0f), (SCREEN_HEIGHT / 2.0f), (SCREEN_WIDTH * 1.0f), 0.0f, 0.0f, 0.0f, fadeoutalpha, NULL, NULL, NULL, NULL);


#ifdef _DEBUG
	gfx->RenderText(MEUTL_DBG_ENGDMSG, (SCREEN_WIDTH - 200), (SCREEN_HEIGHT - 25), 1.0f, 1.0f, 1.0f, 1.0f);
#endif

}
