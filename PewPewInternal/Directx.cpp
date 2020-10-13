#include "pch.h"

int windowHeight, windowWidth;

//
bool GetD3D9Device(void** pTable, size_t size)
{

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	IDirect3DDevice9* pTempDevice = nullptr;

	D3DPRESENT_PARAMETERS pParams = {};

	pParams.Windowed = false;
	pParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pParams.hDeviceWindow = GetProcessWindow();

	HRESULT result = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, pParams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pParams, &pTempDevice);
	if(result != S_OK)
	{
		pParams.Windowed = !pParams.Windowed;

		result = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, pParams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pParams, &pTempDevice);
		if(result != S_OK)
		{
			pD3D->Release();
			return FALSE;
		}
	}

	memcpy(pTable, *(void***)pTempDevice, size);

	pTempDevice->Release();
	pD3D->Release();

	return TRUE;
}

//
BOOL CALLBACK enumWind(HWND handle, LPARAM lp)
{
	DWORD procId;
	GetWindowThreadProcessId(handle, &procId);
	
	if(GetCurrentProcessId() != procId)
		return TRUE;

	Window = handle;
	
	return FALSE;
}

//
HWND GetProcessWindow()
{
	Window = nullptr;
	RECT size;
	
	EnumWindows(enumWind, NULL);

	GetWindowRect(Window, &size);

	windowWidth  = size.right  - size.left;
	windowHeight = size.bottom - size.top;

	return Window;
}

//
void InitImGui(IDirect3DDevice9* pDevice)
{
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImFont* defaulFont =  io.Fonts->AddFontFromFileTTF(("c:\\Windows\\Fonts\\Arial.ttf"), 15.0f);
	
	D3DDEVICE_CREATION_PARAMETERS cp;
	pDevice->GetCreationParameters(&cp);
	
    ImGui_ImplWin32_Init(cp.hFocusWindow);
    ImGui_ImplDX9_Init(pDevice);
}