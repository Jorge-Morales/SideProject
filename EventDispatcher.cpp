#include "EventDispatcher.h"

void EventDispatcher::StoreListener(Delegate del, unsigned int eventCode)
{
	/*
		TODO: Consider making it an array of Delegate pointers

			  It would make memory management a hassle, but would
			  use substantially less memory overall if used in a large
			  project.

		Delegate* ptr = &Del;
	*/

	Registrants[eventCode][del.ID] = del;
}


Delegate EventDispatcher::PackageListener(IGameObject* pIGO)
{
	Delegate D = Delegate::makeDelegateFromFunction<IGameObject, &IGameObject::HandleEvent>(pIGO, pIGO->ID);

	return D;
}

void EventDispatcher::RegisterListener(IGameObject* pIGO, unsigned int eventCode)
{
	StoreListener(PackageListener(pIGO), eventCode);
}

void EventDispatcher::DispatchEvent(Event* pEvent)
{
	EventQueue.push(pEvent);
}

void EventDispatcher::PurgeAllListeners()
{
	// Listeners::iterator lIt;

	for (unsigned int i = 0; i < Registrants.size(); ++i)
	{
		//for (lIt = Registrants[i].begin(); lIt != Registrants[i].end(); ++lIt)
		//{
		//		Use this if we ever switch over to pointers to Delegates
		//}

		Registrants[i].erase(Registrants[i].begin(), Registrants[i].end());
	}
}

void EventDispatcher::PurgeListener(unsigned int ID_NUMBER, unsigned int eventCode)
{
	// Iterate through the Registrants map
	//for(Listeners::iterator InnerIter = Registrants[eventCode].begin(); InnerIter != Registrants[eventCode].end(); )
	//{
	//	// Remove an element from the vector
	//	if(InnerIter->ID == ID_NUMBER)
	//	{
	//		InnerIter = Registrants[eventCode].erase(InnerIter);
	//		break;
	//	}
	//	else
	//	{
	//		InnerIter++;
	//	}
	//}

	// Remove the specified listener
	Registrants[eventCode].erase(ID_NUMBER);
}

void EventDispatcher::Update()
{
	// Dispatch all events
	while (EventQueue.empty() != true)
	{
		// More convienent reference to the Event
		Event* pEvent = EventQueue.front();

		if (pEvent == NULL)
		{
			// TODO: Create proper error message because this should not happen
			return;
		}

		Listeners::iterator Iter = Registrants[pEvent->Event_Type].begin();

		// Iterate through the 
		while (pEvent->handledErase != true && Iter != Registrants[pEvent->Event_Type].end())
		{
			(*Iter).second(pEvent);

			++Iter;
		}

		delete pEvent;
		pEvent = NULL;
		EventQueue.pop();
	}
}

EventDispatcher::EventDispatcher()
{
	for(int i = 0; i <= Event_Listings::MAX; ++i)
	{
		Registrants[i] = Listeners();
	}
}

EventDispatcher::~EventDispatcher()
{
	// Purges Registrants to deallocate memory
	this->PurgeAllListeners();
}