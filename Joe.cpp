#include "Joe.h"
#include "IWeapon.h"
#include <cmath>
#include "GlobalEnvironment.h"

void Joe::SwitchWeapon(unsigned int changeInIndex)
{
	/*
		If the new index value is too large or too small, we 'loop' around.

		Otherwise, we just increment/decrement by the passed amount
	*/
	if (currentWeapon + changeInIndex > Weapons.size() - 1)
	{
		currentWeapon = 0;
	}
	else if (currentWeapon + changeInIndex < 0)
	{
		currentWeapon = Weapons.size() - 1;
	}
	else
	{
		currentWeapon += changeInIndex;
	}
}

void Joe::RevertToIdle()
{
	// No need to change frames because we're already on the idle frame
	if (Renderer.getEndFrame() == idleAnimationEnd)
	{
		return;
	}
	else
	{
		/*
			Check to see if the current animation is done. If it is, and we're not moving,
			switch to the idle animation.
		*/
		if (Renderer.getCurrentFrame() == Renderer.getEndFrame())
		{
			Renderer.Initialize(200, 200, idleAnimationStart, idleAnimationEnd, 55);
		}
	}
}

void Joe::BoundaryEnforcement()
{
#pragma region Prevent player from leaving play area
	// Right boundary
	if (hitBox.getBoundingBox().right > Play_Area::RIGHT)
	{
		Renderer.modifyX(-(hitBox.getBoundingBox().right - Play_Area::RIGHT));
	}

	// Left boundary
	if (hitBox.getBoundingBox().left < Play_Area::LEFT)
	{
		Renderer.modifyX(Play_Area::LEFT - hitBox.getBoundingBox().left);
	}

	// Top boundary
	if (hitBox.getBoundingBox().top < 350.0f)
	{
		Renderer.modifyY(350 - hitBox.getBoundingBox().top);
	}
	
	// Bottom boundary
	if (hitBox.getBoundingBox().bottom > Play_Area::BOTTOM)
	{
		Renderer.modifyY(-(hitBox.getBoundingBox().bottom - Play_Area::BOTTOM));
	}
#pragma endregion

#pragma region Encounter specific code

	if (hitBox.getBoundingBox().right > SCREENW / 2)
	{
		if (movedRight)
		{
			// Reset flag to prevent false positives
			movedRight = false;

			/*
				If the player isn't in an encounter, we need to send an event 
				specifying the
			*/
			if (!inEncounter)
			{
				Player_Move_Event* pTemp = new Player_Move_Event(6.5f);
				gEnv->getEventDispatcher()->DispatchEvent(pTemp);

				// The character is only slightly past the halfway point, so just snap them into place
				if (abs(hitBox.getBoundingBox().right - SCREENW / 2) <= 7)
				{
					Renderer.modifyX(-(hitBox.getBoundingBox().right - (SCREENW / 2)));
				}
				// The player is somewhere beyond the error threshold, so slowly move them back
				else
				{
					//Renderer.modifyX(-(hitBox.getBoundingBox().right - (SCREENH / 2)));
					Renderer.modifyX(-9.0f);
				}
			}
		}
	}
#pragma endregion

	// Update the collider with any changes that may have been made
	hitBox.Initialize(Renderer.getPos().x + 70 * Renderer.getScaleX(), Renderer.getPos().y + 66 * Renderer.getScaleY(), 60 * Renderer.getScaleX(), 73 * Renderer.getScaleY());
}

void Joe::HandleEvent(Event* pEvent)
{
	/*
		TODO: Handle damage events
				Receive damage and handle accordingly
	*/
	if (pEvent->Event_Type == Event_Listings::PLAYER_INPUT)
	{
		Player_Input_Event* pTemp = static_cast<Player_Input_Event*>(pEvent);

		// Attack
		if (pTemp->attack)
		{
			if (Weapons.size() > 0 && !isAttacking)
			{
				Weapons[currentWeapon]->Update(Renderer.getPos().x, Renderer.getPos().y, facingLeft);
				isAttacking = Weapons[currentWeapon]->Attack(hitBox.getBoundingBox(), depth);
				if (isAttacking)
				{
					// Play whoosh sound
					whooshSound->MP3Stop();

					std::ostringstream convert;
					convert << (1 + (rand() % 13));
					std::string num = convert.str();
					std::string prefix = "swing";
					std::string suffix = ".wav";
					std::string soundName = prefix + num + suffix;
					
					whooshSound->PlaySongMP3(soundName.c_str());
				}
			}
		}

		if (!isAttacking)
		{
			// Right/Left movement
			if (pTemp->right)
			{
				Renderer.modifyX(6.5f);

				facingLeft = false;
				hasMoved = true;
				movedRight = true;
			}
			else if (pTemp->left)
			{
				Renderer.modifyX(-6.5f);

				facingLeft = true;
				hasMoved = true;
			}

			if (pTemp->up)
			{
				Renderer.modifyY(-4.0f);

				hasMoved = true;
			}
			else if (pTemp->down)
			{
				Renderer.modifyY(4.0f);

				hasMoved = true;
			}

			if (pTemp->nextWeap)
			{
				SwitchWeapon(1);
			}
			else if (pTemp->prevWeap)
			{
				SwitchWeapon(-1);
			}

			if (pTemp->jump && isJumping)
			{
				isJumping = true;

				// TODO: Set animation frames
			}

			// If Joe has moved as part of this input cycle, we need to change his animations
			if (hasMoved)
			{
				// Change the idle animations depending on the new facing direction 
				if (facingLeft)
				{
					Renderer.Initialize(200, 200, 6, 9, 65);
				}
				else
				{
					Renderer.Initialize(200, 200, 1, 4, 65);
				}

				//Update the collider, and make sure we're still in the play area
				hitBox.Initialize(Renderer.getPos().x + 70 * Renderer.getScaleX(), Renderer.getPos().y + 66 * Renderer.getScaleY(), 60 * Renderer.getScaleX(), 73 * Renderer.getScaleY());
				BoundaryEnforcement();
			}
		}
	}
	else if (pEvent->Event_Type == Event_Listings::START_ENCOUNTER)
	{
		inEncounter = true;
	}
	else if (pEvent->Event_Type == Event_Listings::END_ENCOUNTER)
	{
		inEncounter = false;
	}
}

