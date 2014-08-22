// Floating Damage - When something is damaged, make numbers float above it

#ifndef FLOATINGDMG_H
#define FLOATINGDMG_H

#include "TempObj.h"

class FloatingDamage : public TemporaryObject
{
private:

	int dmg;

	// Register registers this class with the Factory
	//static void Register();

public:

	void Update();
	void Render();

	/*
		CreateInstance creates a FloatingDamage object with
		given coordinates.

		Use this to create FloatingDamage objects.
	*/
	TemporaryObject* CreateInstance(float startX, float startY);


	// Tors
	FloatingDamage();
	FloatingDamage(float startX, float startY);
	~FloatingDamage();
};

#endif FLOATINGDMG_H