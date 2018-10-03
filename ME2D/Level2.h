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

#include "GameLevel.h"

//LEVEL 2 - D2D OBJECTS DEMO SCENE

class Level2 : public GameLevel
{
	SpriteSheet* ui_shapes;

	uint8_t uiMenuLID;
	#define UI_MENULIST_MAX 7
	#define UI_MENULIST_MIN 1

	#define SPRITEFRAME_UI_SQUARE_NACTIVE 0
	#define SPRITEFRAME_UI_RSQUARE_NACTIVE 1
	#define SPRITEFRAME_UI_RECT_NACTIVE 2
	#define SPRITEFRAME_UI_RRECT_NACTIVE 3
	#define SPRITEFRAME_UI_CIRCLE_NACTIVE 4
	#define SPRITEFRAME_UI_ELLIPSE_NACTIVE 5
	#define SPRITEFRAME_UI_LINE_NACTIVE 6
	#define SPRITEFRAME_UI_SQUARE_ACTIVE 7
	#define SPRITEFRAME_UI_RSQUARE_ACTIVE 8
	#define SPRITEFRAME_UI_RECT_ACTIVE 9
	#define SPRITEFRAME_UI_RRECT_ACTIVE 10
	#define SPRITEFRAME_UI_CIRCLE_ACTIVE 11
	#define SPRITEFRAME_UI_ELLIPSE_ACTIVE 12
	#define SPRITEFRAME_UI_LINE_ACTIVE 13

public:
	void Load() override;
	void UnLoad() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
};
