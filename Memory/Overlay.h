#pragma once

#include <d3d9.h>
#include "../ImGui/imgui_impl_win32.h"

class COverlay
{
public:
	COverlay();
	bool InitWindows(HWND GameHwnd);
	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	
	HWND GetLocalHwnd(void)
	{
		return m_hWndOverlay;
	}
	float m_pWidth;
	float m_pHeight;
private:
	static LRESULT CALLBACK	WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND m_hWndOverlay;
};

extern LPDIRECT3D9              g_pD3D;
extern LPDIRECT3DDEVICE9        g_pd3dDevice;
extern D3DPRESENT_PARAMETERS    g_d3dpp;