

#include "main.h"
#include "manager.h"
#include "input.h"
#include "dropFile.h"
#include "imgui_impl_dx11.h"
#include "imguiManager.h"
#include <thread>


const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "DX11�Q�[��";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


HWND g_Window;

HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	WNDCLASSEX wcex;
	{
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = 0;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = nullptr;

		RegisterClassEx(&wcex);


		RECT rc = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		g_Window = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
	}

	//�O������̃t�@�C�����󂯓����
	DragAcceptFiles(g_Window, TRUE);

	Manager::Init();


	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);




	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;



	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				Manager::Update();
				Manager::Draw();
			}
		}
	}

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::Uninit();

	return (int)msg.wParam;
}

#ifdef _DEBUG
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif // _DEBUG


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
	// �����̏��������s����
	if(ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
#endif // _DEBUG


	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_MOUSEWHEEL:
	{
		// �}�E�X�z�C�[���̏����擾
		short delta = GET_WHEEL_DELTA_WPARAM(wParam);
		Input::SetMouseRot(delta);
		break;
	}
	case WM_SIZE:
#ifdef _DEBUG


		// ��ʃT�C�Y���ύX���ꂽ�ꍇ�Ag_isWindowSizeChanged��true�ɐݒ�
		float newWidth;  // �V�����E�B���h�E�̕�
		newWidth = static_cast<float>(LOWORD(lParam));  // �V�����E�B���h�E�̕�
		float newHeight; // �V�����E�B���h�E�̍���
		newHeight = static_cast<float>(HIWORD(lParam)); // �V�����E�B���h�E�̍���
		ImguiManager::SetWindowSize(Vector2(newWidth, newHeight));
#endif // _DEBUG
		break;
	case WM_DROPFILES:
#ifdef _DEBUG
		HDROP hdrop;
		hdrop = (HDROP)wParam;

		DropFile::SetDrop(hdrop);
		DropFile::DropFileData();

		DragFinish(hdrop);
		break;
#endif // _DEBUG
	default:
		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

