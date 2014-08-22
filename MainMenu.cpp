#include "MainMenu.h"
#include "GlobalEnvironment.h"

void MainMenu::HandleEvent(Event* pEvent)
{
	if (pEvent->Event_Type == Event_Listings::MOUSE_CLICK)
	{
		Mouse_Click_Event* pTemp = static_cast<Mouse_Click_Event*>(pEvent);

		RECT tempRect;
		RECT tempTwo = pTemp->clickArea;

		/*
			Dispatch different events based on which RECT gets clicked on.
		*/
		if (IntersectRect(&tempRect, &startGameRect, &pTemp->clickArea))
		{
			// TODO: Redirect to screen with level select abilities
			Start_Game_Event* pTemp = new Start_Game_Event();
			gEnv->getEventDispatcher()->DispatchEvent(pTemp);
		}
		else if (IntersectRect(&tempRect, &creditsRect, &pTemp->clickArea))
		{
			// TODO: Implement this
			Goto_Credit_Event* pTemp = new Goto_Credit_Event();
			gEnv->getEventDispatcher()->DispatchEvent(pTemp);
		}
		else if (IntersectRect(&tempRect, &exitRect, &pTemp->clickArea))
		{
			Quit_Game_Event* pTemp = new Quit_Game_Event();
			gEnv->getEventDispatcher()->DispatchEvent(pTemp);
		}
	}
}

void MainMenu::Update()
{

}

void MainMenu::Render()
{
	Renderer.Render();
	//StartRender.Render();
	//CreditsRender.Render();
}

MainMenu::MainMenu()
{
	// Register with Event System
	ID = gEnv->getNewID();
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::MOUSE_CLICK);

	/// RECT = {Left, Top, Right, Bottom};
	//startGameRect = {784, 1164, 723, 660};
	startGameRect = {770, 670, 1155, 740};
	creditsRect = {758, 812, 1194, 888};
	exitRect;

	Renderer.Initialize(1.0f, 1.0f, 1920, 1080, 1, 0, 0, 0, 1, 0, 0, 0, "MainMenu.png");
	StartRender.Initialize(1.0f, 1.0f, 385, 70, 1, 0, 0, 0, 0, 0, 770, 670, "startRect.png");
	CreditsRender.Initialize(1.0f, 1.0f, 436, 76, 1, 0, 0, 0, 0, 0, 758, 812, "creditsRect.png");
	
}

MainMenu::~MainMenu()
{
	// Remove from Event System
	gEnv->getEventDispatcher()->PurgeListener(ID, Event_Listings::MOUSE_CLICK);
}