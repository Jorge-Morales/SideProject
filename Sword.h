#ifndef SWORD_H
#define SWORD_H

#include "IWeapon.h"

class Sword : public IWeapon
{
private:

	/*
		Determines when it's appropriate to revert to the idle animation.

		This is called every time an Update function is called to make sure
		we don't accidently stay on the same animation for longer than needed.
	*/
	void RevertToIdle();

public:

	/*
		Attack is a general purpose function that weapons use to deal damage.

		Attack returns true if an attack was made, and returns false if the action
		couldn't occur for whatever reason (I.E. Out of ammo, delay still active, etc).
	*/
	bool Attack(const RECT& composingObjectRect, unsigned int composingObjectDepth);

	/*
		Call this when the composing object is hit to allow the weapon to compensate
		accordingly.
	*/
	void ComposerWasAttacked();

	/*
		Allows the composing object to know when a particular weapon is done 
		attacking.

		This is primarily used to limit the amount of times the composer can
		attack in a given timeframe.
	*/
	bool FinishedAttacking();

	/*
		The composing object should call this every update frame BEFORE it calls
		the Update function of the weapon.

		This will allow the composed weapon to make any animation adjustments necessary
		to react to the composer's movement.
	*/
	void ComposerMoved();

	/*
		Call this function when the composing object moves, to make sure that the weapon
		'travels' with the object properly, or to initialize a weapon when switching to it
		or on startup
	*/
	void Update(long xPosition, long yPosition);

	/*
		Call this function when the composing object moves, to make sure that the weapon
		'travels' with the object properly, or to initialize a weapon when switching to it
		or on startup
	*/
	void Update(long xPosition, long yPosition, bool isFacingLeft);

	void Render();

	Sword();
	~Sword();
};

#endif