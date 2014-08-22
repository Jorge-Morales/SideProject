#ifndef IBACKGROUND_H
#define IBACKGROUND_H

#include "IGameObject.h"
#include "IRenderableObject.h"
#include "2DRender.h"

/*
	Interface that backgrounds should inherit from.
*/

class IBackground : public IGameObject, public IRenderableObject
{
protected:
	
	/*
		Being that all backgrounds need to draw, we them to have 
		a rendering extension of some kind.
	*/
	TwoDRenderer Renderer;
	
public:

	virtual Vector2 getPos() = 0;
	virtual ~IBackground(){}

};

#endif