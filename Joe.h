#ifndef JOE_H
#define JOE_H

#include "Entity.h"
#include <vector>

class IWeapon;
class Event;

class Joe : public Entity
{
private:
	
	// Index of the currently active weapon
	unsigned int currentWeapon;

	// Store all the weapons the player currently has
	std::vector<IWeapon*> Weapons;

	// Switch to a new weapon in the vector if possible
	void SwitchWeapon(unsigned int changeInIndex);

	/*
		Reverts to the idle animation frames if the current 
		animation has completed.
	*/
	void RevertToIdle();

	/*
		Utility function that prevents Joe from moving off the play
		area when moving.

		This is kept seperate from the rest of the movement code to
		make both sections of the code easier to maintain.
	*/
	void BoundaryEnforcement();

	// Flags for limiting actions
	bool isAttacking;
	bool isJumping;
	bool hasMoved;
	bool inEncounter;

	/*
		Because moving right is tied not only to the character movement, but also 
		to the background scrolling, we need to specifically keep track of movements 
		in this direction.
	*/
	bool movedRight;

	// Sounds
	MP3 *whooshSound;

public:

	void HandleEvent(Event* pEvent);
	void Update();
	void Render();

	const RECT getRECT();

	/*
		Add a weapon to the main character.

		For the love of Kemski, don't add the same weapon twice.
		It won't break anything, but, man, it'll look dumb.
	*/
	void AddWeapon(IWeapon* pWeapon);

	/*
		Set an entirely new set of weapons.
	
		O(n) operation, so avoid doing this in gameplay
	*/
	void SwitchWeaponVector(std::vector<IWeapon*>& WeaponVector);

	Joe();
	~Joe();

};

#endif