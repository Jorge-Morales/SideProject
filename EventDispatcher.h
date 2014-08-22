#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include "Delegate.h"
#include "IGameObject.h"

#include <queue>
#include <map>

/* 
	Typedefing this here because the syntax for nested STL data structures
	is absolutely atrocious otherwise. 
*/
typedef std::map<unsigned int, Delegate> Listeners;

class EventDispatcher
{
private:

	/*
		Registrants stores Delegates that need to receive events.

		To do this, Registrants is organized into 'rows' where each row
		represents a different Event to be listened for. Each row is accessed 
		by an unsigned int key, and contains a vector of Delegates. The Event
		is passed through the vector until someone claims it, or there are no
		more objects for the Event to be distributed to.
	*/
	std::map<unsigned int, Listeners> Registrants;

	// Store 
	std::queue<Event*> EventQueue;

	/*
		Creates, and returns, a Delegate out of the passed pointer so that 
		the object can be stored and receive Events.

		TODO: The event system shouldn't be the only person with the ability 
			to create Delegates. Come up with a better way of handling this 
			kind of thing as multiple systems will need to do this at some point.
	*/
	Delegate PackageListener(IGameObject* pIGO);

	
	// Stores a Delegate into Registrants to allow it to receive Events of type eventCode
	void StoreListener(Delegate, unsigned int eventCode);

	EventDispatcher();

public:

	~EventDispatcher();

	static EventDispatcher& getInstance()
	{
		static EventDispatcher* pInstance = NULL;

		if (!pInstance)
		{
			pInstance = new EventDispatcher();
		}

		return (*pInstance);
	}

	/*
		Public function that hides the internal process of Delegate creation and
		registering.

		Call this function any time you need to register an object with the event system.
	*/
	void RegisterListener(IGameObject* pIGO, unsigned int eventCode);


	// Distributes the receieved event to any listeners registered for it
	void DispatchEvent(Event* pEvent);

	/*
		Purges the entire contents of Registrants. Use when transitioning
		between levels, or something.

		If you only need to remove a specific listener from the event system,
		call the PurgeListener function instead.
	*/
	void PurgeAllListeners();

	// Remove a specific listener from a given event listing
	void PurgeListener(unsigned int ID, unsigned int eventCode);

	// Process all events that have been received since the last Update cycle
	void Update();
};

#endif
