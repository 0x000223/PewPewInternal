#include <MinHook.h>

#include "pch.h"

tEndScene oEndScene = nullptr;

extern LPDIRECT3DDEVICE9 g_pDevice = nullptr;

bool hasInit = false;

//
void __stdcall hkEndScene(LPDIRECT3DDEVICE9 o_pDevice)
{
	if(!g_pDevice)
		g_pDevice = o_pDevice;

	if(!hasInit)
	{
		InitImGui(o_pDevice);
		hasInit = true;
	}
	
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

	Render::Menu();

	Render::Meme();

	ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	
	// Call original
	oEndScene(g_pDevice);
}

//
DWORD __stdcall PewPewThread(HMODULE hModule)
{
	void* d3d9Device[119];
	
	// hook
	if(GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
	{
		auto status = MH_Initialize();
		
		status = MH_CreateHook(d3d9Device[42], &hkEndScene, reinterpret_cast<LPVOID*>(&oEndScene));

		status = MH_EnableHook(d3d9Device[42]);
	}

	Meme::Init();
	
	while(!GetAsyncKeyState(VK_INSERT))
	{
		Meme::Update();
	}

	// Unhook
	MH_DisableHook(d3d9Device[42]);
	MH_Uninitialize();

	// Unload module
	FreeLibraryAndExitThread(hModule, 0);
}

//
BOOL __stdcall DllMain(HMODULE hModule, DWORD  reason, LPVOID lpReserved)
{
    switch (reason)
    {
		case DLL_PROCESS_ATTACH:
		    {
				CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PewPewThread, hModule, 0, nullptr);
		    };
    }
    return TRUE;
}