void Joe::Update()
{
	if (hasMoved)
	{
		Weapons[currentWeapon]->ComposerMoved();
		hasMoved = false;
	}
	else
	{
		RevertToIdle();
	}

	// Update the player
	Renderer.Update();

	if (Weapons.size() > 0)
	{
		Weapons[currentWeapon]->Update(Renderer.getPos().x, Renderer.getPos().y, facingLeft);
	}

	/*
		Joe's behavior may need to change based on his current state. Generally, 
		these changes are just animation start/end frame modifications.
	*/
	if (isAttacking)
	{
		isAttacking = !(Weapons[currentWeapon]->FinishedAttacking());
	}
	if (isJumping)
	{

	}
	if (facingLeft)
	{
		idleAnimationStart = 5;
		idleAnimationEnd = 5;
	}
	else
	{
		idleAnimationStart = 0;
		idleAnimationEnd = 0;
	}

	depth = hitBox.getBoundingBox().bottom - (hitBox.getBoundingBox().bottom - hitBox.getBoundingBox().top) / 2;
}

void Joe::Render()
{
	// Render the player
	Renderer.Render();

	// Render the active weapon
	if (Weapons.size() > 0)
	{
		Weapons[currentWeapon]->Render();
	}
}

const RECT Joe::getRECT()
{
	return hitBox.getBoundingBox();
}

void Joe::AddWeapon(IWeapon* pWeapon)
{
	Weapons.push_back(pWeapon);
}

void Joe::SwitchWeaponVector(std::vector<IWeapon*>& WeaponVector)
{
	// Deallocate any memory in the current vector before we switch to a new one
	for (std::vector<IWeapon*>::iterator it = Weapons.begin(); it != Weapons.end();)
	{
		IWeapon* pTemp = (*it);
		it = Weapons.erase(it);

		delete pTemp;
		pTemp = NULL;
	}

	// Shallow copy the vector to preserve the pointers
	Weapons = WeaponVector;

	// Don't go out of the bounds of the vector
	if (currentWeapon > Weapons.size())
	{
		currentWeapon = 0;
	}
}

Joe::Joe()
{
	currentWeapon = 0;
	isAttacking = false;
	isJumping = false;
	hasMoved = false;
	inEncounter = false;
	movedRight = false;

	// Register with Event System
	gEnv->setPlayer(this);
	ID = gEnv->getNewID();
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::PLAYER_INPUT);
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::START_ENCOUNTER);
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::END_ENCOUNTER);

	idleAnimationStart = 0;
	idleAnimationEnd = 0;
	Renderer.Initialize(2.5f, 2.5f, 200, 200, 10, 0, 0, 0, 1, 0, 500.0f, 300.0f, "Joepla_body.png");
	Renderer.setAnimateFlag(true);

	// Wrap the hitbox around Joe's body, but exclude as much of the white around Joe as possible
	hitBox.Initialize(Renderer.getPos().x + 70 * Renderer.getScaleX(), Renderer.getPos().y + 66 * Renderer.getScaleY(), 60 * Renderer.getScaleX(), 73 * Renderer.getScaleY());

	// Init sounds
	whooshSound = new MP3();
}

Joe::~Joe()
{
	gEnv->getEventDispatcher()->PurgeListener(ID, Event_Listings::PLAYER_INPUT);
	gEnv->getEventDispatcher()->PurgeListener(ID, Event_Listings::START_ENCOUNTER);
	gEnv->getEventDispatcher()->PurgeListener(ID, Event_Listings::END_ENCOUNTER);

	for (int i = 0; i < Weapons.size(); ++i)
	{
		delete Weapons[i];
	}

	// Deallocate sounds
	if (whooshSound != NULL)
	{
		delete whooshSound;
		whooshSound = NULL;
	}
}