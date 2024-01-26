#include "Window.h"

Graphics* graphics;
Game* game;
std::vector<Node> finally;

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
	Mat4x4 proj = game->GetProj();

	std::vector<Node> nodes, filled;

	game->rotationX += 0.01f;
	game->rotationZ += 0.003f;
	game->rotationY += 0.02f;

	for (auto& node : nodes)
	{
		Node projectedNode, rotatedNodeX, rotatedNodeY, rotatedNodeZ, translatedNode;

		Mat4x4 rotx = game->GetRotX();
		Mat4x4 roty = game->GetRotY();
		Mat4x4 rotz = game->GetRotZ();

		Tools::MultiplyMatrixVector(node, rotatedNodeX, rotx);
		Tools::MultiplyMatrixVector(rotatedNodeX, rotatedNodeY, roty);
		Tools::MultiplyMatrixVector(rotatedNodeY, rotatedNodeZ, rotz);

		translatedNode = rotatedNodeZ;

		translatedNode.z += 5.0f;

		Tools::MultiplyMatrixVector(translatedNode, projectedNode, proj);

		projectedNode.x *= 200;
		projectedNode.y *= 200;

		projectedNode.x += 400.0f;
		projectedNode.y += 400.0f;

		filled.push_back(projectedNode);

	}
	finally = filled;
}

void Window::Render()
{
	graphics->BeginDraw();
	graphics->ClearScreen(0.0f, 0.0f, 0.0f);

	for (auto& node : finally)
	{
		graphics->DrawCircle(node.x, node.y, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	}

	graphics->EndDraw();
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd,
									UINT uMsg,
									WPARAM wParam,
									LPARAM lParam)
{

	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	/*
	if (uMsg == WM_PAINT)
	{
		graphics->BeginDraw();
		graphics->ClearScreen(0.0, 0.0, 0.0);

		Mat4x4 proj = game->GetProj();

		std::vector<Node> nodes;

		float arr[8][3] = {
		{
			-1, -1, -1
		},
		{
			-1, -1, 1
		},
		{
			-1, 1, -1
		},
		{
			-1, 1, 1
		},
		{
			1, -1, -1
		},
		{
			1, -1, 1
		},
		{
			1, 1, -1
		},
		{
			1, 1, 1
		}
		};

		for (int i = 0; i < 8; i++) {
			Node thing;
			thing.x = arr[i][0];
			thing.y = arr[i][1];
			thing.z = arr[i][2];

			nodes.push_back(thing);
		}

		FILE* fp;

		AllocConsole();
		freopen_s(&fp, "CONIN$", "r", stdin);
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONOUT$", "w", stderr);

		game->rotationX += 0.1f;
		game->rotationZ += 0.1f;
		for (auto& node : nodes)
		{
			Node projectedNode, rotatedNode, translatedNode;

			Mat4x4 rotx = game->GetRotX();
			Mat4x4 roty = game->GetRotY();
			Mat4x4 rotz = game->GetRotZ();

			Tools::MultiplyMatrixVector(node, rotatedNode, rotx);
			Tools::MultiplyMatrixVector(rotatedNode, rotatedNode, roty);
			Tools::MultiplyMatrixVector(rotatedNode, rotatedNode, rotz);

			translatedNode = rotatedNode;

			translatedNode.z += 3.0f;

			Tools::MultiplyMatrixVector(translatedNode, projectedNode, proj);

			projectedNode.x *= 200;
			projectedNode.y *= 200;

			projectedNode.x += 400.0f;
			projectedNode.y += 400.0f;

			std::cout << node.x << " " << node.y << " " << projectedNode.x << " " << projectedNode.y << "\n";

			graphics->DrawCircle(projectedNode.x, projectedNode.y, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		}

		graphics->EndDraw();
	}
	*/

	return DefWindowProc(hwnd,
						 uMsg,
						 wParam,
						 lParam);
}