/*
	Temporary Object
	- Useful for floating damage, particle effects, etc.
	- Anything that is going to be on the screen for a set period
		of time and then disappear
*/

#ifndef TEMPOBJ_H
#define TEMPOBJ_H

#include "IRenderableObject.h"
#include "2DRender.h"

class TemporaryObject : public IRenderableObject
{
protected:

	// Variables for determining how long this should stay on-screen
	int deletionTime;
	int lifetime;

	// Should this object be deleted?
	bool toBeDeleted;

	// Determine when this object should be deleted
	void SetDeathTime();

	// Check if this object should be deleted
	void DeletionCheck();

	// The renderer
	TwoDRenderer Renderer;

public:

	// Self-explanatory Getter
	bool getToBeDeleted();

	virtual TemporaryObject* CreateInstance(float, float) = 0;

	virtual void Update() = 0;
	virtual ~TemporaryObject(){}
};

#endif TEMPOBJ_H