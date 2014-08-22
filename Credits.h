#ifndef CREDITS_H
#define CREDITS_H

#include "IGameObject.h"
#include "IRenderableObject.h"
#include "2DRender.h"

class Credits : public IGameObject, public IRenderableObject
{
private:

	TwoDRenderer background;
	TwoDRenderer credits;

public:

	void Update();
	void Render();

	void HandleEvent(Event* pEvent);

	Credits();
	~Credits();
};

#endif