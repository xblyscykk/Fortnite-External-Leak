#include <Windows.h>
#include <string>
#include <dwmapi.h>
#include <d3d9.h>
#include <tchar.h>
#include "Overlay.h"
#include <map>
#include "../ImGui/imgui_impl_dx9.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGuiRender/ImGuiRender.h"
#include "../menu/menu.h"

#include "../HyperV/Utils.h"

#include <Windows.h>
#include <string>
#include <random>
#include <stdint.h>

#pragma comment( lib, "dwmapi.lib" )
#pragma comment( lib, "D3d9.lib" )


LPDIRECT3D9              g_pD3D = NULL;
LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
D3DPRESENT_PARAMETERS    g_d3dpp = {};

COverlay::COverlay(void)
{

}

#define silent_fail(x) MessageBoxA(NULL, x, NULL, NULL); exit(0);

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool COverlay::InitWindows(HWND GameHwnd)
{
	if (GameHwnd == 0)
	{

		silent_fail("ERR: 0x1000000")
		return false;

	}

	static std::wstring strOverlayClass = GetRandomString(10);
	static std::wstring strOverlayTitle = GetRandomString(10);

	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),
		0,
		&COverlay::WndProc,
		0,
		0,
		nullptr,
		NULL,
		NULL,
		0,
		0,
		strOverlayClass.c_str(),
		LoadIcon(0, IDI_APPLICATION)
	};

	if (!RegisterClassEx(&wc))
	{
		silent_fail("ERR: 0x2000000");
		return false;
	}

	POINT Cord{};
	RECT GameRect{};
	if (!GetClientRect(GameHwnd, &GameRect))
	{
		silent_fail("ERR: 0x3000000");
		return false;
	}

	if (!ClientToScreen(GameHwnd, &Cord))
	{
		silent_fail("ERR: 0x4000000");
		return false;
	}

	GameRect.left = Cord.x;
	GameRect.top = Cord.y;
	m_pWidth = static_cast<float>(GameRect.right);
	m_pHeight = static_cast<float>(GameRect.bottom);
	m_hWndOverlay = CreateWindowExW(0, strOverlayClass.c_str(), strOverlayTitle.c_str(), WS_POPUP | WS_VISIBLE, static_cast<int>(GameRect.left - 3.f), static_cast<int>(GameRect.top - 3.f), static_cast<int>(m_pWidth + 3.f), static_cast<int>(m_pHeight + 3.f), 0, NULL, NULL, NULL);
	if (!m_hWndOverlay)
		return false;

	static MARGINS DWMMargins = { static_cast<int>(GameRect.left - 3.f), static_cast<int>(GameRect.top - 3.f), static_cast<int>(m_pWidth + 3.f), static_cast<int>(m_pHeight + 3.f) };
	if (FAILED(DwmExtendFrameIntoClientArea(m_hWndOverlay, &DWMMargins)))
	{
		silent_fail("ERR: 0x5000000");
		return false;
	}

	ShowWindow(m_hWndOverlay, SW_SHOW);
	if (!UpdateWindow(m_hWndOverlay))
	{
		silent_fail("ERR: 0x6000000");
		return false;
	}

	if (!CreateDeviceD3D(m_hWndOverlay))
	{
		silent_fail("ERR: 0x7000000");
		return false;
	}

	//SetWindowLong(m_hWndOverlay, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(m_hWndOverlay);
	ImGui_ImplDX9_Init(g_pd3dDevice);
	CMenu::Get().Initialize();
	ImRenderer->Initialize();

	//if (*(ULONG*)(0x7FFE0260) >= 19041)
	//	SetWindowDisplayAffinity(m_hWndOverlay, 0x00000011);

	return true;
}

bool COverlay::CreateDeviceD3D(HWND hWnd)
{
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;

	return true;
}

void COverlay::CleanupDeviceD3D()
{
	if (g_pd3dDevice) 
	{ 
		g_pd3dDevice->Release(); 
		g_pd3dDevice = NULL; 
	}
	if (g_pD3D)
	{ 
		g_pD3D->Release(); 
		g_pD3D = NULL; 
	}
}

LRESULT CALLBACK COverlay::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ImGui_ImplDX9_InvalidateDeviceObjects();
			g_pd3dDevice->Reset(&g_d3dpp);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}
