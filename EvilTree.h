#ifndef EVILTREE_H
#define EVILTREE_H

#include "IAI.h"

class EvilTree : public IAI
{
private:

	/*
		A utility function that reverts the animation cycle to the idle animation
		when another animation (I.E. Walking, Attacking, etc) has finished.
	*/
	void RevertToIdle();

	void BoundaryEnforcement();

	// Sounds
	MP3 *spawnSound, *menacingSound, *deathSound;
	bool soundPlayed;

public:

	/*
		Informs the AIEncounterManager when this object is ready to be deleted, 
		by checking the object's internal internal state.

		The removal criteria differ from object to object, but generally revolve
		around the object dying, or otherwise being incapacitated.
	*/
	bool removeFromPlay();

	/*
		In an effort to keep the Event System running fluidly, AI will only register
		listeners while their active on the screen. To accomplish this, the AIEncounterManager
		will call this function
	*/
	void RegisterWithES();

	void HandleEvent(Event* pEvent);
	void Update();
	void Render();

	EvilTree(unsigned int xPosition, unsigned int yPosition);
	~EvilTree();
};

#endif