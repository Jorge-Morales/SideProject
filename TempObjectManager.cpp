// TempObject Manager implementation

#include "TempObjectManager.h"
#include "GlobalEnvironment.h"

// Forward-declare all TempObjects here
class FloatingDamage;

// Update
void TempObjManager::Update()
{
	// Do we need to check if the vector is empty?
	// Render everything in the vector
	for (std::vector<TemporaryObject*>::iterator it = tempObjVector.begin();
		it != tempObjVector.end(); /* LEFT INTENTIONALLY BLANK */)
	{
		TemporaryObject* pTemp = static_cast<TemporaryObject*>(*it);

		if (pTemp->getToBeDeleted())
		{
			delete (pTemp);
			it = tempObjVector.erase(it);
		}
		else
		{
			pTemp->Update();
			++it;
		}
	}
}

// Render
void TempObjManager::Render()
{
	// Do we need to check if the vector is empty?
	// Render everything in the vector
	for (std::vector<TemporaryObject*>::iterator it = tempObjVector.begin();
		it != tempObjVector.end(); ++it)
	{
		(*it)->Render();
	}
}

// Handle events (creation)
void TempObjManager::HandleEvent(Event* pEvent)
{
	if (pEvent->Event_Type == Event_Listings::CREATE_TEMPOBJ)
	{
		// Static Cast the event so we can access it's members
		Create_TempObj_Event* pTemp = static_cast<Create_TempObj_Event*>(pEvent);
		
		/// Create an object based on the ID of the event
		// Floating Damage
		if (pTemp->ID == FLOATING_DAMAGE)
		{
			/*
				Call the factory to call FloatingDamage's constructor, then
				push the newly created object into the vector.
			*/
			tempObjVector.push_back(gEnv->getFactory()->Create(FLOATINGDAMAGE_ID, pTemp->x, pTemp->y));
		}
		// Floating Hand
		else if (pTemp->ID == FLOATING_HAND)
		{
			/*
				Call the factory to call FloatingDamage's constructor, then
				push the newly created object into the vector.
			*/
			tempObjVector.push_back(gEnv->getFactory()->Create(FLOATINGHAND_ID, pTemp->x, pTemp->y));
		}
	}
	else if (pEvent->Event_Type == Event_Listings::END_ENCOUNTER)
	{
		Create_TempObj_Event* pTemp = new Create_TempObj_Event();
		pTemp->ID = FLOATINGHAND_ID;
		pTemp->x = SCREENW - 350;
		pTemp->y = (SCREENH / 4) - 100;
		gEnv->getEventDispatcher()->DispatchEvent(pTemp);
	}
}

// Tors
TempObjManager::TempObjManager()
{
	ID = gEnv->getNewID();
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::CREATE_TEMPOBJ);
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::END_ENCOUNTER);
}

TempObjManager::~TempObjManager()
{
	for (std::vector<TemporaryObject*>::iterator it = tempObjVector.begin();
		it != tempObjVector.end(); /* INTENTIONALLY LEFT BLANK */)
	{
		delete (*it);
		it = tempObjVector.erase(it);
	}

	gEnv->getEventDispatcher()->PurgeListener(this->ID, Event_Listings::CREATE_TEMPOBJ);
	gEnv->getEventDispatcher()->PurgeListener(this->ID, Event_Listings::END_ENCOUNTER);
}