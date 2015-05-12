#include <Windows.h>
#include <iostream>

#include "SystemManager.h"

LRESULT CALLBACK proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
		break;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS windowClass;
	HWND windowHandle;
	HINSTANCE instance = NULL;
	int pixelformat;

	windowClass.style = CS_OWNDC;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = L"Window";
	windowClass.lpfnWndProc = proc;


	if (!RegisterClass(&windowClass))
		printf("error: %d\r\n", GetLastError());

	windowHandle = CreateWindowEx(
		WS_EX_APPWINDOW,
		L"Window",
		L"TEST",
		WS_OVERLAPPED | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		(HWND)NULL,
		(HMENU)NULL,
		NULL, NULL);

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	if (!windowHandle)
	{
		//error here
		return 0;
	}


	ShowWindow(windowHandle, true);

	//OpenGL context creation
	HDC hdc = GetDC(windowHandle);
	HGLRC hglrc;

	pixelformat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelformat, &pfd);
	hglrc = wglCreateContext(hdc);
	wglMakeCurrent(GetDC(windowHandle), hglrc);


	//Game stuff
	GameObject* object1 = new GameObject();
	GameObject* object2 = new GameObject();
	GameObject* object3 = new GameObject();

	PhysicsComponent* phys= new PhysicsComponent(glm::vec2());
	std::vector<unsigned char> ImageData;
	unsigned int Width, Height;
	unsigned error = lodepng::decode(ImageData, Width, Height, "Test.png");
	RenderComponent* render = new RenderComponent(ImageData, Width, Height);
	object1->AddComponent(phys);
	object1->AddComponent(render);

	SystemManager manager;
	manager.InitGraphics();

	manager.AddObject(object1);
	//manager.AddObject(object2);
	//manager.AddObject(object3);
	
	for (;;)
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		manager.Update();
		SwapBuffers(hdc);
	}
	//OpenGL context destroy
	wglMakeCurrent(GetDC(windowHandle), NULL);
	wglDeleteContext(hglrc);

	return 0;
}