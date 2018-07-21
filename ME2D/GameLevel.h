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

#include "Graphics.h"
#include "Spritesheet.h"

class GameLevel
{
protected:
	static Graphics* gfx;

public:
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void UnLoad() = 0;
	virtual void Render() = 0;
	virtual void Update(double timeTotal, double timeDelta) = 0;
};