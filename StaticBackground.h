#ifndef SBG_H
#define SBG_H

#include "IBackground.h"
#include "2DRender.h"
#include "GlobalEnvironment.h"
#include <string>

/*
	Static Background class
	Created by Garhett Bambrick
	-----------------------------------------------
	The background never moves
*/

class StaticBackground : public IBackground
{
private:

public:

	// get position
	Vector2 getPos()
	{
		return Renderer.getPos();
	}

	// Handle events
	void HandleEvent(Event* pEvent)
	{
		
	}

	void Update()
	{

	}

	void Render()
	{
		Renderer.Update();
	}

	// Tors
	StaticBackground()
	{
		Renderer.Initialize(1.0f, 1.0f, 5120, 768, 1, 0, 0, 0, 1, 0, 0.0f, 0.0f, "Hallway.jpg");
	}

	// Create a Background with specific parameters
	StaticBackground(int frameW, int frameH, float startX, float startY, std::string texture)
	{
		Renderer.Initialize(1.0f, 1.0f, frameW, frameH, 1, 0, 0, 0, 1, 0, 0.0f, 0.0f, texture);
		Renderer.setX(startX);
		Renderer.setY(startY);
	}

	~StaticBackground(){}

};

#endif