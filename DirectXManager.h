#ifndef D3DMAN_H
#define D3DMAN_H

#include <d3d9.h>
#include <d3dx9.h>

// libraries
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

#pragma warning (disable : 4081 4244 4800 4018)

class D3DManager
{
private:

	// References to DirectX9 variables
	IDirect3DDevice9* pD3DDev;
	IDirect3D9* pD3D;
	IDirect3DSurface9* pBackBuffer;
	ID3DXSprite* pSpriteObject;
	IDirect3DVertexBuffer9* pVertexBuffer;
	D3DPRESENT_PARAMETERS d3dpp;

	// We require these for 3D rendering
	D3DXMATRIX matOrtho;
	D3DXMATRIX matIdent;

	// Camera variables
	D3DXMATRIX matProj;
	D3DXMATRIX matView;

	// A one time initialization process that preps the vertex buffer for use
	void initVertexBuffer();

	D3DManager();

public:

	static D3DManager& getInstance()
	{
		static D3DManager* pInstance = NULL;

		if (!pInstance)
		{
			pInstance = new D3DManager();
		}

		return (*pInstance);
	}

	bool Initialize();

	IDirect3DDevice9* getD3DDevice();
	IDirect3D9* getD3D();
	IDirect3DSurface9* getBackbuffer();
	ID3DXSprite* getSpriteObject();
	IDirect3DVertexBuffer9* getVertexBuffer();
	D3DPRESENT_PARAMETERS getDPP();

	~D3DManager();
};

#endif