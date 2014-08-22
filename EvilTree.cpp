#include "EvilTree.h"
#include "GlobalEnvironment.h"
#include <cmath>
#include <mmsystem.h>

void EvilTree::RevertToIdle()
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
			/* 
				If the spawning animation completed, we'll register the AI with the event system and
				set the spawning to true so that other actions can be done within the Update function
			*/
			if (!spawningAnimationOver)
			{
				spawningAnimationOver = true;
				RegisterWithES();
			}

			Renderer.Initialize(70, 70, idleAnimationStart, idleAnimationEnd, 55);
		}
	}
}

void EvilTree::BoundaryEnforcement()
{

}

bool EvilTree::removeFromPlay()
{
	if (health == 0 && (Renderer.getCurrentFrame() == 70 || Renderer.getCurrentFrame() == 157))
	{
		// Play a death sound
			// This is commented out because it causes HUGE performance drops
		//std::ostringstream convert;
		//convert << (5 + (rand() % 9));
		//std::string num = convert.str();
		//std::string prefix = "WoodCrack";
		//std::string suffix = ".wav";
		//std::string soundName = prefix + num + suffix;
		//
		//deathSound->PlaySongMP3(soundName.c_str());

		return true;
	}
	else
	{
		return false;
	}
}

void EvilTree::RegisterWithES()
{
	
	// Register for all events that object will care about
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::PLAYER_ATTACK);
}

void EvilTree::HandleEvent(Event* pEvent)
{
	if (pEvent->Event_Type == Event_Listings::PLAYER_ATTACK)
	{
		Player_Attack_Event* pTemp = static_cast<Player_Attack_Event*>(pEvent);

		/*
			If the attack 
		*/
		if (abs((int)depth - (int)pTemp->depth) <= 60)
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
			}
		}
	}
}

void EvilTree::Update()
{
	RevertToIdle();

	if (spawningAnimationOver)
	{
		if (health <= 0)
		{
			(facingLeft) ? Renderer.Initialize(70, 70, 153, 157, 135) : Renderer.Initialize(70, 70, 66, 70, 135);
		}
		else
		{
			/*
				Cache these locally to eliminate some function call overhead.

				The center points allow us to more easily/accurately track the player,
				so that we can make better decisions about what actions are the beneficial
				at a given point.
			*/
			RECT playerRect = gEnv->getPlayerRECT();
			Vector2 playerCenter(playerRect.right - (playerRect.right - playerRect.left) / 2, playerRect.bottom - (playerRect.bottom - playerRect.top) / 2);

			RECT myRect = hitBox.getBoundingBox();
			Vector2 myCenter(myRect.right - (myRect.right - myRect.left) / 2, myRect.bottom - (myRect.bottom - myRect.top) / 2);

			// Very simple move towards player to attack code
			// change later
			if (playerCenter.x > myCenter.x)
			{
				// Player to the right, move towards
				Renderer.modifyX(3.0f);
				hasMoved = true;
				facingLeft = false;
			}
			else if (playerCenter.x < myCenter.x)
			{
				// Player to the left, move towards
				Renderer.modifyX(-3.0f);
				hasMoved = true;
				facingLeft = true;
			}

			if (playerCenter.y > myCenter.y)
			{
				// Player below, move towards
				Renderer.modifyY(2.25f);
				hasMoved = true;
			}
			else if (playerCenter.y < myCenter.y)
			{
				//Player above, move towards
				Renderer.modifyY(-2.25f);
				hasMoved = true;
			}

			// If we've moved, we need to switch animations
			if (hasMoved)
			{
				if (facingLeft)
				{
					Renderer.Initialize(70, 70, 85, 98, 60);
				}
				else
				{
					Renderer.Initialize(70, 70, 3, 17, 60);
				}

				depth = hitBox.getBoundingBox().bottom - (hitBox.getBoundingBox().bottom - hitBox.getBoundingBox().top) / 2;
			}

			// 
			if (facingLeft)
			{
				idleAnimationStart = 85;
				idleAnimationEnd = 88;
			}
			else
			{
				idleAnimationStart = 0;
				idleAnimationEnd = 3;
			}

			// Occasionally play a menacing sound
			if (rand() % 1000 >= 995)
			{
				// Play a death sound
				std::ostringstream convert;
				convert << (1 + (rand() % 9));
				std::string num = convert.str();
				std::string prefix = "mnstr";
				std::string suffix = ".wav";
				std::string soundName = prefix + num + suffix;
				menacingSound->PlaySongMP3(soundName.c_str());
			}
		}
	}
	else
	{
		if (!soundPlayed)
		{
			// Play spawning sound
			std::ostringstream convert;
			convert << (1 + (rand() % 4));
			std::string num = convert.str();
			std::string prefix = "WoodCrack";
			std::string suffix = ".wav";
			std::string soundName = prefix + num + suffix;
			
			spawnSound->PlaySongMP3(soundName.c_str());

			soundPlayed = true;
		}
	}

	hitBox.UpdateCollider(Renderer.getPos().x, Renderer.getPos().y);
	Renderer.Update();

	hasMoved = false;
}

void EvilTree::Render()
{
	Renderer.Render();

	// Potentially render weapons in the future
}

EvilTree::EvilTree(unsigned int xPosition, unsigned int yPosition)
{
	spawningAnimationOver = false;
	isAttacking = false;
	hasMoved = false;
	health = 5;

	ID = gEnv->getNewID();

	/*
		To provide some variance, this kind of AI will have different spawning
		animation rates.

		Hopefully this forces the player to priortize certain mobs (as they'll visibly
		spawn faster), and will provide some extra mechanics for the player to learn.
	*/
	int tempAnimationDelay = rand() % 80 + 140;
	int spawnFrameStart = 0;
	int spawnFrameEnd = 0;

	if (gEnv->getPlayerRECT().left > xPosition)
	{
		facingLeft = false;

		idleAnimationStart = 0;
		idleAnimationEnd = 3;
		spawnFrameStart = 49;
		spawnFrameEnd = 55;
	}
	else
	{
		facingLeft = true;

		idleAnimationStart = 85;
		idleAnimationEnd = 88;
		spawnFrameStart = 136;
		spawnFrameEnd = 142;
	}

	// Initialize the renderer with the information of the EvilTree
	Renderer.Initialize(1.5f, 1.5f, 70, 70, 17, spawnFrameStart, spawnFrameEnd, tempAnimationDelay, 1, 0, xPosition, yPosition, "EvilTree2.png");

	Renderer.setAnimateFlag(true);

	hitBox.Initialize(Renderer.getPos().x, Renderer.getPos().y, Renderer.getAdjustedWidth(), Renderer.getAdjustedHeight());

	// Initialize sounds
	spawnSound = new MP3();
	menacingSound = new MP3();
	deathSound = new MP3();
	soundPlayed = false;
}

EvilTree::~EvilTree()
{
	// Remove the AI from the Event System
	gEnv->getEventDispatcher()->PurgeListener(ID, Event_Listings::PLAYER_ATTACK);

	if (spawnSound != NULL)
	{
		delete spawnSound;
		spawnSound = NULL;
	}
	if (menacingSound != NULL)
	{
		delete menacingSound;
		menacingSound = NULL;
	}
	if (deathSound != NULL)
	{
		delete deathSound;
		deathSound = NULL;
	}
}