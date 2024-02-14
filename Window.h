#pragma once

#include <Windows.h>
#include <iostream>
#include "Graphics.h"
#include "Tools.h"
#include "Types.h"
#include "Game.h"

class Window
{
private:
	HWND hWnd;
	std::vector<Point> renderStack;

public:
	Window();
	~Window();

	void Update();
	void Render();

	HWND Create(HINSTANCE hInstance, int width, int height);

	static LRESULT CALLBACK WindowProc(HWND hwnd,
									   UINT uMsg,
									   WPARAM wParam,
									   LPARAM lParam);
};

