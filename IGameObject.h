#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "Event.h"


/*
	Interface that all Game Objects should inherit from.

	Contains the means for objects to update internal logic, identify themselves,
	and receive events that they choose to listen to.
*/
class IGameObject
{
public:

	// Identification number used in event system
	unsigned int ID;

	// Determines how the object uses information received from events
	virtual void HandleEvent(Event*) = 0;

	/*
		Function in which any object logic should be placed. 

		>>> DO NOT PUT ANY KIND OF RENDERING CALLS HERE <<<

		Called only when the Game::Update function is called.
	*/
	virtual void Update() = 0;

	virtual ~IGameObject() {}
};

#endif