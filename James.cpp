#include "James.h"
#include "GlobalEnvironment.h"

void James::RevertToIdle()
{
	// If we're already on the idle animation, we can end the function here
	if (Renderer.getEndFrame() == idleAnimationEnd)
	{
		return;
	}
	else
	{
		// If the current animation is finished, we'll switch back to the idle animation
		if (Renderer.getCurrentFrame() == Renderer.getEndFrame())
		{
			Renderer.Initialize(1037, 1557, idleAnimationStart, idleAnimationEnd, 150);
		}
	}
}

void James::BoundaryEnforcement()
{
	// JAMES OBEYS NO RULES ON MOVEMENT
}

bool James::removeFromPlay()
{
	if (health == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void James::RegisterWithES()
{
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::PLAYER_ATTACK);
}

void James::HandleEvent(Event* pEvent)
{
	if (pEvent->Event_Type == Event_Listings::PLAYER_ATTACK)
	{
		Player_Attack_Event* pTemp = static_cast<Player_Attack_Event*>(pEvent);

		RECT tempRect;

		if (abs((int)depth - (int)pTemp->depth) <= 250)
		{
			// Check to see if our hitbox intersects with the attack's hitbox. 
			RECT tempRect;
			if (IntersectRect(&tempRect, &hitBox.getBoundingBox(), &pTemp->damageBox))
			{
				// Testing tempObj
				Create_TempObj_Event* tempObjTest = new Create_TempObj_Event();
				tempObjTest->x = hitBox.getBoundingBox().left;
				tempObjTest->y = hitBox.getBoundingBox().top;
				tempObjTest->ID = FLOATING_DAMAGE;
				gEnv->getEventDispatcher()->DispatchEvent(tempObjTest);

				if (pTemp->damage > health)
				{
					health = 0;
				}
				else
				{
					health -= pTemp->damage;
				}

				Renderer.Initialize(1037, 1557, 36, 40, 150);
			}
		}
	}
}

void James::Update()
{
	static bool jamesPlayedSound = false;

	if (!jamesPlayedSound)
	{
		PlaySound("NSJ2.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		jamesPlayedSound = true;
	}

	/*
		If the spawning animation completed, we'll register the AI with the event system and
		set the spawning to true so that other actions can be done within the Update function
	*/
	if (!spawningAnimationOver)
	{
		Renderer.modifyY(4.5f);
		static int startTime = GetTickCount();

		/*
			If sufficient time has passed since James has spawned,
			register with the Event System and switch animations
		*/
		if (GetTickCount() > startTime + 4000)
		{
			spawningAnimationOver = true;
			RegisterWithES();

			Renderer.Initialize(1037, 1557, idleAnimationStart, idleAnimationEnd, 150);
		}
	}
	else
	{

		RevertToIdle();
	}

	Renderer.Update();

	// Update depth value
	depth = hitBox.getBoundingBox().bottom - (hitBox.getBoundingBox().bottom - hitBox.getBoundingBox().top) / 2;
	hitBox.UpdateCollider(Renderer.getPos().x, Renderer.getPos().y);
}

void James::Render()
{
	Renderer.Render();
}

James::James()
{
	// Register with Event System
	ID = gEnv->getNewID();
	isAttacking = false;
	hasMoved = false;
	health = 50;
	idleAnimationStart = 12;
	idleAnimationEnd = 17;

	Renderer.Initialize(0.35f, 0.35f, 1037, 1557, 6, 6, 7, 145, 1, 0, SCREENW - SCREENW / 3, -545.0f, "James.png");
	Renderer.setAnimateFlag(true);

	hitBox.Initialize(Renderer.getPos().x, Renderer.getPos().y, Renderer.getAdjustedWidth(), Renderer.getAdjustedHeight());
}

James::~James()
{
	gEnv->getEventDispatcher()->PurgeListener(ID, Event_Listings::PLAYER_ATTACK);
}