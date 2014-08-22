// TempObj implementation

#include "TempObj.h"

// Set the time that this object is going to be removed
void TemporaryObject::SetDeathTime()
{
	deletionTime = GetTickCount() + lifetime;
}

// Check if it is time for this object to be removed
void TemporaryObject::DeletionCheck()
{
	if (GetTickCount() >= deletionTime) toBeDeleted = true;
}

// Self-explanatory Getter
bool TemporaryObject::getToBeDeleted()
{
	return toBeDeleted;
}