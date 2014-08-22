// Background Manager implementation

#include "BackgroundManager.h"
#include "GlobalEnvironment.h"
#include <algorithm>

// Add a background
void BackgroundManager::AddBackground(IBackground* newBG)
{
	backgrounds.push_back(newBG);
}

// Update the backgrounds
void BackgroundManager::Update()
{
	// If the background that we care about reaches a certain position, start an
	// encounter. We only care about one background.
	if (encounterStartPos.size() > 0 && (( -(*backgrounds[getPlayAreaLayerNum()]).getPos().x) >= encounterStartPos.front()))
	{
		// Start an encounter
		gEnv->getEventDispatcher()->DispatchEvent(new Start_Encounter_Event);

		// Pop the first position in the ESP queue so the next
		//	encounter will happen at the next location
		encounterStartPos.pop();
	}

	for (std::vector<IBackground*>::iterator bIt = backgrounds.begin(); bIt != backgrounds.end(); ++bIt)
	{
		(*bIt)->Update();
	}
}

// Render the backgrounds
void BackgroundManager::Render()
{
	for (std::vector<IBackground*>::iterator bIt = backgrounds.begin(); bIt != backgrounds.end(); ++bIt)
	{
		(*bIt)->Render();
	}
}

// Set the encounter positions
void BackgroundManager::SetEncounterPositions(std::vector<float> encounterPos)
{
	// Sort the encounter positions in ascending order. /// ABSOLUTELY MANDATORY <--Not kidding
	std::sort(encounterPos.begin(), encounterPos.end());
	
	// Reverse (because we're pushing stuff into the queue backwards)
	std::reverse(encounterPos.begin(), encounterPos.end());

	// Push the encounter positions into the queue
	while (!encounterPos.empty())
	{
		/*
			Push the last element (the smallest one, see the std::reverse above)
			into the queue, then pop that element off of the vector
		*/
		float temp = encounterPos.back();
		encounterStartPos.push(temp);
		encounterPos.pop_back();
	}
}

// Self-explanatory Getter and Setter functions
int BackgroundManager::getNumLayers()
{
	return totalLayers;
}
int BackgroundManager::getPlayAreaLayerNum()
{
	return playAreaLayer;
}

void BackgroundManager::SetNumLayers(int numLayers)
{
	totalLayers = numLayers;
}
void BackgroundManager::SetPlayAreaLayerNum(int pan)
{
	playAreaLayer = pan;
}

BackgroundManager::BackgroundManager()
{
	
}

BackgroundManager::~BackgroundManager()
{
	// Damn you for not managing your memory Garhett
	for (int i = 0; i < backgrounds.size(); ++i)
	{
		delete backgrounds[i];
	}
}