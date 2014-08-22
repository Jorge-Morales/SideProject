#ifndef DBG_H
#define DBG_H

#include "IBackground.h"
#include "2DRender.h"
#include "GlobalEnvironment.h"
#include <string>

/*
	Dynamic Background class
	Created by Garhett Bambrick
	-----------------------------------------------
	The background can move when it receives a move event
*/

class DynamicBackground : public IBackground
{
private:

	/* 
		This background will move at a certain speed depending on
		what layer it's on. Immediate background should be 1.
		The further back the background should appear, the smaller
		this number should be.
	*/
	float moveSpeed;
	

public:

	bool isLocked;
	
	// get position
	Vector2 getPos();

	// Handle events
	void HandleEvent(Event* pEvent);

	void Update();

	void Render();

	// Tors
	DynamicBackground();

	// Create a Background with specific parameters
	DynamicBackground(float MS, int frameW, int frameH, float startX, float startY, std::string texture);

	~DynamicBackground();
};

#endif