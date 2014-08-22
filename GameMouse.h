#ifndef GAMEMOUSE_H
#define GAMEMOUSE_H

#include "RenderableMouse.h"
#include "IGameObject.h"

class GameMouse : public RenderMouse, public IGameObject
{
private:

	bool leftClick;
	bool rightClick;
	TwoDRenderer altRender;

public:

	void Update();
	void Render();

	void HandleEvent(Event* pEvent);
	void ProcessInput(const unsigned int mask);

	GameMouse();
	~GameMouse();
};

#endif