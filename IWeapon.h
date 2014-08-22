#ifndef IWEAPON_H
#define IWEAPON_H

#include "Collider.h"
#include "2DRender.h"
#include "IRenderableObject.h"

/*
	IWeapon is an interface that all weapons must inherit from to guarantee
	compatibility with weapon using objects.

	IWeapon allows any weapon implementation code to be kept seperate from
	the composing object. This allows us to easily add weapons to existing 
	classes without modifying the existing object code.

	(I punch that into my calculator and it makes a happy face)
*/
class IWeapon : public IRenderableObject
{
protected:

	// Damage this weapon does when hitting an enemy
	unsigned int damage;

	// Timing variables to control weapon attack rates
	unsigned int delayBetweenAttacks;
	unsigned int lastAttackTime;
	bool isAttacking;

	// Animation 
	unsigned int idleAnimationStart;
	unsigned int idleAnimationEnd;

	/*
		Direction value of the composing object.

		True = facing left
		False = facing right
	*/
	bool facingLeft;

	TwoDRenderer Renderer;

	/*
		Area this weapon hits when an attack is performed.

		This area is determined by the composing object's RECT and directional
		value. As such, it's important that this object's positional values are
		updated as frequently as the composing object moves.
	*/
	Collider hitBox;

	virtual void RevertToIdle() = 0;

public:

	/*
		Attack is a general purpose function that weapons use to deal damage.

		Attack returns true if an attack was made, and returns false if the action
		couldn't occur for whatever reason (I.E. Out of ammo, delay still active, etc).
	*/
	virtual bool Attack(const RECT& composingObjectRect, unsigned int composingObjectDepth) = 0;

	/*
		Call this when the composing object is hit to allow the weapon to compensate
		accordingly.
	*/
	virtual void ComposerWasAttacked() = 0;

	// Allows the composing object to know when a particular weapon is done attacking
	virtual bool FinishedAttacking() = 0;

	/*
		The composing object should call this every update frame BEFORE it calls
		the Update function of the weapon.
	
		This will allow the composed weapon to make any animation adjustments necessary
		to react to the composer's movement.
	*/
	virtual void ComposerMoved() = 0;

	/*
		Call this function when the composing object moves, to make sure that the weapon
		'travels' with the object properly, or to initialize a weapon when switching to it
		or on startup
	*/
	virtual void Update(long xPosition, long yPosition) = 0;
	virtual void Update(long xPosition, long yPosition, bool isFacingLeft) = 0;

	~IWeapon(){}
};

#endif