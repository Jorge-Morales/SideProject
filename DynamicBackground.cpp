// I HOPE YOU'RE HAPPY, WHORE HEY
// Dynamic Background implementation

#include "DynamicBackground.h"

// Handle Event function
void DynamicBackground::HandleEvent(Event* pEvent)
{
	if (pEvent->Event_Type == Event_Listings::PLAYER_MOVE)
	{
		Player_Move_Event* pTemp = static_cast<Player_Move_Event*>(pEvent);

		// get the amount this background needs to move
		Renderer.modifyX(-1.0f * (pTemp->amountMoved) * moveSpeed);
	}
	if (pEvent->Event_Type == Event_Listings::START_ENCOUNTER)
	{
		isLocked = true;
	}
	if (pEvent->Event_Type == Event_Listings::END_ENCOUNTER)
	{
		isLocked = false;
	}
}

// Update
void DynamicBackground::Update()
{
	Renderer.Update();
}

// Render
void DynamicBackground::Render()
{
	Renderer.Render();
}

// Get position
Vector2 DynamicBackground::getPos()
{
	return Renderer.getPos();
}


// Tors
DynamicBackground::DynamicBackground()
{
	Renderer.Initialize(1.0f, 1.0f, 5120, 768, 1, 0, 0, 0, 1, 0, 0.0f, 0.0f, "Hallway.jpg");
	Renderer.setX(0.0f);
	Renderer.setY(0.0f);
	this->moveSpeed = 1;
	isLocked = false;

	// Start listening for Start/End Encounter and Player Move events
	ID = gEnv->getNewID();
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::PLAYER_MOVE);
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::START_ENCOUNTER);
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::END_ENCOUNTER);
}

DynamicBackground::DynamicBackground(float MS, int frameW, int frameH, float startX, float startY, std::string texture)
{
	Renderer.Initialize(1.0f, 1.0f, frameW, frameH, 1, 0, 0, 0, 1, 0, 0.0f, 0.0f, texture);
	Renderer.setX(startX);
	Renderer.setY(startY);
	this->moveSpeed = MS;
	isLocked = false;

	// Start listening for Start/End Encounter and Player Move events
	ID = gEnv->getNewID();
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::PLAYER_MOVE);
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::START_ENCOUNTER);
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::END_ENCOUNTER);
}

DynamicBackground::~DynamicBackground()
{
	gEnv->getEventDispatcher()->PurgeListener(ID, Event_Listings::PLAYER_MOVE);
	gEnv->getEventDispatcher()->PurgeListener(ID, Event_Listings::START_ENCOUNTER);
	gEnv->getEventDispatcher()->PurgeListener(ID, Event_Listings::END_ENCOUNTER);
}