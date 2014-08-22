#ifndef ENTITY_H
#define ENTITY_H

#include "Collider.h"
#include "IGameObject.h"
#include "IRenderableObject.h"
#include "2DRender.h"

namespace Play_Area
{
	const int TOP = 425;
	const int RIGHT = 1895;
	const int BOTTOM = 900;
	const int LEFT = 25;
};

class Entity : public IGameObject, public IRenderableObject
{
protected:

	unsigned int health;

	// Animation
	unsigned int idleAnimationStart;
	unsigned int idleAnimationEnd;
	bool hasMoved;
	bool isAttacking;

	/*
		The 'depth' of the object in relation to the player's perspective.

		Objects that are 'deeper' in the screen will have a higher depth value.
	*/
	unsigned int depth;

	/*
		A utility function that inheriting classes can use to determine when they
		revert to their default/idle animations.

		This approach is preferable to the dozens-of-statements-everywhere approach
		for obvious reasons.
	*/
	virtual void RevertToIdle() = 0;

	/*
		Utility function that prevents the object from moving
		outside of a defined area (generally off the play area/
		off the screen.
	*/
	virtual void BoundaryEnforcement() = 0;

	// Keeps track of the player's direction
	bool facingLeft;

	// Hitbox of the inherited object
	Collider hitBox;

	TwoDRenderer Renderer;
};

#endif