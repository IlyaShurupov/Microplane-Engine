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

#include <Windows.h>

class HPTimer
{
	long long startTime;					// Last time we reset time
	long long lastCallToUpdate;				// Previous timestamp Call To Update
	long long currentCallToUpdate;			// Current timestamp Call To Update
	long long frequency;					// Number of tick per second for this High Precision Timer (HPTimer)

public:
	HPTimer() {
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);
		frequency = t.QuadPart;				// QuadPart is converting integer into long long

		Reset();
	}

	//Set the current time
	void Reset() {
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);
		startTime = t.QuadPart;
		currentCallToUpdate = t.QuadPart;
		lastCallToUpdate = t.QuadPart;
	}

	void Update() {
		lastCallToUpdate = currentCallToUpdate;
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		currentCallToUpdate = t.QuadPart;
	}

	//Time since Reset() was called
	double GetTimeTotal() {
		double d = (double)currentCallToUpdate - (double)startTime;
		return d / frequency;				// Return conversion to seconds
	}

	//Difference between two calls of Update (time between frames)
	double GetTimeDelta() {
		double d = (double)currentCallToUpdate - (double)lastCallToUpdate;
		return d / frequency;				// Return conversion to seconds
	}
};
