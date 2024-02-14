#include <iostream>
#include <Windows.h>
#include <cmath>
#include "Window.h"


Window* window;

//G³ówna fukncja
int WINAPI wWinMain(HINSTANCE hInstance,
					HINSTANCE prevInstance,
					LPWSTR cmd,
					int nCmdShow)
{



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