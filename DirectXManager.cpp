#include "DirectXManager.h"
#include "GlobalEnvironment.h"

// Vertex format used to draw our 3D, 2D images
const DWORD D3DFVF_TLVERTEX = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

// Struct that defines the format of our vertex
struct TLVERTEX
{
	// Positional variables
		// Y is assumed to be 0, but can be modified to give depth effects
	float x;
	float y;
	float z;

	// Color and alpha value of the vertex
		// 32-bit value in AARRGGBB format
	D3DCOLOR colour;

	// Coordinates for the texture to be applied on the vertex
		// u = 0.0f == left | u = 1.0f == right
		// v = 0.0f == top | v = 1.0f == bottom
	float u;
	float v;
};

bool D3DManager::Initialize()
{
	HRESULT hr;

	//initialize Direct3D
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D)
	{
		MessageBox(NULL, "Failed Initializing DirectXManager", "D3D did not initialize", MB_OK);
		return false;
	}

	// Set Direct3D presentation parameters
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.hDeviceWindow = gEnv->getWindow();
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
	//d3dpp.EnableAutoDepthStencil = 1;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	//d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	d3dpp.BackBufferCount = 1;

	//Check if windowed
	if (!fullscreen)
	{
		D3DDISPLAYMODE d3ddm;
		RECT rWindow;

		//Get display mode
		pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

		//Get window bounds
		GetClientRect(gEnv->getWindow(), &rWindow);

		int newBackBufferW = 0;
		int newBackBufferH = 0;
		//Setup screen dimensions
		newBackBufferW = rWindow.right - rWindow.left;
		newBackBufferH = rWindow.bottom - rWindow.top;

		//Setup backbuffer
		d3dpp.Windowed = true;
		d3dpp.BackBufferFormat = d3ddm.Format;
		d3dpp.BackBufferWidth = rWindow.right - rWindow.left;
		d3dpp.BackBufferHeight = rWindow.bottom - rWindow.top;
	}
	else
	{
		d3dpp.Windowed = false;
		d3dpp.BackBufferWidth = SCREENW;
		d3dpp.BackBufferHeight = SCREENH;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	}

	//Capabilities of graphics adapter
	D3DCAPS9 d3dCaps;
	ZeroMemory(&d3dCaps, sizeof(d3dCaps));
	pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps);

	//Check if hardware vertex processing is available
	if (d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		//Create device with hardware vertex processing
		hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, gEnv->getWindow(),
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pD3DDev);
	}
	else
	{
		//Create device with software vertex processing
		hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, gEnv->getWindow(),
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDev);
	}

	//Make sure device was created
	if (FAILED(hr))
	{
		MessageBox(NULL, "Failed loading DirectXManager", "D3DDEV did not initialize", MB_OK);
		return FALSE;
	}

	//Setup orthographic projection matrix
	D3DXMatrixOrthoLH(&matOrtho, d3dpp.BackBufferWidth, d3dpp.BackBufferHeight, 1.0f, 10.0f);
	D3DXMatrixIdentity(&matIdent);
	pD3DDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
	pD3DDev->SetTransform(D3DTS_VIEW, &matIdent);
	pD3DDev->SetTransform(D3DTS_WORLD, &matIdent);

	//get a pointer to the back buffer surface
	pD3DDev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);

	// The vertexBuffer is a bit complicated, so we initialize it in its own function
	initVertexBuffer();

	//create sprite object
	D3DXCreateSprite(pD3DDev, &pSpriteObject);

	pD3DDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// Kludgey camera code
	//Here we specify the field of view, aspect ration and near and far clipping planes.
	// D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, SCREENW / SCREENH, 1.0f, 500.0f);
	// pD3DDev->SetTransform(D3DTS_PROJECTION, &matProj);
	// 
	// // Point the camera to a point in space
	// D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(0.0f, 0.0f, -15.0f),		//Camera Position
	// 				   &D3DXVECTOR3(0.0f, 0.0f, 0.0f),					//Look At Position
	// 				   &D3DXVECTOR3(0.0f, 1.0f, 0.0f));	//Up Direction
	// 
	// pD3DDev->SetTransform(D3DTS_VIEW, &matView);

	return true;
}

