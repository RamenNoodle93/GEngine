#include "Window.h"

Graphics* graphics;
Game* game;

Window::Window()
{
	hWnd = NULL;

	object2d trifirst;

	trifirst.points.push_back(Point{ -0.5, -0.5 });
	trifirst.points.push_back(Point{ 0.5, -0.5 });
	trifirst.points.push_back(Point{ 0.0, 0.5 });

	trifirst.vertices.resize(3);

	trifirst.posData = { Point{0,0.5}, 0 };

	object2d trisecond;

	trisecond.points.push_back(Point{ -0.5, -0.5 });
	trisecond.points.push_back(Point{ 0.5, -0.5 });
	trisecond.points.push_back(Point{ 0.0, 0.5 });

	trisecond.vertices.resize(3);

	trisecond.posData = { Point{2,0}, 0 };

	objects.push_back(trifirst);
	objects.push_back(trisecond);

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

	objects[0].posData.position.x += 0.01;

	for (auto& obj : objects)
	{
		for (int i = 0; i < obj.points.size(); i++)
		{
			obj.vertices[i] = { obj.points[i].x + obj.posData.position.x, obj.points[i].y + obj.posData.position.y };
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects.size(); j++)
		{
			if (j != i)
				if (Tools::SATcollision(objects[i], objects[j]))
					graphics->DrawLine(0, 400, 800, 400, 3, 0, 1, 0, 1);
		}
		graphics->DrawTriangle((objects[i].vertices[0].x) * 50 + 400, (objects[i].vertices[0].y) * 50 + 400, (objects[i].vertices[1].x) * 50 + 400, (objects[i].vertices[1].y) * 50 + 400, (objects[i].vertices[2].x) * 50 + 400, (objects[i].vertices[2].y) * 50 + 400, 2, 1.0, 0.0, 0.0, 1.0);
	}

	//for (auto& object : objects)
	//{
	//	graphics->DrawTriangle((object.vertices[0].x + object.posData.position.x) * 50 + 400, (object.vertices[0].y + object.posData.position.y) * 50 + 400, (object.vertices[1].x + object.posData.position.x) * 50 + 400, (object.vertices[1].y + object.posData.position.y) * 50 + 400, (object.vertices[2].x + object.posData.position.x) * 50 + 400, (object.vertices[2].y + object.posData.position.y) * 50 + 400, 2, 1.0, 0.0, 0.0, 1.0);
	//}

	//for (auto& tri : renderStack)
	//{
	//	graphics->DrawLine(tri.p[0].x, tri.p[0].y, tri.p[1].x, tri.p[1].y, 1, 1.0f, 1.0f, 1.0f, 1.0f);
	//	graphics->DrawLine(tri.p[1].x, tri.p[1].y, tri.p[2].x, tri.p[2].y, 1, 1.0f, 1.0f, 1.0f, 1.0f);
	//	graphics->DrawLine(tri.p[2].x, tri.p[2].y, tri.p[0].x, tri.p[0].y, 1, 1.0f, 1.0f, 1.0f, 1.0f);
	//}

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