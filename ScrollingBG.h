#ifndef SCROLL_BG_H
#define SCROLL_BG_H

#include "MyDirectX.h"

class Scrolling_BG
{
private:
	LPDIRECT3DSURFACE9 ScrollBG;
	float ScrollX;
	float ScrollY;

public:
	void InitBG(LPDIRECT3DDEVICE9 d3ddev, int SCREENW, int SCREENH, std::string filename);

	void ModifyScrollX(float Change);
	void SetScrollX(float NewVal);
	void SetScrollY(float NewVal);

	float GetScrollX();
	float GetScrollY();

	void DrawBG(LPDIRECT3DDEVICE9 d3ddev, int SCREENH, int SCREENW);

	Scrolling_BG();
	~Scrolling_BG();
};

#endif