#include "Sword.h"
#include "GlobalEnvironment.h"
#include <mmsystem.h>

void Sword::RevertToIdle()
{
	// No need to switch animations because we're already in the idle animation
	if (Renderer.getEndFrame() == idleAnimationEnd)
	{
		return;
	}
	else
	{
		/*
			If the current animation has finished, we need to change the animation
			frames to the idle frames. Additionally
		*/
		if (Renderer.getCurrentFrame() == Renderer.getEndFrame())
		{
			Renderer.setCurrentFrame(idleAnimationStart);
			isAttacking = false;
			Renderer.Initialize(200, 200, idleAnimationStart, idleAnimationEnd, 100);		
		}
	}
}

bool Sword::Attack(const RECT& compObjectRect, unsigned int compObjectDepth)
{
	/*
		Determine when the weapon can actually attack. This function aler

		1) If there's been a sufficient delay between the last use of the weapon
			and the current system time THEN

		2) Change the active frames based on the direction the composing object
			is facing, and generate an appropriate hit box for the attack.

		3) Update any attacking related flags to reflect the weapon's new status.
			This prevents the weapon from being used again before it should be,
			and helps us avoid animation bugs.

		4) Create an Event that contains the weapon's hit information (hit box,
			damage, depth, etc), and dispatch it to any listeners in the Event
			System.

		5) If the weapon was able to attack, we return true so that the composing
			object knows that an attack has occured. Otherwise, we return false.
	*/

	// 1
	if (delayBetweenAttacks + lastAttackTime < GetTickCount())
	{
		// '36' is the approximate length of the sword attack. 
		// 2
		if (facingLeft)
		{
			Renderer.Initialize(200, 200, 22, 27, 65);

			// We give this a width of 100 to allow the weapon to attack enemies 'on' the player
			hitBox.Initialize(Renderer.getPos().x + 110, Renderer.getPos().y, 110, 139 * Renderer.getScaleY());
		}
		else
		{
			Renderer.Initialize(200, 200, 8, 13, 65);

			hitBox.Initialize(Renderer.getPos().x + (120 * Renderer.getScaleX()), Renderer.getPos().y, 115, 139 * Renderer.getScaleY());
		}
		
		// 3
		isAttacking = true;
		lastAttackTime = GetTickCount();

		// 4
		Player_Attack_Event* pTemp = new Player_Attack_Event();
		pTemp->damageBox = hitBox.getBoundingBox();
		pTemp->damage = damage;
		pTemp->depth = compObjectDepth;
		gEnv->getEventDispatcher()->DispatchEvent(pTemp);

		// 5
		return true;
	}
	else
	{
		// 5
		return false;
	}
}

void Sword::ComposerWasAttacked()
{
	// TODO: Hurt animations
}

void Sword::ComposerMoved()
{
	/* 
		If the composer has moved, we need update the current animation frames
		to whatever the 'in motion' frames are. 
	*/
	if (facingLeft)
	{
		Renderer.Initialize(200, 200, 18, 21, 100);
	}
	else
	{
		Renderer.Initialize(200, 200, 4, 7, 100);
	}
}

bool Sword::FinishedAttacking()
{
	/*
		
	*/
	unsigned int attackEndFrame = 0;
	if (facingLeft)
	{
		attackEndFrame = 27;
	}
	else
	{
		attackEndFrame = 13;
	}

	if (Renderer.getEndFrame() != attackEndFrame)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// DEPRECATED
void Sword::Update(long xPosition, long yPosition)
{
	Renderer.setX(xPosition);
	Renderer.setY(yPosition); 
	Renderer.Update();

	RevertToIdle();
}

void Sword::Update(long xPosition, long yPosition, bool isFacingLeft)
{
	// We need to update several flags/values if we've changed directions
	if (facingLeft != isFacingLeft)
	{
		facingLeft = isFacingLeft;

		if (facingLeft)
		{
			idleAnimationStart = 18;
			idleAnimationEnd = 21;
		}
		else
		{
			idleAnimationStart = 4;
			idleAnimationEnd = 7;
		}
	}

	Renderer.setX(xPosition);
	Renderer.setY(yPosition);
	Renderer.Update();

	RevertToIdle();
}

void Sword::Render()
{
	Renderer.Render();
}

Sword::Sword()
{
	damage = 3;
	idleAnimationStart = 4;
	idleAnimationEnd = 7;
	delayBetweenAttacks = 390;
	lastAttackTime = 0;
	facingLeft = false;

	Renderer.Initialize(2.5f, 2.5f, 200, 200, 10, idleAnimationStart, idleAnimationEnd,
						115, 1, 0, 0.0f, 0.0f, "Joepla_arms.png");
	Renderer.setAnimateFlag(true);
}