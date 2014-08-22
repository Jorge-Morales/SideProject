#ifndef UI_H
#define UI_H

#include "IGameObject.h"
#include "IRenderableObject.h"
#include "2DRender.h"

class UI : public IGameObject, public IRenderableObject
{
private:

	TwoDRenderer Renderer;

public:

	void HandleEvent(Event* pEvent);
	void Update();
	void Render();

	UI();
	~UI();
};

#endif