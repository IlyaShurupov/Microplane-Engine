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

#include "GameLevel.hpp"

//LEVEL 1 - DEMO SCENE

class Level1 : public GameLevel
{
	double ySpeed;

	double xPlayerPosition;
	double yPlayerPosition;

	SpriteSheet* s_sprites;
	SpriteSheet* s_starAnim;

	int frame;
	int framestaranim;

	#define SPRITEFRAME_PLAYER_LEFT 0
	#define SPRITEFRAME_PLAYER_LEFTFLY 1
	#define SPRITEFRAME_PLAYER_RIGHT 2
	#define SPRITEFRAME_PLAYER_RIGHTFLY 3
	#define SPRITEFRAME_PLANET 4
	#define SPRITEFRAME_EMPTY 5
	#define SPRITEFRAME_GROUND 6
	#define SPRITEFRAME_STARINIT 0

public:
	void Load() override;
	void UnLoad() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
};
