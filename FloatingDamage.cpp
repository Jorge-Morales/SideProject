// Floating Damage implementation

#include "FloatingDamage.h"
#include "GlobalEnvironment.h"

/// Update - Float upwards while alive
void FloatingDamage::Update()
{
	// Float upwards slowly
	Renderer.setY(Renderer.getPos().y - 2.5f);

	// Ready to die?
	DeletionCheck();

	// Update renderer
	Renderer.Update();
}

/// Register this class with the Factory
//void FloatingDamage::Register()
//{
//	gEnv->getFactory()->RegisterNewObject(150, new FloatingDamage);
//	/*int ID = 150;
//	return new FloatingDamage(startX, startY);*/
//}

/// Use this to create a new FloatingDamage object
TemporaryObject* FloatingDamage::CreateInstance(float startX, float startY)
{
	return new FloatingDamage(startX, startY);
}

/// Render
void FloatingDamage::Render()
{
	Renderer.Render();
}

/// Constructor
FloatingDamage::FloatingDamage()
{

}

FloatingDamage::FloatingDamage(float startX, float startY)
{
	// Initialize
	lifetime = 500;
	toBeDeleted = false;
	SetDeathTime();
	Renderer.Initialize(1.0f, 1.0f, 64, 64, 10, 0, 0, 0, 1, 0.0f, startX, startY, "alpha.png");
}

/// Unconstructor
FloatingDamage::~FloatingDamage()
{

}