#include "Credits.h"
#include "GlobalEnvironment.h"

void Credits::Update()
{
	credits.modifyY(-0.85f);

	if (credits.getPos().y <= -17185.0f)
	{
		Goto_Menu_Event* pTemp = new Goto_Menu_Event();
		gEnv->getEventDispatcher()->DispatchEvent(pTemp);
	}
}

void Credits::Render()
{
	background.Render();
	credits.Render();
}

void Credits::HandleEvent(Event* pEvent)
{

}

Credits::Credits()
{
	background.Initialize(1.0f, 1.0f, 1920, 1080, 1, 0, 0, 0, 1, 0, 0, 0, "CreditsBackground.jpg");
	credits.Initialize(1.0f, 1.0f, 1920, 19187, 1, 0, 0, 0, 1, 0, 0, 1085, "Credits.png");
}

Credits::~Credits()
{

}