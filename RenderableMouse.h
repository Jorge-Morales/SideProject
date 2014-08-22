#ifndef RENDMOUSE_H
#define RENDMOUSE_H

#include "IInputDevice.h"
#include "IRenderableObject.h"
#include "2DRender.h"

class RenderMouse : public IInputDevice, public IRenderableObject
{
protected:

	TwoDRenderer Renderer;
	POINT prevPos, curPos;
	unsigned int state;
	
public:

};

#endif