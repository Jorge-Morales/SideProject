#ifndef MAINMENU_H
#define MAINMENU_H

#include "IGameObject.h"
#include "IRenderableObject.h"
#include "2DRender.h"

class MainMenu : public IGameObject, public IRenderableObject
{
private:

	TwoDRenderer Renderer;

	TwoDRenderer StartRender;
	TwoDRenderer CreditsRender;

	RECT startGameRect;
	RECT creditsRect;
	RECT exitRect;

public:

	void HandleEvent(Event* pEvent);
	void Update();
	void Render();

	MainMenu();
	~MainMenu();
};

#endif