#include "UI.h"
#include "GlobalEnvironment.h"

void UI::HandleEvent(Event* pEvent)
{

}

void UI::Update()
{
	// Not sure anything needs to go here
}

void UI::Render()
{
	Renderer.Render();
}

UI::UI()
{
	ID = gEnv->getNewID();
	gEnv->getEventDispatcher()->RegisterListener(this, Event_Listings::SCORE_EVENT);

	Renderer.Initialize(1.0f, 1.0f, 1920, 1080, 1, 0, 0, 0, 0, 0, 0, 0, "UI.png");
}

UI::~UI()
{
	gEnv->getEventDispatcher()->PurgeListener(ID, Event_Listings::SCORE_EVENT);
}