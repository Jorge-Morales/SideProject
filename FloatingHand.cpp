// Floating Damage implementation

#include "FloatingHand.h"
#include "GlobalEnvironment.h"

/// Update - Animate
void FloatingHand::Update()
{
	// Ready to die?
	DeletionCheck();

	// Update renderer
	Renderer.Update();
}

/// Register this class with the Factory
//void FloatingHand::Register()
//{
//	gEnv->getFactory()->RegisterNewObject(150, new FloatingHand);
//	/*int ID = 150;
//	return new FloatingHand(startX, startY);*/
//}

/// Use this to create a new FloatingHand object
TemporaryObject* FloatingHand::CreateInstance(float startX, float startY)
{
	return new FloatingHand(startX, startY);
}

/// Render
void FloatingHand::Render()
{
	Renderer.Render();
}

/// Constructor
FloatingHand::FloatingHand()
{

}

FloatingHand::FloatingHand(float startX, float startY)
{
	// Initialize
	lifetime = 5000;
	toBeDeleted = false;
	SetDeathTime();
	Renderer.Initialize(1.0f, 1.0f, 200, 200, 2, 0, 1, 500, 1, 0.0f, startX, startY, "FloatingHand.png");
	Renderer.setAnimateFlag(true);
}

/// Unconstructor
FloatingHand::~FloatingHand()
{

}