#include <iostream>
#include <Windows.h>
#include <cmath>
#include "Window.h"


Window* window;

//G��wna fukncja
int WINAPI wWinMain(HINSTANCE hInstance,
					HINSTANCE prevInstance,
					LPWSTR cmd,
					int nCmdShow)
{
	//FILE* fp;

	//AllocConsole();
	//freopen_s(&fp, "CONIN$", "r", stdin);
	//freopen_s(&fp, "CONOUT$", "w", stdout);
	//freopen_s(&fp, "CONOUT$", "w", stderr);

	window = new Window();

	HWND mainHandle = window->Create(hInstance, 800, 800);
	ShowWindow(mainHandle, nCmdShow);

	MSG message = { 0 };

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		else {
			window->Update();
			window->Render();
		}
	}

	return 0;
}