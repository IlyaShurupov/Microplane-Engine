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

//Windows Header Files
#include <Windows.h>
#include <windowsx.h>


#define MEDEF_ENG_ENGNAME "Microplane Engine"           // Engine Name
#define MEDEF_ENG_ENGABBV "ME2D"                        // Engine Name Abbreviation
#define MEDEF_ENG_ENGVERD "1.1"                         // Engine Version
#define MEDEF_ENG_ENGVERS "build 20180928"              // Engine Build/Secondary Version
#define MEDEF_ENG_ENGDEVN "Ivan Kmeťo"                  // Engine Developer Name

#define SCREEN_WIDTH GetPrivateProfileInt("GlobalSettings", "ScreenWidth", 800, ".\\settings.ini")
#define SCREEN_HEIGHT GetPrivateProfileInt("GlobalSettings", "ScreenHeight", 600, ".\\settings.ini")
