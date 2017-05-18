#include "GameWorld.h"
#include <time.h>

IDirect3DDevice9 *Device;
HWND hwnd;

GameState *currentState, *previousState;
GameState *gameWorld = new GameWorld();

LRESULT CALLBACK D3D::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstances, LPSTR cmdLine, int showCmd) {

	float currentTime = 0, lastTime = 0, deltaTime;

	currentState = gameWorld;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	D3D::InitWindow(hInstance);
	ShowWindow(hwnd, SW_SHOW);

	D3D::InitD3D();


	currentState->Enter();
	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE) && !IsDialogMessage(NULL, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			currentTime = timeGetTime();
			deltaTime = currentTime - lastTime;

			currentState->GameLoop(deltaTime);

			lastTime = currentTime;
			srand(time(NULL));

		}



	}

	Device->Release();

	return msg.wParam;
}