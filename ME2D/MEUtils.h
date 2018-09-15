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

#include "stdafx.h"
#include "Logger.h"


static const std::string s_debugMsg = std::string(MEDEF_ENG_ENGABBV) + " " + std::string(MEDEF_ENG_ENGVERD) + " (" + std::string(MEDEF_ENG_ENGVERS) + ") (Debug)";
static std::wstring MEUTL_DBG_ENGDMSG(s_debugMsg.begin(), s_debugMsg.end());


static void ASSERT_ME2D(HRESULT value, std::string description, std::string msgboxTitle) {
	MessageBox(nullptr, description.c_str(), msgboxTitle.c_str(), MB_OK | MB_ICONERROR);
	Log_Open("debug.log");
	Error(value);
	Log_Write(description + "\n");
	Log_Close();
}

static void ASSERT_ME2D_AUTO(HRESULT value, std::string description, std::string msgboxTitle) {
	if (value != S_OK) {
		ASSERT_ME2D(value, description, msgboxTitle);
	}
}
