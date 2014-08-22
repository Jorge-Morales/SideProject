#include "ScrollingBG.h"

void Scrolling_BG::InitBG(LPDIRECT3DDEVICE9 d3ddev, int SCREENW, int SCREENH, std::string filename)
{
	int BUFFERW = SCREENW * 2;
	int BUFFERH = SCREENH * 2;

	LPDIRECT3DSURFACE9 TempImage = LoadSurface(filename);
	
	

	if(!TempImage)
	{
		MessageBox(NULL, "TEMP_IMAGE", "INITBG", MB_OK);
	}

	HRESULT result = d3ddev->CreateOffscreenPlainSurface(BUFFERW, BUFFERH, D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT, &ScrollBG, NULL);

	if(result != D3D_OK)
	{
		MessageBox(NULL, "DEBUG", "INITBG", MB_OK);
	}

	RECT SOURCE_RECT = { 0, 0, SCREENW, SCREENH };

	RECT src_ul = { 0, 0, SCREENW, SCREENH };
	d3ddev->StretchRect(TempImage, &SOURCE_RECT, ScrollBG, &src_ul, D3DTEXF_NONE);

	RECT src_ur = { SCREENW, 0, SCREENW * 2, SCREENH };
	d3ddev->StretchRect(TempImage, &SOURCE_RECT, ScrollBG, &src_ur, D3DTEXF_NONE);

	RECT src_ll = { 0, SCREENH, SCREENW, SCREENH *2 };
	d3ddev->StretchRect(TempImage, &SOURCE_RECT, ScrollBG, &src_ll, D3DTEXF_NONE);

	RECT src_lr = { SCREENW, SCREENH, SCREENW * 2, SCREENH * 2 };
	d3ddev->StretchRect(TempImage, &SOURCE_RECT, ScrollBG, &src_lr, D3DTEXF_NONE);

	TempImage->Release();
}

void Scrolling_BG::ModifyScrollX(float Change)
{
	ScrollX += Change;
}

void Scrolling_BG::SetScrollX(float NewVal)
{
	ScrollX = NewVal;
}

void Scrolling_BG::SetScrollY(float NewVal)
{
	ScrollY = NewVal;
}

float Scrolling_BG::GetScrollX()
{
	return ScrollX;
}

float Scrolling_BG::GetScrollY()
{
	return ScrollY;
}

void Scrolling_BG::DrawBG(LPDIRECT3DDEVICE9 d3ddev, int SCREENW, int SCREENH)
{
	// For scrolling background
		RECT srect = {ScrollX, ScrollY, ScrollX + SCREENW, ScrollY + SCREENH};
		RECT drect = {0, 0, SCREENW, SCREENH};

		d3ddev->StretchRect(ScrollBG, &srect, backbuffer, &drect, D3DTEXF_NONE);
}

// TORS
Scrolling_BG::Scrolling_BG()
{
	ScrollX = 0;
	ScrollY = 0;

	ScrollBG = NULL;


}

Scrolling_BG::~Scrolling_BG()
{
	ScrollBG->Release();
}