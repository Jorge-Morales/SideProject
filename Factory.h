#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include "TempObj.h"

/*
	The Factory is used to create objects of any type. Use
	it ONLY in Managers, NOT in objects themselves.

	To use the Factory:
	 - First, include the Factory.
	 - Second, make sure you have forward-declared any objects
		you are going to be using.
	 - Third, you are going to need to define a creation event
		in Event.h that has an x, y, and ID.
	 - Fourth, in the Manager's HandleEvent function, once
		you've set it up to handle the creation event, add a
		series of if-elseifs to check the ID of the event
		currently being handled.
	 - Fifth, once you've identified the appropriate ID,
		add a call to the templated Create function. The
		syntax is as follows:
		
		ObjectType* tempPtr = gEnv->getFactory()->Create<ObjectType>(pTemp->x, pTemp->y);

	If it isn't working, make sure you have the object forward-declared.
*/

/*
	The TemporaryObject Factory, for all your TemporaryObject
	creation needs (patent pending).
*/

// Enum of object IDs
enum ObjectIDs
{
	FLOATINGDAMAGE_ID = 150,
	FLOATINGHAND_ID = 151
};

class Factory
{
private:

	// Mapmagical
	std::map<int, TemporaryObject*> mObjectMap;

	// Better method that we don't have time to implement
	//std::map<int, void* (float, float)> objectMap;

public:


	static Factory& getInstance();

	/*
		Use this to create new Temporary Objects. The calling
		code will look something like this:

		FloatingDamage* f = gEnv()->getFactory()->Create(FLOATINGDAMAGE_ID, 150.0f, 250.0f);
	*/
	TemporaryObject* Create(int ID, float startX, float startY);

	// Register objects with the factory
	void RegisterNewObject(int ID, TemporaryObject* newObject);
	
	// Better method that we don't have time to implement
	/*
	template<class T>
	void RegisterNewObject(int ID, T(ObjectReference)(float, float))
	{
		//objectMap.insert(ID, ObjectReference);
	}
	*/

	// Anticonstructor
	~Factory();
};

#endif