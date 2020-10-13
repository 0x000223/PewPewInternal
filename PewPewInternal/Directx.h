#pragma once

typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);

static HWND Window;

extern int windowHeight;
extern int windowWidth;

//
bool GetD3D9Device(void** pTable, size_t size);

//
HWND GetProcessWindow();

//
void InitImGui(IDirect3DDevice9* pDevice);