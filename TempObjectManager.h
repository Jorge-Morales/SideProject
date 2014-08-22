#ifndef TEMPOBJMAN_H
#define TEMPOBJMAN_H

#include "TempObj.h"
#include "IGameObject.h"
#include <vector>

/*
	Created by Garhett Bambrick

	TempObjManager controls the operation of temporary objects, such as
	 - Floating Damage
	 - Particle effects
	 - Floating XP

	If something should be rendered to the screen for a set period of
	time and then removed, it should be a TempObj of some sort. The
	manager handles the updating and rendering of all TempObj objects.
	It manages memory when a TempObj object's life has expired, making
	sure that no memory leaks occur (this is most important).
*/

/*
	Forward-declare TempObject and Event to save on compile time (we'll
	include	the actual header files in the manager's implementation)
*/

class TempObjManager : public IGameObject
{
private:
	
	// This vector holds all of the TempObj objects.
	std::vector<TemporaryObject*> tempObjVector;

public:
	
	/*
		Retrieve static address of the TempObjManager.

		Should only be called within GlobalEnvironment.
	*/
	static TempObjManager& getInstance()
	{
		static TempObjManager* pInstance = NULL;

		if (!pInstance)
		{
			pInstance = new TempObjManager();
		}

		return (*pInstance);
	}

	/*
		Handles events.

		Call this in the Update function.
	*/
	void HandleEvent(Event* pEvent);


	/*
		Tells the objects to update

		Only call this in the Update cycle of Game. DO NOT call this in the Render cycle.
	*/
	void Update();

	/*
		Only call this in the Render cycle of Game. DO NOT call this in the Update cycle.
	*/
	void Render();

	// Tors
	TempObjManager();
	~TempObjManager();
};


#endif