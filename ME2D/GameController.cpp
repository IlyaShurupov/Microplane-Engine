//============================================================================
// Microplane Engine - ME2D
//
// Game Controller
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

GameLevel* GameController::currentLevel;
bool GameController::Loading;

HPTimer* GameController::hpTimer;


void GameController::Init()
{
	Loading = true;
	currentLevel = 0;

	hpTimer = new HPTimer();
}

void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true;

	currentLevel = lev;
	currentLevel->Load();

	Loading = false;
}

void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;
	currentLevel->UnLoad();
	lev->Load();
	delete currentLevel;
	currentLevel = lev;
	Loading = false;
}

void GameController::Render()
{
	if (Loading) return;
	currentLevel->Render();
}

void GameController::Update()
{
	if (Loading) return;

	hpTimer->Update();
	currentLevel->Update(hpTimer->GetTimeTotal(), hpTimer->GetTimeDelta());
}

void GameController::UnLoad()
{
	Loading = true;
	currentLevel->UnLoad();
	delete currentLevel;
	delete hpTimer;
	Loading = false;
}
