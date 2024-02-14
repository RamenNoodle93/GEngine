#include "Window.h"

Graphics* graphics;
Game* game;

Window::Window()
{
	hWnd = NULL;
}

Window::~Window()
{

}

HWND Window::Create(HINSTANCE hInstance, int width, int height)
{
	graphics = new Graphics();
	game = new Game(1.0f);

	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = &WindowProc;
	windowclass.lpszClassName = L"MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&windowclass);

	RECT rect = { 0, 0, width, height }; //Wymiary okna
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME;

	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"MyGame", windowStyle, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);


	graphics->Init(windowhandle);

	return windowhandle;
}

void Window::Update()
{
	renderStack = game->Update();
}

void Window::Render()
{
	graphics->BeginDraw();
	graphics->ClearScreen(0.0f, 0.0f, 0.0f);

	for (auto& tri : renderStack)
	{
		graphics->DrawLine(tri.p[0].x, tri.p[0].y, tri.p[1].x, tri.p[1].y, 1, 1.0f, 1.0f, 1.0f, 1.0f);
		graphics->DrawLine(tri.p[1].x, tri.p[1].y, tri.p[2].x, tri.p[2].y, 1, 1.0f, 1.0f, 1.0f, 1.0f);
		graphics->DrawLine(tri.p[2].x, tri.p[2].y, tri.p[0].x, tri.p[0].y, 1, 1.0f, 1.0f, 1.0f, 1.0f);
	}

	graphics->EndDraw();
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd,
									UINT uMsg,
									WPARAM wParam,
									LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hwnd,
								 uMsg,
								 wParam,
								 lParam);
	}
}