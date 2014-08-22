#include "GameMouse.h"
#include "GlobalEnvironment.h"

/*
	altRender, drawRect, and clickRect are all debug variables that help show where the mouse
	is clicking. Uncomment them if we need to visually debug at any point.
*/

//RECT drawRect;

enum MouseStates
{
	inactive = 0,
	active = 1
};

void GameMouse::Update()
{
	GetCursorPos(&curPos);

	if (curPos.x != prevPos.x)
	{
		Renderer.modifyX(-(prevPos.x - curPos.x));

		prevPos.x = curPos.x;
	}

	if (curPos.y != prevPos.y)
	{
		Renderer.modifyY(-(prevPos.y - curPos.y));

		prevPos.y = curPos.y; 
	}
}

void GameMouse::Render()
{
	if (state != inactive)
	{
		Renderer.Render();
		//altRender.Render();
	}
}

void GameMouse::ProcessInput(unsigned int mask)
{
	/*
		Bitmask used to determine mouse input.

		1 = Left click
		2 = Right click
	*/
	if (state == active)
	{
		if (!leftClick)
		{
			leftClick = (mask & 1);
		}
		else
		{
			/*
				If the player left clicked in the past, but is no holding down the left
				click button, we need to dispatch a click event.
			*/
			if (leftClick && !(mask & 1))
			{
				// Reset leftClick value
				leftClick = false;

				Mouse_Click_Event* pTemp = new Mouse_Click_Event();

				// Create a RECT that contains the location of the click
				RECT clickRect;
				clickRect.left = Renderer.getPos().x + (Renderer.getAdjustedWidth() / 2) - 1;
				clickRect.right = clickRect.left + 2;
				clickRect.top = Renderer.getPos().y + (Renderer.getAdjustedHeight() / 2) - 1;
				clickRect.bottom = clickRect.top + 2;

				//drawRect = clickRect;
				//altRender.Initialize(5.0f, 5.0f, 2, 2, 1, 0, 0, 0, 0, 0, drawRect.left, drawRect.top, "creditsRect.png");
				pTemp->clickArea = clickRect;

				gEnv->getEventDispatcher()->DispatchEvent(pTemp);
			}
		}

		rightClick = (mask & 2);
	}
}

void GameMouse::HandleEvent(Event* pEvent)
{
	if (pEvent->Event_Type == Event_Listings::START_GAME ||
		pEvent->Event_Type == Event_Listings::GOTO_CREDITS)
	{
		state = inactive;
	}
	else if (pEvent->Event_Type == Event_Listings::GOTO_MENU)
	{
		state = active;
	}
}

GameMouse::GameMouse()
{
	// Save current mouse coordinates
	GetCursorPos(&prevPos);
	curPos = prevPos;

	// Register with Event System
	ID = gEnv->getNewID();
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::START_GAME);
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::GOTO_MENU);
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::GOTO_CREDITS);

	// Initialize the rendering interface
	Renderer.Initialize(1.0f, 1.0f, 80, 80, 1, 0, 0, 1, 1, 0, curPos.x, curPos.y, "mouse_ptr.png");
	state = active;
}

GameMouse::~GameMouse()
{

}