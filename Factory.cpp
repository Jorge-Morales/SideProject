// Factory implementation

#include "Factory.h"

Factory& Factory::getInstance()
{
	static Factory* pInstance = NULL;

	if (!pInstance)
	{
		pInstance = new Factory();
	}

	return (*pInstance);
}

TemporaryObject* Factory::Create(int ID, float startX, float startY)
{
	return mObjectMap[ID]->CreateInstance(startX, startY);
}

// Register objects with the factory
void Factory::RegisterNewObject(int ID, TemporaryObject* newObject)
{
	mObjectMap[ID] = newObject;
}

Factory::~Factory()
{
	std::map<int, TemporaryObject*>::iterator it;

	for (it = mObjectMap.begin(); it != mObjectMap.end(); /* Intentionally left blank */)
	{
		delete it->second;
		it = mObjectMap.erase(it);
	}
}