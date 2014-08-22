#ifndef FLOATINGHAND_H
#define FLOATINGHAND_H
#include "TempObj.h"

/*
	Floating Hand Object

	When the player finishes an encounter, a floating hand will
	appear, pointing the player to continue the level.
*/

class FloatingHand : public TemporaryObject
{
private:



public:

	void Update();
	void Render();

	/*
		CreateInstance creates a FloatingHand object with
		given coordinates.

		Use this to create FloatingHand objects.
	*/
	TemporaryObject* CreateInstance(float startX, float startY);

	// Tors
	FloatingHand();
	FloatingHand(float startX, float startY);
	~FloatingHand();
};

#endif