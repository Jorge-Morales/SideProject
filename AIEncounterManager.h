#ifndef AIENCOUNTERMAN_H
#define AIENCOUNTERMAN_H

#include "IAI.h"
#include "IGameObject.h"

#include <vector>

/*
	Typedefing this here to reduce syntax confusion.
*/
typedef std::vector<IAI*> Wave;
typedef std::vector<Wave> Encounter;
typedef std::vector<Encounter> EncounterVector;

/*
	AIEncounterManager controls when to Update and Render a given level's AI.

	This allows us to have a managed way of determining when AI is drawn to the
	screen or updated, and minimizes the amount of memory that needs to be allocated
	during runtime.
*/
class AIEncounterManager : public IGameObject
{
private:

	// Vector used
	EncounterVector encounterVector;

	unsigned int encounterNumber;
	unsigned int waveNumber;

	AIEncounterManager();

	/*
		Determines when to begin Updating/Rendering the active vector.

		gets updated when an EncounterStart Event is received.
	*/
	bool startInitialEncounter;

public:

	/*
		Retrieve static address of the AIEncounterManager.

		Should only be called within GlobalEnvironment.
	*/
	static AIEncounterManager& getInstance()
	{
		static AIEncounterManager* pInstance = NULL;

		if (!pInstance)
		{
			pInstance = new AIEncounterManager();
		}

		return (*pInstance);
	}
	
	/*
		Store a level's EncounterVector into the AIEncounterManager so that it can be used.

		Call this when loading a new level, or when restarting a level. 
		
		Calling this during gameplay when an EncounterVector is already stored is 
		ill-advised as it's, potentially, an O(n^3) operation and may cause a noticeable 
		slowdown in the game.
	*/
	void setEncounterVector(EncounterVector& newEncounterVector);

	/*
		Function that determines how this class processes events that it listens for.

		This should never be called directly, and should instead be invoked by the delegate
		the Event System uses.
	*/
	void HandleEvent(Event* pEvent);

	/*
		Iterates through the currently active encounter vector and Updates the stored AI.
		
		Only call this in the Update cycle of Game. DO NOT call this in the Render cycle.
	*/
	void Update();

	/*
		Iterates through the currently active encounter vector and Renders the stored AI.

		Only call this in the Render cycle of Game. DO NOT call this in the Update cycle.
	*/
	void Render();

	
	/*
		Deallocate any AI remaining in the EncounterVector, and remove all listeners associated
		with this class from the Event System.
	*/
	~AIEncounterManager();
};

#endif