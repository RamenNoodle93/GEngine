#pragma once
#pragma comment(lib, "d2d1.lib")

#include <Windows.h>
#include <d2d1.h>

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;

public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ResizeScreen(HWND windowHandle);
	void ClearScreen(float r, float g, float b);

	void DrawCircle(float x, float y, float width, float radius, float r, float g, float b, float a);
	void DrawLine(float x1, float y1, float x2, float y2, float width, float r, float g, float b, float a);
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float width, float r, float g, float b, float a);
};
