#include "AIEncounterManager.h"
#include "GlobalEnvironment.h"

void AIEncounterManager::setEncounterVector(EncounterVector& newEncounterVector)
{
	/*
		If an encounterVector is already stored, we need to deallocate the memory stored in it
		before we store the 'new' encounterVector.
	*/
	for (int i = 0; i < encounterVector.size(); ++i)
	{
		for (int j = 0; j < encounterVector[i][j].size(); ++j)
		{
			for (Wave::iterator evIt = encounterVector[i][j].begin();
				evIt != encounterVector[i][j].end(); /* INTENTIONALLY LEFT BLANK */)
			{
				delete (*evIt);
				evIt = encounterVector[i][j].erase(evIt);
			}
		}
	}

	// Shallow copy the vector to preserve the pointers stored in the passed vector
	encounterVector = newEncounterVector;
}

void AIEncounterManager::HandleEvent(Event* pEvent)
{
	if (pEvent->Event_Type == Event_Listings::START_ENCOUNTER)
	{
		startInitialEncounter = true;
	}
}

void AIEncounterManager::Update()
{
	/*
		1) Check to see if it's appropriate to increment waveNumber
			- If the player has killed all enemies in a given wave AND incrementing the waveNumber
			  won't result in an array out of bounds error THEN

		2) Validation checks that make sure it's okay to proceed
			- If we've been given the okay to start an encounter AND the current inner-most-
			  vector has elements to iterate through THEN

		3) Iterate through the waveNumber vector and Update any applicable enemies.
			- If the AI is ready to be removed from play, we deallocate its memory and update the vector
				Otherwise, just Update the AI and increment the iterator
	*/

	// 1
	if ( encounterVector.size() > 0 && encounterVector[encounterNumber][waveNumber].size() == 0 
		&& waveNumber + 1 < encounterVector[encounterNumber].size())
	{
		++waveNumber;
	}

	// 2
	if (startInitialEncounter && encounterVector[encounterNumber][waveNumber].size() != 0)
	{
		// 3
		for (Wave::iterator evIt = encounterVector[encounterNumber][waveNumber].begin();
			evIt != encounterVector[encounterNumber][waveNumber].end(); /* INTENTIONALLY LEFT BLANK */)
		{
			if ((*evIt)->removeFromPlay())
			{
				delete (*evIt);
				evIt = encounterVector[encounterNumber][waveNumber].erase(evIt);
			}
			else
			{
				(*evIt)->Update();
				++evIt;
			}
		}
	}

	/*
		If the player exhausted all waves in a particular encounter, we need to reset any
		encounter related variables in preparation for the next encounter.
	*/
	if (encounterVector.size() > 0 && waveNumber + 1 == encounterVector[encounterNumber].size()
		&& encounterVector[encounterNumber][waveNumber].size() == 0)
	{
		startInitialEncounter = false;
		waveNumber = 0;

		// The player has completed an encounter, but hasn't beaten the level yet
		if (encounterNumber + 1 < encounterVector.size())
		{
			++encounterNumber;

			// Send event alerting listeners that an encounter has ended
			End_Encounter_Event* pTemp = new End_Encounter_Event();
			gEnv->getEventDispatcher()->DispatchEvent(pTemp);
		}
		else
		{
			// TODO: Send 'Player beat level' Event?
		}
	}
}

void AIEncounterManager::Render()
{
	/*
		Check to make sure it's okay to iterate through the encounterVector, and then only 
		Render objects that shouldn't be removed from play in the next logic cycle.
	*/
	if (startInitialEncounter && encounterVector[encounterNumber][waveNumber].size() != 0)
	{
		for (Wave::iterator evIt = encounterVector[encounterNumber][waveNumber].begin();
			evIt != encounterVector[encounterNumber][waveNumber].end(); ++evIt)
		{
			/* 
				As long as the AI are still 'valid' (E.G. they aren't dead/incapped), we 
				render them. Otherwise, we skip them and handle the clean up in the update
				cycle.
			*/
			if ((*evIt)->removeFromPlay())
			{
				continue;
			}
			else
			{
				/* 
					Normally we'd dynamic_cast to a IRenderableObject here, but IAI's have a 
					guaranteed inheritance structure that
				*/
				(*evIt)->Render();
			}
		}
	}
}

AIEncounterManager::AIEncounterManager()
{
	startInitialEncounter = false;
	encounterNumber = 0;
	waveNumber = 0;

	// Event System registration
	ID = gEnv->getNewID();
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::START_ENCOUNTER);
}

AIEncounterManager::~AIEncounterManager()
{
	/*
		If we've used the AIEncounterManager, we need to deallocate any memory
		that may not have been handled already.
	*/
	for (int i = 0; i < encounterVector.size(); ++i)
	{
		for (int j = 0; j < encounterVector[i].size(); ++j)
		{
			for (Wave::iterator evIt = encounterVector[i][j].begin();
				evIt != encounterVector[i][j].end(); /* INTENTIONALLY LEFT BLANK */)
			{
				delete (*evIt);
				evIt = encounterVector[i][j].erase(evIt);
			}
		}
	}
}