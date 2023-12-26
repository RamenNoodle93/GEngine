#include <Windows.h>
#include "Graphics.h"
#include "Mesh.h"
#include <iostream>
Graphics* graphics;
Mesh* mesh;

float points[2][2] = { {400, 400}, {500, 500} };

std::vector<Node> nodes;
std::vector<Edge> edges;

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	if (uMsg == WM_SIZE)
	{
		graphics->ResizeScreen(hwnd);
	}

	if (uMsg == WM_PAINT)
	{
		graphics->BeginDraw();

		graphics->ClearScreen(0.0f, 0.0f, 0.2f);

		for (Node point : nodes)
		{
			graphics->DrawCircle(point.x, point.y, 1, 3, 1.0f, 0.0f, 0.0f, 1.0);
		}

		graphics->EndDraw();
	}

	return DefWindowProc(hwnd,
						 uMsg,
						 wParam,
						 lParam);
}

//G³ówna fukncja
int WINAPI wWinMain(HINSTANCE hInstance,
					HINSTANCE prevInstance,
					LPWSTR cmd,
					int nCmdShow)
{
	//Tworzenie okna
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = L"MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowclass);

	RECT rect = { 0, 0, 800, 800 }; //Wymiary okna
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME;

	//Tworzenie identyfikatora obiektu okna
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"MyGame", windowStyle, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	//Jeœli dojdzie do b³êdu, zakoñcz program
	if (!windowhandle) return -1;

	//Tworzenie obiektu graphics, koñczenie programu w wypadku b³edu
	graphics = new Graphics();

	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}

	//Wyœwlietlanie okna
	ShowWindow(windowhandle, nCmdShow);

	for (int i = 0; i < 5; i++) {
		Node node;
		node.x = i * 50;
		node.y = 400;
		node.z = 0;
		nodes.push_back(node);
	}


	FILE* fp;

	AllocConsole();
	freopen_s(&fp, "CONIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);

	mesh = new Mesh(nodes, edges);


	//G³ówna pêtla
	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		DispatchMessage(&message);
	}

	return 0;
}