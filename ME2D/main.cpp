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

#include "appconfig.hpp"
#include "CoreModule.hpp"

#include "Graphics.hpp"
#include "GameController.h"
#include "LevelList.hpp"

Graphics* graphics;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }

	getMousePosX = GET_X_LPARAM(lParam);
	getMousePosY = GET_Y_LPARAM(lParam);

	return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	logutil::file_clear("debug.log");
	logutil::write_to_file(str_logEngineInfo, "debug.log");

	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));

	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	windowclass.hIcon = (HICON)LoadImage(NULL, MEDEF_RES_WINICON, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

	RegisterClassEx(&windowclass);

	RECT rect = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", MEDEF_RES_WINTITL, WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	if (!windowhandle) return -1;

	//GRAPHICS INITIALIZATION
	graphics = new Graphics();

	if (!graphics->Init(windowhandle)) {
		delete graphics;
		return -1;
	}


	GameLevel::Init(graphics);

	ShowWindow(windowhandle, nCmdShow);

	GameController::Init();

	GameController::LoadInitialLevel(new SplashScreen()); // Load Initial Level

	//PEEKMESSAGE LOOP
	MSG message;
	message.message = WM_NULL;

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&message);
		else
		{
			graphics->mousePosX = getMousePosX;
			graphics->mousePosY = getMousePosY;

			GameController::Update();
			graphics->BeginDraw();

			GameController::Render();
			graphics->EndDraw();
		}
	}
	//PEEK MESSAGE LOOP END

	GameController::UnLoad();

	if(graphics) delete graphics;


	return 0;
}