void D3DManager::initVertexBuffer()
{

	// Create the vertex buffer
	pD3DDev->CreateVertexBuffer(sizeof(TLVERTEX)* 4, NULL,
		D3DFVF_TLVERTEX, D3DPOOL_MANAGED,
		&pVertexBuffer, NULL);

	pD3DDev->SetStreamSource(0, pVertexBuffer, 0, sizeof(TLVERTEX));

	// Set the current vertex shader
	pD3DDev->SetVertexShader(NULL);
	pD3DDev->SetFVF(D3DFVF_TLVERTEX);

	TLVERTEX* vertices = NULL;
	pVertexBuffer->Lock(0, 4 * sizeof(TLVERTEX), (VOID**)&vertices, 0);

	// Setup vertices
		// This method does not allow colour modulation
	vertices[0].colour = 0xffffffff;
	vertices[0].x = 0.0f;
	vertices[0].y = 0.0f;
	vertices[0].z = 1.0f;
	vertices[0].u = 0.0f;
	vertices[0].v = 0.0f;

	vertices[1].colour = 0xffffffff;
	vertices[1].x = 1.0f;
	vertices[1].y = 0.0f;
	vertices[1].z = 1.0f;
	vertices[1].u = 1.0f;
	vertices[1].v = 0.0f;

	vertices[2].colour = 0xffffffff;
	vertices[2].x = 1.0f;
	vertices[2].y = -1.0f;
	vertices[2].z = 1.0f;
	vertices[2].u = 1.0f;
	vertices[2].v = 1.0f;

	vertices[3].colour = 0xffffffff;
	vertices[3].x = 0.0f;
	vertices[3].y = -1.0f;
	vertices[3].z = 1.0f;
	vertices[3].u = 0.0f;
	vertices[3].v = 1.0f;

	pVertexBuffer->Unlock();
}

IDirect3DDevice9* D3DManager::getD3DDevice()
{
	return pD3DDev;
}

IDirect3D9* D3DManager::getD3D()
{
	return pD3D;
}

IDirect3DSurface9* D3DManager::getBackbuffer()
{
	return pBackBuffer;
}

ID3DXSprite* D3DManager::getSpriteObject()
{
	return pSpriteObject;
}

IDirect3DVertexBuffer9* D3DManager::getVertexBuffer()
{
	return pVertexBuffer;
}

D3DPRESENT_PARAMETERS D3DManager::getDPP()
{
	return d3dpp;
}

D3DManager::D3DManager()
{
	pD3DDev = NULL;
	pD3D = NULL;
	pBackBuffer = NULL;
	pSpriteObject = NULL;
	pVertexBuffer = NULL;
}

D3DManager::~D3DManager()
{
	// We need to deallocate the vertex buffer first because it requires a valid instance of D3DDev
	if (pVertexBuffer)
	{
		pD3DDev->SetStreamSource(0, NULL, 0, 0);

		pVertexBuffer->Release();
		delete pVertexBuffer;
		pVertexBuffer = NULL;
	}

	/*
		DirectX variables can't be properly handled by just using delete on their pointer
		so we need to call their virtual Release() function to allow them to handle their
		own memory internally before NULLing out the pointer
	*/
	if (pD3DDev)
	{
		pD3DDev->Release();
		delete pD3DDev;
		pD3DDev = NULL;
	}

	if (pD3D)
	{
		pD3D->Release();
		delete pD3D;
		pD3D = NULL;
	}

	if (pBackBuffer)
	{
		pBackBuffer->Release();
		delete pBackBuffer;
		pBackBuffer = NULL;
	}

	if (pSpriteObject)
	{
		pSpriteObject->Release();
		delete pSpriteObject;
		pSpriteObject = NULL;
	}
}